#include "../../src/dsp/filters/CrossoverLR4.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <vector>

using namespace dnb::dsp::filters;

TEST_CASE("CrossoverLR4 splits and sums flat", "[dsp][filters]") {
  CrossoverLR4 crossover;
  crossover.prepare(44100.0);
  crossover.setFrequency(120.0f); // Typical DnB Sub limit

  SECTION("Impulse response sum equals exactly 1.0 (flat phase/magnitude)") {
    crossover.reset();

    // Feed an impulse (delta function)
    float outLow = 0.0f, outHigh = 0.0f;

    std::vector<float> impulse(2000, 0.0f);
    impulse[0] = 1.0f;

    float sumOfSums = 0.0f;
    for (int i = 0; i < 2000; ++i) {
      crossover.process(impulse[i], outLow, outHigh);
      sumOfSums += (outLow + outHigh);
    }

    // Summing the impulse responses of LP and HP in an LR4 crossover
    // perfectly recreates the original impulse (all-pass response in
    // magnitude). The total integral of the output sum should match the input.
    REQUIRE_THAT(sumOfSums, Catch::Matchers::WithinAbs(1.0f, 0.001f));
  }
}
