#pragma once

#include "DnBLimits.h"
#include <algorithm>

namespace dnb::domain::macros {

struct MacroOutputs {
  float xoverFreqModifier;
  float fmRatioTarget;
  float distAmount;
  float filterCutoffTarget;
  float ottDepthTarget;
};

// Maps 0.0-1.0 input from a macro to internal DSP changes, constrained
inline MacroOutputs applyNeuroFormant(float macroValue) {
  return {
      0.0f, // doesn't affect xover
      limits::defaultFMRatio,
      macroValue * 0.8f,              // Up to 80% dist
      1000.0f + macroValue * 4000.0f, // 1kHz to 5kHz
      macroValue * 0.3f               // Neuro adds some OTT depth
  };
}

inline float applyFmMetal(float macroValue) {
  // Maps 0.0-1.0 to curated FM ratios
  int index = static_cast<int>(macroValue * (limits::allowedFMRatios.size() - 1));
  return limits::allowedFMRatios[std::clamp(index, 0, (int)limits::allowedFMRatios.size() - 1)];
}

inline float applyLiquidDepth(float macroValue) {
  // Smoothes out highs, increases warmth (used later as multiplier)
  return macroValue;
}

inline float applyRollerDyn(float macroValue) {
  // Affects resonance and envelope depth
  return macroValue * 0.5f;
}

} // namespace dnb::domain::macros
