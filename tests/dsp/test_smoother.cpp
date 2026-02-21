#include "../../src/dsp/core/Smoother.h"
#include <catch2/catch_test_macros.hpp>

using namespace dnb::dsp::core;

TEST_CASE("Smoother interpolates values", "[dsp][core]") {
  Smoother smoother;
  smoother.prepare(44100.0, 10.0f); // 10ms smooth
  smoother.reset(0.0f);

  SECTION("Smoothes toward target") {
    smoother.setTarget(1.0f);

    // Step 1
    float val1 = smoother.process();
    REQUIRE(val1 > 0.0f);
    REQUIRE(val1 < 1.0f);

    // Value after 441 samples (approx 10ms) should be roughly 0.63
    float valN = 0.0f;
    for (int i = 0; i < 441; ++i) {
      valN = smoother.process();
    }
    REQUIRE(valN > 0.60f);
    REQUIRE(valN < 0.66f);
  }
}
