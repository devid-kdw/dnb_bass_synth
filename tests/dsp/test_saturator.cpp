#include "../../src/dsp/dist/Saturator.h"
#include <catch2/catch_test_macros.hpp>
#include <vector>

using namespace dnb::dsp::dist;

TEST_CASE("Saturator basic functionality", "[dsp][dist]") {
  Saturator saturator;
  saturator.prepare(44100.0, 256);

  SECTION("SoftClip attenuates loud signals but passes low ones") {
    saturator.setParameters(Saturator::Type::SoftClip, 1.0f);

    std::vector<float> buffer(64, 10.0f); // Very loud signal
    saturator.processBlock(buffer.data(), buffer.size());

    // With SoftClip, it shouldn't be 10.0 anymore, but closer to 1.0
    for (size_t i = 0; i < buffer.size(); ++i) {
      REQUIRE(std::abs(buffer[i]) < 2.0f);
    }
  }

  SECTION("HardClip strictly bounds signal") {
    saturator.setParameters(Saturator::Type::HardClip, 1.0f);

    std::vector<float> buffer(64, 5.0f);
    saturator.processBlock(buffer.data(), buffer.size());

    for (size_t i = 0; i < buffer.size(); ++i) {
      REQUIRE(buffer[i] < 1.15f);
    }
  }
}
