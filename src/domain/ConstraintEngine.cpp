#include "ConstraintEngine.h"
#include "DnBLimits.h"

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
      std::min(neuroOut.ottDepthTarget + input.macroSmashGlue * 0.4f,
               styleMods.maxOttDepth));

  // 7. Macro 10 additions

  // 7.1 Cutoff Motion expands filter movement range
  out.filterCutoff += input.macroCutoffMotion * 3500.0f;

  // 7.2 Sub Punch creates transient energy and minor drive
  out.subTransientEnv = input.macroSubPunch;

  // 7.3 FM Pressure expands FM depth if FMMetal is active
  if (input.macroFmMetal > 0.01f) {
    out.fmDepth = input.macroFmPressure * 0.8f;

    // Scale Tech < Neuro < Dark
    if (input.activeStyle == style::Mode::Tech) {
      out.fmDepth *= 0.5f; // Tech allows minimal FM pressure
    } else if (input.activeStyle == style::Mode::Neuro) {
      out.fmDepth *= 1.0f; // Neuro allows standard
    } else if (input.activeStyle == style::Mode::Dark) {
      out.fmDepth *= 1.25f; // Dark allows highest ceiling
    }
  } else {
    out.fmDepth = 0.0f;
  }

  // 7.4 Fold Bite determines wavefolder drive, capped by style
  out.foldDrive = input.macroFoldBite * 0.8f;
  if (input.activeStyle == style::Mode::Tech) {
    out.foldDrive *= 0.5f; // Tech prefers cleaner wavefolding
  } else if (input.activeStyle == style::Mode::Dark) {
    out.foldDrive =
        std::min(1.0f, out.foldDrive * 1.5f); // Dark drives it harder
  }

  // 7.5 Table drift provides organic wavetable position offset
  out.tablePositionMod = input.macroTableDrift * 0.3f;
  if (input.activeStyle == style::Mode::Neuro) {
    out.tablePositionMod *= 1.5f; // Neuro encourages more spectral animation
  }

  // Final Safety Clamp for Computed Parameters (F-P6.1-002)
  out.filterCutoff = limits::clampCutoff(out.filterCutoff);

  return out;
}

} // namespace dnb::domain
