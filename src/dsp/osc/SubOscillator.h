#pragma once

#include <cmath>

namespace dnb::dsp::osc {

// Generates the fundamental low frequencies. Must guarantee deterministic phase
// reset on note-on to ensure consistent low-end transient impact.
class SubOscillator {
public:
  SubOscillator() = default;

  void prepare(double newSampleRate) { sampleRate = newSampleRate; }

  void setFrequency(float newFrequency) {
    frequency = newFrequency;
    phaseIncrement = static_cast<float>(frequency * (2.0 * M_PI / sampleRate));
  }

  // Forcefully locks the start phase (according to limits::subPhaseLockDeg).
  void resetPhase(float startPhaseDegrees = 0.0f) {
    currentPhase = startPhaseDegrees * static_cast<float>(M_PI / 180.0);
  }

  // Process a single sample
  [[nodiscard]] inline float process() {
    // Simple Sine wave implementation
    float output = std::sin(currentPhase);

    currentPhase += phaseIncrement;
    if (currentPhase >= static_cast<float>(2.0 * M_PI)) {
      currentPhase -= static_cast<float>(2.0 * M_PI);
    }

    return output;
  }

private:
  double sampleRate = 44100.0;
  float frequency = 440.0f;
  float currentPhase = 0.0f;
  float phaseIncrement = 0.0f;
};

} // namespace dnb::dsp::osc
