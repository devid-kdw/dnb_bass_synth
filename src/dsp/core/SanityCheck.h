#pragma once

#include <cmath>

namespace dnb::dsp::core {

// Provides safety checks against NaNs and Infs.
// Should be used at the end of nonlinear blocks to prevent DSP crash/silence.
class SanityCheck {
public:
  // Checks if the given sample is a valid float. Replace with 0.0f if not.
  // Returns true if the value was safe, false if it was fixed.
  static inline bool ensureSafe(float &sample) {
    if (std::isnan(sample) || std::isinf(sample)) {
      sample = 0.0f;
      return false;
    }
    return true;
  }
};

} // namespace dnb::dsp::core
