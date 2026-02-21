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
}
