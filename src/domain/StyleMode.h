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
    return "Neurofunk";
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
  bool enableFMMetal;
};

inline StyleModifiers getModifiersForStyle(Mode mode) {
  switch (mode) {
  case Mode::Tech:
    return {0.30f, 2.0f, false, false};
  case Mode::Neuro:
    return {0.60f, 1.0f, true, false};
  case Mode::Dark:
    return {0.60f, 0.0f, true, true};
  default:
    return {0.30f, 2.0f, false, false};
  }
}

} // namespace dnb::domain::style
