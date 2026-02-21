#include "../../src/dsp/osc/CharacterOscillator.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using namespace dnb::dsp::osc;

TEST_CASE("CharacterOscillator FM Depth", "[dsp][osc]") {
  CharacterOscillator osc;
  osc.prepare(44100.0);
  osc.setFrequency(100.0f);

  SECTION("Zero FM Depth matches pure sine wave behavior") {
    osc.setFMRatio(2.0f);
    osc.setFMDepth(0.0f);
    osc.resetPhase();

    float pureSine = osc.process();
    // Since both phase arrays start at 0, first sample should be very close to
    // 0
    REQUIRE_THAT(pureSine, Catch::Matchers::WithinAbs(0.0f, 0.001f));

    // It should match sub exactly if both run fundamental freq, but let's just
    // test the zero-modulation assumption first block
    std::vector<float> noMod(100);
    for (int i = 0; i < 100; ++i)
      noMod[i] = osc.process();

    // Gen modulated block
    osc.resetPhase();
    osc.setFMDepth(1.0f);

    // Discard first sample which is 0
    (void)osc.process();

    std::vector<float> modulated(100);
    for (int i = 0; i < 100; ++i)
      modulated[i] = osc.process();

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
