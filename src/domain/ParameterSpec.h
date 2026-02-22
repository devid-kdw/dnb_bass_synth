#pragma once

#include <string_view>

namespace dnb::domain::parameters {

struct ParamDesc {
  std::string_view id;
  std::string_view name;
  float minVal;
  float maxVal;
  float defaultVal;
  bool isDiscrete;
};

// Global Style Category
constexpr ParamDesc styleMode{"style.mode", "Style Mode", 0.0f, 2.0f, 0.0f, true};

// Sub Engine
constexpr ParamDesc subShape{"sub.shape", "Sub Osc Shape", 0.0f, 1.0f, 0.0f, true};
constexpr ParamDesc subPhase{"sub.phase", "Sub Phase Lck", 0.0f, 0.0f, 0.0f, true};

// Envelope
constexpr ParamDesc ampAttack{"env.amp.att", "Amp Attack", 0.0f, 5.0f, 2.0f, false};
constexpr ParamDesc ampRelease{"env.amp.rel", "Amp Release", 10.0f, 300.0f, 150.0f, false};

// Character Engine
constexpr ParamDesc xoverFreq{"sys.xover", "Mid/Side Cross", 80.0f, 150.0f, 120.0f, false};
constexpr ParamDesc fmRatio{"osc.fm.ratio", "FM Ratio", 1.0f, 8.23f, 1.41f, true};
constexpr ParamDesc ottMix{"fx.ott.mix", "OTT Depth", 0.0f, 0.60f, 0.15f, false};

// Macros (Normalized 0.0 to 1.0)
constexpr ParamDesc macroNeuroFormant{
    "macro.neuro_formant", "Neuro-Formant", 0.0f, 1.0f, 0.0f, false};
constexpr ParamDesc macroFmMetal{"macro.fm_metal", "FM Metal", 0.0f, 1.0f, 0.0f, false};
constexpr ParamDesc macroRollerDyn{
    "macro.roller_dynamics", "Roller Dynamics", 0.0f, 1.0f, 0.0f, false};
constexpr ParamDesc macroLiquidDepth{"macro.liquid_depth", "Liquid Depth", 0.0f, 1.0f, 0.0f, false};
constexpr ParamDesc macroStyleMorph{"macro.style_morph", "Style Morph", 0.0f, 1.0f, 0.0f, false};
constexpr ParamDesc macroSubPunch{"macro.sub_punch", "Sub Punch", 0.0f, 1.0f, 0.0f, false};
constexpr ParamDesc macroFmPressure{"macro.fm_pressure", "FM Pressure", 0.0f, 1.0f, 0.0f, false};
constexpr ParamDesc macroCutoffMotion{
    "macro.cutoff_motion", "Cutoff Motion", 0.0f, 1.0f, 0.0f, false};
constexpr ParamDesc macroFoldBite{"macro.fold_bite", "Fold Bite", 0.0f, 1.0f, 0.0f, false};
constexpr ParamDesc macroTableDrift{"macro.table_drift", "Table Drift", 0.0f, 1.0f, 0.0f, false};
constexpr ParamDesc macroSmashGlue{"macro.smash_glue", "Smash Glue", 0.0f, 1.0f, 0.0f, false};

} // namespace dnb::domain::parameters
