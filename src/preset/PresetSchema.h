#pragma once

#include <string_view>

#include "Config.h"

namespace dnb::preset {
namespace schema {

// Current version of the preset schema.
// This must be incremented when adding/removing parameters or changing
// parameter IDs in a backwards-incompatible way.
constexpr int currentVersion = 1;

// Base identifier for the preset XML tag
constexpr std::string_view presetTag = "DnBBassSynthState";
constexpr std::string_view versionAttr = "version";

// Use the overarching project version defined by CMake/ProJucer as single
// source of truth (G-P6P7-003)
constexpr std::string_view pluginVersion = dnb::config::pluginVersion;

} // namespace schema

// Stable canonical parameter IDs mapped directly to the P1/P5 frozen contract.
// These must NEVER be changed without a corresponding migration strategy.
namespace keys {

constexpr std::string_view styleMode = "style.mode";

// Envelope
constexpr std::string_view ampAttack = "env.amp.att";
constexpr std::string_view ampRelease = "env.amp.rel";

// Macros
constexpr std::string_view macroNeuroFormant = "macro.neuro_formant";
constexpr std::string_view macroFmMetal = "macro.fm_metal";
constexpr std::string_view macroRollerDynamics = "macro.roller_dynamics";
constexpr std::string_view macroLiquidDepth = "macro.liquid_depth";
constexpr std::string_view macroStyleMorph = "macro.style_morph";

} // namespace keys
} // namespace dnb::preset
