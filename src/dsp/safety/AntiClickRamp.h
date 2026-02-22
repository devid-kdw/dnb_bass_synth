#pragma once

#include <algorithm>
#include <cmath>

namespace dnb::dsp::safety {

// Provides a 0-2ms fade in when attack is set to 0, preventing digital clicks.
// Hard constraint for DnB DSP.
class AntiClickRamp {
public:
  AntiClickRamp() = default;

  void prepare(double sampleRate) {
    // Enforce a strict 2ms ramp for 0ms attacks
    rampLengthInSamples = static_cast<int>(std::ceil(0.002 * sampleRate));
    reset();
  }

  void reset() {
    currentSampleIndex = 0;
    isActive = true;
  }

  // Process a single sample
  [[nodiscard]] inline float process(float sample) {
    if (!isActive)
      return sample;

    if (currentSampleIndex >= rampLengthInSamples || rampLengthInSamples == 0) {
      isActive = false;
      return sample;
    }

    // Linear ramp up
    float multiplier =
        static_cast<float>(currentSampleIndex) / static_cast<float>(rampLengthInSamples);
    currentSampleIndex++;

    return sample * multiplier;
  }

  // Process a block/buffer in-place
  void processBlock(float *buffer, int numSamples) {
    for (int i = 0; i < numSamples; ++i) {
      buffer[i] = process(buffer[i]);
    }
  }

private:
  int rampLengthInSamples = 0;
  int currentSampleIndex = 0;
  bool isActive = false;
};

} // namespace dnb::dsp::safety
