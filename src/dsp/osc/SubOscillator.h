#pragma once

#include <cmath>
#include <numbers>

namespace dnb::dsp::osc {

// Generates the fundamental low frequencies. Must guarantee deterministic phase
// reset on note-on to ensure consistent low-end transient impact.
class SubOscillator {
public:
  SubOscillator() = default;

  void prepare(double newSampleRate) {
    sampleRate = newSampleRate;
  }

  void setFrequency(float newFrequency) {
    frequency = newFrequency;
    phaseIncrement = frequency * (kTwoPi / static_cast<float>(sampleRate));
  }

  // Forcefully locks the start phase (according to limits::subPhaseLockDeg).
  void resetPhase(float startPhaseDegrees = 0.0f) {
    currentPhase = startPhaseDegrees * (kPi / 180.0f);
  }

  // Process a single sample
  [[nodiscard]] inline float process() {
    // Simple Sine wave implementation
    float output = std::sin(currentPhase);

    currentPhase += phaseIncrement;
    if (currentPhase >= kTwoPi) {
      currentPhase -= kTwoPi;
    }

    return output;
  }

private:
  static constexpr float kPi = std::numbers::pi_v<float>;
  static constexpr float kTwoPi = 2.0f * kPi;

  double sampleRate = 44100.0;
  float frequency = 440.0f;
  float currentPhase = 0.0f;
  float phaseIncrement = 0.0f;
};

} // namespace dnb::dsp::osc
