#include "../../src/dsp/core/Oversampler.h"
#include <catch2/catch_test_macros.hpp>

using namespace dnb::dsp::core;

TEST_CASE("Oversampler basic structure works", "[dsp][core]") {
  Oversampler os;
  os.prepare(44100.0, Oversampler::Factor::x2, 256);
  os.reset();

  SECTION("Up and Down sampling array ranges are safe") {
    std::vector<float> input(64, 1.0f);
    float *upsampled = os.processUp(input.data(), 64);

    // Downsample back
    std::vector<float> output(64, 0.0f);
    os.processDown(output.data(), 64);

    // Output should just match in this simplistic mock
    REQUIRE(output[0] == 1.0f);
    REQUIRE(output[63] == 1.0f);
  }
}
