#include "../../src/domain/ConstraintEngine.h"
#include <catch2/catch_test_macros.hpp>

using namespace dnb::domain;

TEST_CASE("Macro changes respect constraints engine constraints",
          "[domain][macros]") {
  ConstraintEngine engine;
  RawInputParams input;

  SECTION("Neuro Formant macro affects distortion and cutoff") {
    input.macroNeuroFormant = 1.0f; // Max
    auto out = engine.process(input);
    REQUIRE(out.distAmount > 0.0f);
    REQUIRE(out.filterCutoff > 1000.0f);
  }

  // Liquid Depth reduces distortion and filter cutoff
  SECTION("Liquid Depth modifies character path") {
    input.macroNeuroFormant = 1.0f;
    auto baseOut = engine.process(input);

    input.macroLiquidDepth = 1.0f;
    auto liquidOut = engine.process(input);

    REQUIRE(liquidOut.distAmount < baseOut.distAmount);
    REQUIRE(liquidOut.filterCutoff < baseOut.filterCutoff);
  }

  SECTION("Sub Punch modifies transient envelope") {
    input.macroSubPunch = 1.0f;
    auto out = engine.process(input);
    REQUIRE(out.subTransientEnv == 1.0f);
  }

  SECTION("Cutoff Motion expands filter movement") {
    auto baseOut = engine.process(input);
    input.macroCutoffMotion = 1.0f;
    auto activeOut = engine.process(input);
    REQUIRE(activeOut.filterCutoff > baseOut.filterCutoff);
  }

  SECTION("FM Pressure responds to style mode progression") {
    input.macroFmMetal = 1.0f; // FM Metal must be active to allow pressure
    input.macroFmPressure = 1.0f;

    // Tech allows minimal FM pressure
    input.activeStyle = style::Mode::Tech;
    auto techOut = engine.process(input);
    REQUIRE(techOut.fmDepth > 0.0f);

    // Neuro allows standard FM pressure
    input.activeStyle = style::Mode::Neuro;
    auto neuroOut = engine.process(input);
    REQUIRE(neuroOut.fmDepth > techOut.fmDepth);

    // Dark allows highest FM pressure ceiling
    input.activeStyle = style::Mode::Dark;
    auto darkOut = engine.process(input);
    REQUIRE(darkOut.fmDepth > neuroOut.fmDepth);

    // If Metal isn't active, pressure is muted regardless of pressure input
    RawInputParams mutedInput;
    mutedInput.activeStyle = style::Mode::Dark; // Would normally allow it
    mutedInput.macroFmMetal = 0.0f;             // But disabled here
    mutedInput.macroFmPressure = 1.0f;

    auto mutedOut = engine.process(mutedInput);
    REQUIRE(mutedOut.fmDepth == 0.0f);
  }

  SECTION("Fold Bite is clamped by Neuro and Dark styles") {
    input.macroFoldBite = 1.0f;

    input.activeStyle = style::Mode::Neuro;
    auto neuroOut = engine.process(input);
    REQUIRE(neuroOut.foldDrive > 0.0f);

    input.activeStyle = style::Mode::Dark;
    auto darkOut = engine.process(input);
    REQUIRE(darkOut.foldDrive > 0.0f);

    // Tech limits fold heavily or mutes it based on engine implementation
    input.activeStyle = style::Mode::Tech;
    auto techOut = engine.process(input);
    REQUIRE(techOut.foldDrive < neuroOut.foldDrive);
  }

  SECTION("Table Drift adds position modulation") {
    input.macroTableDrift = 1.0f;
    auto out = engine.process(input);
    REQUIRE(out.tablePositionMod > 0.0f);
  }

  SECTION("Smash Glue increases compression mix") {
    auto baseOut = engine.process(input);
    input.macroSmashGlue = 1.0f;
    auto out = engine.process(input);
    REQUIRE(out.ottDepth > baseOut.ottDepth);
  }
}
