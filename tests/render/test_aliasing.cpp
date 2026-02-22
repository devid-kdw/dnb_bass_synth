#include "render_test_utils.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <algorithm>
#include <cmath>
#include <limits>
#include <numbers>
#include <vector>

namespace {

constexpr double kSampleRate = 44100.0;
constexpr int kBlockSize = 512;
constexpr int kWarmupBlocks = 10;
constexpr int kAnalysisSamples = 4096;
constexpr int kStressNote = 120; // C9

constexpr float kAliasBandLowHz = 30.0f;
constexpr float kAliasBandHighHz = 5000.0f;
constexpr float kReferenceBandLowHz = 7000.0f;
constexpr float kReferenceBandHighHz = 18000.0f;
constexpr float kMaxFoldbackRatioDb = -4.0f;

float computeBandEnergyDft(const std::vector<float> &samples, double sampleRate,
                           float lowHz, float highHz) {
  const size_t n = samples.size();
  if (n == 0 || lowHz >= highHz) {
    return 0.0f;
  }

  std::vector<double> windowed(n, 0.0);
  for (size_t i = 0; i < n; ++i) {
    const double phase = (2.0 * std::numbers::pi_v<double> * static_cast<double>(i)) /
                         static_cast<double>(n - 1);
    const double hann = 0.5 * (1.0 - std::cos(phase));
    windowed[i] = static_cast<double>(samples[i]) * hann;
  }

  const double binHz = sampleRate / static_cast<double>(n);
  size_t kStart = static_cast<size_t>(std::ceil(lowHz / binHz));
  size_t kEnd = static_cast<size_t>(std::floor(highHz / binHz));
  kStart = std::max<size_t>(kStart, 1);
  kEnd = std::min(kEnd, (n / 2) - 1);

  if (kStart > kEnd) {
    return 0.0f;
  }

  double energy = 0.0;
  for (size_t k = kStart; k <= kEnd; ++k) {
    double re = 0.0;
    double im = 0.0;
    const double base =
        -2.0 * std::numbers::pi_v<double> * static_cast<double>(k) /
        static_cast<double>(n);

    for (size_t i = 0; i < n; ++i) {
      const double angle = base * static_cast<double>(i);
      const double sample = windowed[i];
      re += sample * std::cos(angle);
      im += sample * std::sin(angle);
    }

    energy += (re * re) + (im * im);
  }

  return static_cast<float>(energy);
}

} // namespace

// Aliasing evidence: compare low-band foldback energy against high-band
// program energy under deterministic nonlinear stress.
TEST_CASE("Aliasing foldback energy remains at least 4dB below high-band energy",
          "[render][aliasing]") {
  SynthEngine engine;
  engine.prepare(kSampleRate, kBlockSize);

  applyTestParams(engine, [](ResolvedParams &map) {
    map.fmDepth = 1.0f;
    map.foldDrive = 1.0f;
    map.distAmount = 1.0f;
    map.ottDepth = 0.6f;
  });

  juce::AudioBuffer<float> block(2, kBlockSize);
  engine.processMidiEvent(kStressNote, 1.0f, true);

  for (int i = 0; i < kWarmupBlocks; ++i) {
    engine.processBlock(block.getWritePointer(0), block.getWritePointer(1),
                        kBlockSize);
  }

  std::vector<float> analysis;
  analysis.reserve(kAnalysisSamples);
  while (analysis.size() < static_cast<size_t>(kAnalysisSamples)) {
    engine.processBlock(block.getWritePointer(0), block.getWritePointer(1),
                        kBlockSize);
    auto *left = block.getReadPointer(0);
    for (int i = 0; i < kBlockSize &&
                    analysis.size() < static_cast<size_t>(kAnalysisSamples);
         ++i) {
      const float s = left[i];
      REQUIRE(std::isfinite(s));
      analysis.push_back(s);
    }
  }

  const float aliasEnergy = computeBandEnergyDft(
      analysis, kSampleRate, kAliasBandLowHz, kAliasBandHighHz);
  const float referenceEnergy = computeBandEnergyDft(
      analysis, kSampleRate, kReferenceBandLowHz, kReferenceBandHighHz);

  REQUIRE(referenceEnergy > 0.0f);

  const float epsilon = std::numeric_limits<float>::epsilon();
  const float foldbackRatioDb = 10.0f * std::log10(
                                           std::max(aliasEnergy, epsilon) /
                                           std::max(referenceEnergy, epsilon));

  CAPTURE(aliasEnergy, referenceEnergy, foldbackRatioDb);
  REQUIRE(foldbackRatioDb <= kMaxFoldbackRatioDb);
}
