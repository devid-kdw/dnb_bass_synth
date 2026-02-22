#pragma once
#include "render_test_utils.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

TEST_CASE("Anti-click handles rapid note on/off", "[render][qa]") {
  SynthEngine engine;
  engine.prepare(44100.0, 512);
  applyTestParams(engine);

  juce::AudioBuffer<float> block(2, 512);

  // Rapid fire: On, Off, On, Off within same block (simulated sequentially
  // before block)
  engine.processMidiEvent(36, 1.0f, true);
  engine.processMidiEvent(36, 0.0f, false);
  engine.processMidiEvent(36, 1.0f, true);
  engine.processMidiEvent(36, 0.0f, false);

  engine.processBlock(block.getWritePointer(0), block.getWritePointer(1), 512);

  // Validate anti-click works by looking for discontinuities (huge deltas)
  auto *L = block.getReadPointer(0);
  float maxDelta = 0.0f;
  for (int i = 1; i < 512; ++i) {
    float delta = std::abs(L[i] - L[i - 1]);
    maxDelta = std::max(maxDelta, delta);
  }

  // Smooth ramp should restrict sample-to-sample difference
  REQUIRE(maxDelta < 0.1f);
}

TEST_CASE("Mono compatibility limits cross phasing", "[render][qa]") {
  SynthEngine engine;
  engine.prepare(44100.0, 512);
  applyTestParams(engine);

  juce::AudioBuffer<float> block(2, 512);
  engine.processMidiEvent(36, 1.0f, true);

  engine.processBlock(block.getWritePointer(0), block.getWritePointer(1), 512);

  auto *L = block.getReadPointer(0);
  auto *R = block.getReadPointer(1);

  // Calculate correlation for sub band
  // Since Sub is strictly mono, L and R should be highly correlated
  float lPower = 0.0f, rPower = 0.0f, crossPower = 0.0f;
  for (int i = 0; i < 512; ++i) {
    lPower += L[i] * L[i];
    rPower += R[i] * R[i];
    crossPower += L[i] * R[i];
  }

  float correlation = crossPower / std::sqrt(lPower * rPower);
  // Since Character osc is mixed in (stereo), correlation won't be 1.0
  // But it must be > 0.0 to be mono compatible
  REQUIRE(correlation > 0.5f);
}

TEST_CASE("Long note stability (Denormal flush)", "[render][qa]") {
  SynthEngine engine;
  engine.prepare(44100.0, 512);
  applyTestParams(engine);

  juce::AudioBuffer<float> block(2, 512);

  engine.processMidiEvent(36, 1.0f, true);
  engine.processBlock(block.getWritePointer(0), block.getWritePointer(1), 512);

  engine.processMidiEvent(36, 0.0f, false);

  // Process many blocks (release tail)
  for (int i = 0; i < 500; ++i) {
    engine.processBlock(block.getWritePointer(0), block.getWritePointer(1),
                        512);
  }

  // Tail should have decayed, flush to zero, no extreme small numbers
  // (denormals)
  auto *L = block.getReadPointer(0);
  for (int i = 0; i < 512; ++i) {
    REQUIRE(std::abs(L[i]) < 1e-4f);
    // If it's very small it should just be zero exactly due to flush
    if (std::abs(L[i]) > 0.0f) {
      REQUIRE(std::abs(L[i]) > 1e-15f); // Rough denormal floor boundary check
    }
  }
}

TEST_CASE("Preset load stress test", "[render][qa]") {
  SynthEngine engine;
  engine.prepare(44100.0, 512);

  juce::AudioBuffer<float> block(2, 512);
  engine.processMidiEvent(36, 1.0f, true);

  // Simulate setting arbitrary weird parameters very fast while rendering
  for (int i = 0; i < 10; ++i) {
    applyTestParams(engine, [i](ResolvedParams &map) {
      map.filterCutoff = 100.0f + (static_cast<float>(i) * 1000.0f);
      map.foldDrive = (i % 2 == 0) ? 1.0f : 0.0f;
      map.subTransientEnv = 1.0f;
    });

    // This validates the setParameters / engine sync does not crash or emit
    // NaNs
    engine.processBlock(block.getWritePointer(0), block.getWritePointer(1),
                        512);

    auto *L = block.getReadPointer(0);
    for (int s = 0; s < 512; ++s) {
      REQUIRE(!std::isnan(L[s]));
      REQUIRE(!std::isinf(L[s]));
    }
  }
}
