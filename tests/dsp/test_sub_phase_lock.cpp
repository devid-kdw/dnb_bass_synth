#include "../../src/dsp/osc/SubOscillator.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using namespace dnb::dsp::osc;

TEST_CASE("SubOscillator has deterministic phase", "[dsp][osc]") {
  SubOscillator sub;
  sub.prepare(44100.0);
  sub.setFrequency(50.0f); // Typical sub freq

  SECTION("Resetting phase to 0 yields 0.0 on next sample") {
    sub.resetPhase(0.0f);

    // At exactly phase 0, sin(0) == 0
    float firstSample = sub.process();
    REQUIRE_THAT(firstSample, Catch::Matchers::WithinAbs(0.0f, 0.001f));

    // Next sample will be positive
    float nextSample = sub.process();
    REQUIRE(nextSample > 0.0f);
  }

  SECTION("Resetting phase guarantees identical output blocks") {
    std::vector<float> block1(100);
    std::vector<float> block2(100);

    // Gen block 1
    sub.resetPhase(0.0f);
    for (int i = 0; i < 100; ++i)
      block1[i] = sub.process();

    // Gen block 2
    sub.resetPhase(0.0f);
    for (int i = 0; i < 100; ++i)
      block2[i] = sub.process();

    // Compare
    for (int i = 0; i < 100; ++i) {
      REQUIRE(block1[i] == block2[i]);
    }
  }
}
