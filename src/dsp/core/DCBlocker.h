#pragma once

#include <cmath>

namespace dnb::dsp::core {

// A simplistic 1-pole high-pass filter specific to removing DC offsets
// resulting from heavy asymmetric distortion.
// Parameter R = 0.995 gives a cutoff around 22Hz at 44.1kHz.
class DCBlocker {
public:
  DCBlocker() = default;

  void reset() {
    xPrev = 0.0f;
    yPrev = 0.0f;
  }

  // Set the internal coefficient R directly.
  // Higher values lower the cutoff frequency (slower reaction to DC).
  void setCoefficient(float newR) { R = newR; }

  [[nodiscard]] inline float process(float x) {
    float y = x - xPrev + R * yPrev;

    // Denormal flush to prevent feedback noise tail spikes
    if (std::abs(y) < 1e-15f)
      y = 0.0f;

    xPrev = x;
    yPrev = y;
    return y;
  }

private:
  float xPrev = 0.0f;
  float yPrev = 0.0f;
  float R = 0.995f;
};

} // namespace dnb::dsp::core
