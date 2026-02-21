#pragma once

#include <algorithm>
#include <cmath>

namespace dnb::dsp::osc {

// Generates the mid/high Character band. Implements simple Phase Modification /
// FM capabilities to provide metallic neuro/jump-up layers.
class CharacterOscillator {
public:
  CharacterOscillator() = default;

  void prepare(double newSampleRate) { sampleRate = newSampleRate; }

  void setFrequency(float newFrequency) {
    frequency = newFrequency;
    phaseIncrement = static_cast<float>(frequency * (2.0 * M_PI / sampleRate));
  }

  void setFMRatio(float newRatio) {
    fmRatio = newRatio;
    fmIncrement =
        static_cast<float>((frequency * fmRatio) * (2.0 * M_PI / sampleRate));
  }

  void setFMDepth(float newDepth) {
    fmDepth = std::clamp(newDepth, 0.0f, 1.0f);
  }

  void resetPhase() {
    currentPhase = 0.0f;
    fmPhase = 0.0f;
  }

  // Process a single sample
  [[nodiscard]] inline float process() {
    // Modulator (Sine)
    float modulator = std::sin(fmPhase);

    // Carrier (Sine with Phase Modulation).
    // FM Depth scaled by a constant to map [0,1] to useful PI modulation
    // depths.
    float output = std::sin(currentPhase +
                            (modulator * fmDepth * static_cast<float>(M_PI)));

    // Tick phases
    currentPhase += phaseIncrement;
    if (currentPhase >= static_cast<float>(2.0 * M_PI)) {
      currentPhase -= static_cast<float>(2.0 * M_PI);
    }

    fmPhase += fmIncrement;
    if (fmPhase >= static_cast<float>(2.0 * M_PI)) {
      fmPhase -= static_cast<float>(2.0 * M_PI);
    }

    return output;
  }

private:
  double sampleRate = 44100.0;
  float frequency = 440.0f;

  // Core phase tracking
  float currentPhase = 0.0f;
  float phaseIncrement = 0.0f;

  // FM params
  float fmRatio = 1.0f;
  float fmDepth = 0.0f;
  float fmPhase = 0.0f;
  float fmIncrement = 0.0f;
};

} // namespace dnb::dsp::osc
