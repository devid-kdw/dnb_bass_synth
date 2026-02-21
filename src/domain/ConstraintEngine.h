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
};

// Represents the fully sanitized, DSP-ready parameters
struct ResolvedParams {
  float ampAttack;
  float ampRelease;
  float subPhase; // Guaranteed to be locked
  float xoverFreq;
  float fmRatio; // Guaranteed to be inharmonic safe
  float ottDepth;
  float filterCutoff;
  float distAmount;
};

// The central authority for the domain boundaries.
class ConstraintEngine {
public:
  ConstraintEngine() = default;

  // The single authority for resolving UI/host inputs to DSP-safe params
  [[nodiscard]] ResolvedParams process(const RawInputParams &input) const;
};

} // namespace dnb::domain
