#include "../../src/dsp/core/SanityCheck.h"
#include <catch2/catch_test_macros.hpp>
#include <limits>

using namespace dnb::dsp::core;

TEST_CASE("SanityCheck ensures values are safe", "[dsp][core][safety]") {
  SECTION("Valid float remains unchanged") {
    float val = 0.5f;
    bool isSafe = SanityCheck::ensureSafe(val);
    REQUIRE(isSafe == true);
    REQUIRE(val == 0.5f);
  }

  SECTION("NaN is caught and replaced by 0.0f") {
    float val = std::numeric_limits<float>::quiet_NaN();
    bool isSafe = SanityCheck::ensureSafe(val);
    REQUIRE(isSafe == false);
    REQUIRE(val == 0.0f);
  }

  SECTION("Infinity is caught and replaced by 0.0f") {
    float val = std::numeric_limits<float>::infinity();
    bool isSafe = SanityCheck::ensureSafe(val);
    REQUIRE(isSafe == false);
    REQUIRE(val == 0.0f);

    float negVal = -std::numeric_limits<float>::infinity();
    bool isSafeNeg = SanityCheck::ensureSafe(negVal);
    REQUIRE(isSafeNeg == false);
    REQUIRE(negVal == 0.0f);
  }
}
