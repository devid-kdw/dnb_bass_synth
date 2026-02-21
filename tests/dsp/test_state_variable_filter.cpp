#include "../../src/dsp/filters/StateVariableFilter.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using namespace dnb::dsp::filters;

TEST_CASE("StateVariableFilter basic functionality", "[dsp][filters]") {
  StateVariableFilter svf;
  svf.prepare(44100.0);

  SECTION("LowPass mode attenuates high frequencies") {
    svf.setParameters(StateVariableFilter::Mode::LowPass, 1000.0f, 0.0f);
    svf.reset();

    // Generate alternating Nyquist signal
    for (int i = 0; i < 100; ++i) {
      float input = (i % 2 == 0) ? 1.0f : -1.0f;
      float output = svf.process(input);
      if (i > 50) {
        // High frequency should be significantly attenuated by 1kHz LPF
        REQUIRE(std::abs(output) < 0.1f);
      }
    }
  }

  SECTION("HighPass mode attenuates low frequencies") {
    svf.setParameters(StateVariableFilter::Mode::HighPass, 10000.0f, 0.0f);
    svf.reset();

    // Generate DC signal
    for (int i = 0; i < 100; ++i) {
      float output = svf.process(1.0f);
      if (i > 50) {
        // DC should be blocked completely by 10kHz HPF
        REQUIRE(std::abs(output) < 0.01f);
      }
    }
  }
}
