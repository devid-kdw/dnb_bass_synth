#include "../../src/domain/ConstraintEngine.h"
#include <catch2/catch_test_macros.hpp>

using namespace dnb::domain;

TEST_CASE("Style modes restrict unaccepted parameter modifications",
          "[domain][style]") {
  ConstraintEngine engine;
  RawInputParams input;

  SECTION("Tech mode doesn't allow FM Metal scaling") {
    input.activeStyle = style::Mode::Tech;
    input.macroFmMetal = 1.0f;
    auto out = engine.process(input);
    // Tech mode doesn't enable FM Metal
    REQUIRE(out.fmRatio == limits::defaultFMRatio);
  }

  SECTION("Dark mode allows FM Metal scaling") {
    input.activeStyle = style::Mode::Dark;
    input.macroFmMetal = 1.0f;
    auto out = engine.process(input);
    REQUIRE(out.fmRatio == limits::allowedFMRatios.back());
  }
}
