#include "../../src/domain/ConstraintEngine.h"
#include <catch2/catch_test_macros.hpp>

using namespace dnb::domain;

TEST_CASE("Style modes keep FM Metal bounded per style profile", "[domain][style]") {
  ConstraintEngine engine;
  RawInputParams input;

  SECTION("Tech mode keeps FM Metal in a controlled range") {
    input.activeStyle = style::Mode::Tech;
    input.macroFmMetal = 1.0f;
    auto out = engine.process(input);
    REQUIRE(out.fmRatio == limits::allowedFMRatios[3]);
  }

  SECTION("Neuro mode expands FM Metal range vs Tech") {
    input.activeStyle = style::Mode::Neuro;
    input.macroFmMetal = 1.0f;
    auto out = engine.process(input);
    REQUIRE(out.fmRatio == limits::allowedFMRatios[4]);
  }

  SECTION("Dark mode unlocks full FM Metal range") {
    input.activeStyle = style::Mode::Dark;
    input.macroFmMetal = 1.0f;
    auto out = engine.process(input);
    REQUIRE(out.fmRatio == limits::allowedFMRatios.back());
  }

  SECTION("FM Metal at zero stays on default curated ratio in every style") {
    input.macroFmMetal = 0.0f;

    input.activeStyle = style::Mode::Tech;
    REQUIRE(engine.process(input).fmRatio == limits::defaultFMRatio);

    input.activeStyle = style::Mode::Neuro;
    REQUIRE(engine.process(input).fmRatio == limits::defaultFMRatio);

    input.activeStyle = style::Mode::Dark;
    REQUIRE(engine.process(input).fmRatio == limits::defaultFMRatio);
  }
}
