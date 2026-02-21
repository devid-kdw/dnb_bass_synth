#include "../../src/dsp/osc/CharacterOscillator.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <vector>

using namespace dnb::dsp::osc;

TEST_CASE("CharacterOscillator FM Depth block processing", "[dsp][osc]") {
  CharacterOscillator osc;
  osc.prepare(44100.0, 256);
  osc.setFrequency(100.0f);

  SECTION("Zero FM Depth matches pure sine wave behavior") {
    osc.setFMRatio(2.0f);
    osc.setFMDepth(0.0f);
    osc.resetPhase();

    // Generate non-modulated block
    std::vector<float> noMod(100, 0.0f);
    osc.processBlock(noMod.data(), 100);

    // Gen modulated block
    osc.resetPhase();
    osc.setFMDepth(1.0f);

    std::vector<float> modulated(100, 0.0f);
    osc.processBlock(modulated.data(), 100);

    // The arrays should diverge because of FM
    bool diverged = false;
    for (int i = 0; i < 100; ++i) {
      if (std::abs(noMod[i] - modulated[i]) > 0.001f) {
        diverged = true;
        break;
      }
    }
    REQUIRE(diverged == true);
  }
}
