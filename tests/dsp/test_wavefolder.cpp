#include "../../src/dsp/dist/Wavefolder.h"
#include <catch2/catch_test_macros.hpp>
#include <vector>

using namespace dnb::dsp::dist;

TEST_CASE("Wavefolder basic functionality", "[dsp][dist]") {
  Wavefolder wavefolder;
  wavefolder.prepare(44100.0, 256);

  SECTION("Bypasses when fold <= 1.0f") {
    wavefolder.setFold(1.0f);

    std::vector<float> buffer(64, 0.5f);
    wavefolder.processBlock(buffer.data(), buffer.size());

    for (size_t i = 0; i < buffer.size(); ++i) {
      REQUIRE(buffer[i] == 0.5f);
    }
  }

  SECTION("Modifies signal when fold > 1.0f") {
    wavefolder.setFold(4.0f); // High folding amount

    std::vector<float> buffer(64, 0.8f);
    wavefolder.processBlock(buffer.data(), buffer.size());

    for (size_t i = 0; i < buffer.size(); ++i) {
      // It should be folded so it's not simply 0.8 anymore
      REQUIRE(buffer[i] != 0.8f);
    }
  }
}
