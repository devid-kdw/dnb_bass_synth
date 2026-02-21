#pragma once

#include <cmath>

namespace dnb::dsp::core {

// Typical 1-pole parameter smoother to prevent zipper noise on macro updates.
class Smoother {
public:
  Smoother() = default;

  // Initializes the smoother with proper response time based on sample rate.
  // timeMs usually ranges from 5ms to 30ms for audio params.
  void prepare(double sampleRate, float timeMs) {
    // Calculate filter coefficient. Time is approx 63% settle time.
    // alpha = exp(-1.0 / (timeSeconds * sampleRate))
    if (timeMs <= 0.0f) {
      alpha = 0.0f;
    } else {
      alpha =
          static_cast<float>(std::exp(-1.0 / ((timeMs * 0.001f) * sampleRate)));
    }
  }

  void reset(float initialValue) {
    currentValue = initialValue;
    targetValue = initialValue;
  }

  void setTarget(float newTarget) { targetValue = newTarget; }

  // Processes one smoothing step and returns the smoothed value.
  [[nodiscard]] inline float process() {
    if (alpha == 0.0f || currentValue == targetValue) {
      currentValue = targetValue;
      return currentValue;
    }

    currentValue = targetValue + alpha * (currentValue - targetValue);

    // Snap to target if very close to avoid infinite tail calculation
    if (std::abs(currentValue - targetValue) < 1e-6f) {
      currentValue = targetValue;
    }

    return currentValue;
  }

  [[nodiscard]] inline float getCurrent() const { return currentValue; }

private:
  float alpha = 0.0f;
  float currentValue = 0.0f;
  float targetValue = 0.0f;
};

} // namespace dnb::dsp::core
