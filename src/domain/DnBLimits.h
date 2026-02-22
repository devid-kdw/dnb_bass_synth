#pragma once

#include <algorithm>
#include <array>
#include <cmath>

namespace dnb::domain::limits {

// 1. Core Envelope Constraints
constexpr float minAttackMs = 0.0f;
constexpr float maxAttackMs = 5.0f;
constexpr float defaultAttackMs = 2.0f;

constexpr float minReleaseMs = 10.0f;
constexpr float maxReleaseMs = 300.0f;
constexpr float defaultReleaseMs = 150.0f;

// 2. Sub Engine Constraints
constexpr float subPhaseLockDeg = 0.0f; // Fixed, no deviation allowed per spec
enum class SubShape { Sine = 0, Triangle = 1 };

// 3. Crossover & Mono Policy
constexpr float minCrossoverHz = 80.0f;
constexpr float maxCrossoverHz = 150.0f;
constexpr float defaultCrossoverHz = 120.0f;

// 4. FM Ratios (Curated Inharmonic Set)
constexpr std::array<float, 6> allowedFMRatios = {
    1.00f, // Fundamental sync
    1.41f, // Squelch / Foghorn base
    2.33f, // Curated ratio
    3.15f, // Curated ratio
    7.10f, // Aggressive squelch
    8.23f  // Max limit per spec
};
constexpr float defaultFMRatio = 1.41f;

// 5. OTT / Dynamics
constexpr float minOttMix = 0.0f;
constexpr float maxOttMix = 0.60f;     // 60% limit
constexpr float defaultOttMix = 0.15f; // 15%

// 6. Filter Limits
constexpr float minCutoffHz = 40.0f;
constexpr float maxCutoffHz = 8000.0f;

// Helper functions for clamping/validation
inline float clampAttack(float value) {
  return std::clamp(value, minAttackMs, maxAttackMs);
}

inline float clampRelease(float value) {
  return std::clamp(value, minReleaseMs, maxReleaseMs);
}

inline float clampCrossover(float value) {
  return std::clamp(value, minCrossoverHz, maxCrossoverHz);
}

inline float clampOtt(float value) {
  return std::clamp(value, minOttMix, maxOttMix);
}

inline float clampCutoff(float value) {
  return std::clamp(value, minCutoffHz, maxCutoffHz);
}

// Snaps arbitrary value to the nearest allowed FM ratio
inline float snapFMRatio(float value) {
  float closest = allowedFMRatios[0];
  float minDiff = std::abs(value - closest);
  for (float ratio : allowedFMRatios) {
    float diff = std::abs(value - ratio);
    if (diff < minDiff) {
      minDiff = diff;
      closest = ratio;
    }
  }
  return closest;
}

} // namespace dnb::domain::limits
