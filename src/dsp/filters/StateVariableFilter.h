#pragma once

#include "../core/DenormalFlush.h"
#include <algorithm>
#include <cmath>

namespace dnb::dsp::filters {

// Multi-mode SVF based on Andrew Simper's algorithm.
// Critical for morphing Neuro formant shapes.
class StateVariableFilter {
public:
  enum class Mode { LowPass, HighPass, BandPass, Notch };

  StateVariableFilter() = default;

  void prepare(double newSampleRate) {
    sampleRate = newSampleRate;
    reset();
  }

  void reset() {
    z1 = 0.0f;
    z2 = 0.0f;
  }

  void setParameters(Mode newMode, float cutoffFreq, float resonance) {
    mode = newMode;

    // Clamp properties to maintain stability
    if (cutoffFreq > sampleRate * 0.49)
      cutoffFreq = static_cast<float>(sampleRate * 0.49);
    if (cutoffFreq < 20.0f)
      cutoffFreq = 20.0f;

    // Filter formulas (linear TP-SVF mapping)
    float g = std::tan(static_cast<float>(M_PI) * cutoffFreq /
                       static_cast<float>(sampleRate));
    float R = std::max(0.0f, 1.0f - resonance);

    a1 = 1.0f / (1.0f + g * (g + 2.0f * R));
    a2 = g * a1;
    a3 = g * a2;

    m0 = 1.0f;
    m1 = 2.0f * R;
    m2 = 1.0f;
  }

  [[nodiscard]] inline float process(float input) {
    // TPT SVF topology
    float v3 = input - z2;
    float v1 = a1 * z1 + a2 * v3;
    float v2 = z2 + a2 * z1 + a3 * v3;

    z1 = 2.0f * v1 - z1;
    z2 = 2.0f * v2 - z2;

    core::ScopedDenormalFlush::flush(z1);
    core::ScopedDenormalFlush::flush(z2);

    switch (mode) {
    case Mode::LowPass:
      return v2;
    case Mode::HighPass:
      return input - v1 * m1 - v2 * m0; // input - BP*2R - LP
    case Mode::BandPass:
      return v1;
    case Mode::Notch:
      return input - v1 * m1; // input - BP*2R
    default:
      return input;
    }
  }

private:
  double sampleRate = 44100.0;
  Mode mode = Mode::LowPass;

  // Coeffs and state
  float a1 = 0.0f, a2 = 0.0f, a3 = 0.0f;
  float m0 = 1.0f, m1 = 0.0f, m2 = 0.0f;
  float z1 = 0.0f, z2 = 0.0f;
};

} // namespace dnb::dsp::filters
