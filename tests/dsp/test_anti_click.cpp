#include "../../src/dsp/safety/AntiClickRamp.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using namespace dnb::dsp::safety;

TEST_CASE("Anti-Click Ramp behavior", "[dsp][safety]") {
  AntiClickRamp ramp;

  // 44100Hz -> 2ms is 88 samples
  ramp.prepare(44100.0);

  SECTION("Fades in from zero linearly over 2ms") {
    float firstSample = ramp.process(1.0f);
    REQUIRE(firstSample == 0.0f); // Index 0 gets 0 multiplier

    float nextSample = ramp.process(1.0f);
    REQUIRE(nextSample > 0.0f);
    REQUIRE(nextSample < 1.0f);
  }

  SECTION("Passes fully after 2ms") {
    // Skip 88 samples
    for (int i = 0; i < 100; ++i) {
      (void)ramp.process(1.0f);
    }

    float sampleAfterWait = ramp.process(1.0f);
    REQUIRE(sampleAfterWait == 1.0f);
  }
}
