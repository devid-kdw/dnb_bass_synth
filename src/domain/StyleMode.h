#pragma once

#include <string_view>

namespace dnb::domain::style {

enum class Mode {
  Tech = 0, // Default, clean, techy
  Neuro,    // Aggressive phase, notch filters
  Dark      // Heavy dist, hard limits
};

inline std::string_view getModeName(Mode mode) {
  switch (mode) {
  case Mode::Tech:
    return "Tech";
  case Mode::Neuro:
    return "Neuro";
  case Mode::Dark:
    return "Dark";
  default:
    return "Unknown";
  }
}

// Struct to hold base parameter modifiers and caps per style
struct StyleModifiers {
  float maxOttDepth;
  float defaultAttack;
  bool allowHarshDistortion;
  int fmMetalMaxRatioIndex;
};

inline StyleModifiers getModifiersForStyle(Mode mode) {
  switch (mode) {
  case Mode::Tech:
    return {0.30f, 2.0f, false, 3};
  case Mode::Neuro:
    return {0.60f, 1.0f, true, 4};
  case Mode::Dark:
    return {0.60f, 0.0f, true, 5};
  default:
    return {0.30f, 2.0f, false, 3};
  }
}

} // namespace dnb::domain::style
