#include "../../src/dsp/core/DCBlocker.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using namespace dnb::dsp::core;

TEST_CASE("DC Blocker removes DC offset", "[dsp][core]") {
  DCBlocker blocker;

  SECTION("Passes alternating signal relatively unaffected") {
    blocker.reset();
    REQUIRE_THAT(blocker.process(1.0f), Catch::Matchers::WithinAbs(1.0f, 0.01f));
    REQUIRE_THAT(blocker.process(-1.0f), Catch::Matchers::WithinAbs(-1.005f, 0.01f));
  }

  SECTION("Filters out massive DC") {
    blocker.reset();
    float output = 0.0f;
    for (int i = 0; i < 1000; ++i) {
      output = blocker.process(1.0f);
    }
    // After 1000 samples of 1.0 DC, the output should settle near 0
    REQUIRE(std::abs(output) < 0.01f);
  }
}
