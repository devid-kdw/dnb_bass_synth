#pragma once

#include "../core/Oversampler.h"
#include "../core/SanityCheck.h"
#include <algorithm>
#include <cmath>

namespace dnb::dsp::dist {

// Dedicated sine-based wavefolder, extremely common in neurofunk FM basses.
class Wavefolder {
public:
  Wavefolder() = default;

  void prepare(double newSampleRate, size_t maxBlockSize) {
    sampleRate = newSampleRate;
    os.prepare(sampleRate, core::Oversampler::Factor::x4, maxBlockSize);
  }

  // Fold amount is typically 1.0 (none) to 10.0+ (extreme)
  void setFold(float newFold) { fold = newFold; }

  void processBlock(float *buffer, size_t numSamples) {
    if (fold <= 1.0f)
      return; // Passthrough if no folding

    // 1. Upsample
    float *oversampled = os.processUp(buffer, numSamples);
    size_t osSamples = numSamples * 4;

    // 2. Fold (Sine-function fold)
    float normalization = 1.0f / std::sin(fold);
    for (size_t i = 0; i < osSamples; ++i) {
      float s = oversampled[i];
      s = std::sin(s * fold) * normalization;
      oversampled[i] = s;
    }

    // 3. Downsample
    os.processDown(buffer, numSamples);

    // 4. Sanity
    for (size_t i = 0; i < numSamples; ++i) {
      core::SanityCheck::ensureSafe(buffer[i]);
    }
  }

private:
  double sampleRate = 44100.0;
  float fold = 1.0f;
  core::Oversampler os;
};

} // namespace dnb::dsp::dist
