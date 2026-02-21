#include "../../src/domain/ConstraintEngine.h"
#include <catch2/catch_test_macros.hpp>

using namespace dnb::domain;

TEST_CASE("P5 Round 2: Style Mode Mapping Evidence", "[domain][style]") {
  ConstraintEngine engine;
  RawInputParams input;

  SECTION("Tech mode is deterministic and bounded") {
    input.activeStyle = style::Mode::Tech;
    auto out = engine.process(input);
    // Tech mode uses default FM ratio (1.41)
    REQUIRE(out.fmRatio == limits::defaultFMRatio);
  }

  SECTION("Dark mode is deterministic and bounded") {
    input.activeStyle = style::Mode::Dark;
    input.macroFmMetal = 1.0f;
    auto out = engine.process(input);
    // Dark mode allows FM Metal to reach max
    REQUIRE(out.fmRatio > 1.41f);
  }
}

TEST_CASE("P5 Round 2: Roller Dynamics Effect Evidence", "[domain][macros]") {
  ConstraintEngine engine;
  RawInputParams input;

  SECTION("macro.roller_dynamics modifies filter mapping") {
    input.macroRollerDynamics = 0.0f;
    auto out0 = engine.process(input);

    input.macroRollerDynamics = 1.0f;
    auto out1 = engine.process(input);

    // Roller dynamics should change the filter cutoff
    REQUIRE(out0.filterCutoff != out1.filterCutoff);
    REQUIRE(out1.filterCutoff > out0.filterCutoff);
  }
}
