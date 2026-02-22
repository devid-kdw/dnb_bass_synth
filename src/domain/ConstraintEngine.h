#pragma once

#include "DnBLimits.h"
#include "MacroMap.h"
#include "StyleMode.h"

namespace dnb::domain {

// Represents the raw normalized inputs generally coming from the UI/Host.
// Unit semantics are frozen as:
// - macro/style controls: normalized UI space (0.0 to 1.0 or stepped enum)
// - attack/release: resolved UI units in milliseconds before domain clamp
struct RawInputParams {
  style::Mode activeStyle = style::Mode::Tech;

  // Envelopes (milliseconds)
  float ampAttack = limits::defaultAttackMs;
  float ampRelease = limits::defaultReleaseMs;

  // Macros (normalized 0.0 to 1.0)
  float macroNeuroFormant = 0.0f;
  float macroFmMetal = 0.0f;
  float macroLiquidDepth = 0.0f;
  float macroRollerDynamics = 0.0f;
  float macroSubPunch = 0.0f;
  float macroFmPressure = 0.0f;
  float macroCutoffMotion = 0.0f;
  float macroFoldBite = 0.0f;
  float macroTableDrift = 0.0f;
  float macroSmashGlue = 0.0f;
};

// Represents the fully sanitized, DSP-ready parameters
struct ResolvedParams {
  float ampAttack = 0.0f;
  float ampRelease = 0.0f;
  float subPhase = 0.0f;
  float xoverFreq = 0.0f;
  float fmRatio = 0.0f;
  float fmDepth = 0.0f;
  float ottDepth = 0.0f;
  float filterCutoff = 0.0f;
  float distAmount = 0.0f;
  float foldDrive = 0.0f;
  float subTransientEnv = 0.0f;
  float tablePositionMod = 0.0f;
};

// The central authority for the domain boundaries.
class ConstraintEngine {
public:
  ConstraintEngine() = default;

  // The single authority for resolving UI/host inputs to DSP-safe params
  [[nodiscard]] ResolvedParams process(const RawInputParams &input) const;
};

} // namespace dnb::domain
