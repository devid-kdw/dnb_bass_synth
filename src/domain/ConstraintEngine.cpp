#include "ConstraintEngine.h"

namespace dnb::domain {

ResolvedParams ConstraintEngine::process(const RawInputParams &input) const {
  ResolvedParams out{};

  // 1. Get Style constraints
  const auto styleMods = style::getModifiersForStyle(input.activeStyle);

  // 2. Base envelope, strictly clamped
  out.ampAttack = limits::clampAttack(input.ampAttack);
  out.ampRelease = limits::clampRelease(input.ampRelease);

  // 3. Sub engine (Hard constraints, absolutely no bypass)
  out.subPhase = limits::subPhaseLockDeg;

  // 4. Macro processing
  const auto neuroOut = macros::applyNeuroFormant(input.macroNeuroFormant);
  const float fmRatioTarget = macros::applyFmMetal(input.macroFmMetal);
  const float liquidVal = macros::applyLiquidDepth(input.macroLiquidDepth);

  // Roller dynamics wiring (F-P5R2-001)
  const float rollerVal = macros::applyRollerDyn(input.macroRollerDynamics);

  out.filterCutoff = neuroOut.filterCutoffTarget;

  // Roller dynamics modulates the cutoff (provides energy/movement)
  // Shift by up to 1kHz
  out.filterCutoff += rollerVal * 2000.0f;

  // 5. Build outputs from macros with clamping
  out.xoverFreq = limits::clampCrossover(limits::defaultCrossoverHz +
                                         neuroOut.xoverFreqModifier);

  // 5a. Style mode gates (e.g. FM Metal is only active if the style allows
  // harsh dist)
  if (styleMods.enableFMMetal) {
    out.fmRatio = limits::snapFMRatio(fmRatioTarget);
  } else {
    out.fmRatio = limits::defaultFMRatio;
  }

  out.distAmount = neuroOut.distAmount;

  // 5b. Liquid depth modifies character path
  if (liquidVal > 0.0f) {
    // Tame highs, reduce dist
    out.distAmount *= (1.0f - liquidVal * 0.5f);
    out.filterCutoff *= (1.0f - liquidVal * 0.3f);
  }

  // 6. Clamp OTT based on style modifier cap
  out.ottDepth = limits::clampOtt(
      std::min(neuroOut.ottDepthTarget, styleMods.maxOttDepth));

  return out;
}

} // namespace dnb::domain
