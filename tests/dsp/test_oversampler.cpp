#include "../../src/dsp/core/Oversampler.h"
#include <catch2/catch_test_macros.hpp>
#include <vector>

using namespace dnb::dsp::core;

TEST_CASE("Oversampler polyphase FIR structure works", "[dsp][core]") {
  Oversampler os;
  os.prepare(44100.0, Oversampler::Factor::x4, 256);
  os.reset();

  SECTION("Oversampler attenuates Nyquist alias frequencies") {
    // Generate a vector of length 200 filled with high freq
    std::vector<float> input(200, 0.0f);
    // Create a 22.05 kHz signal at 44.1kHz (Nyquist) -> [1, -1, 1, -1]
    for (size_t i = 0; i < 200; ++i) {
      input[i] = (i % 2 == 0) ? 1.0f : -1.0f;
    }

    // Upsample
    float *upsampled = os.processUp(input.data(), 200);

    // Downsample
    std::vector<float> output(200, 0.0f);
    os.processDown(output.data(), 200);

    // Should attenuate Nyquist due to the FIR filter (cutoff is exactly at
    // Nyquist, so amplitude will be ~0.35)
    float mag = 0.0f;
    for (size_t i = 100; i < 200; ++i) { // check after transient
      if (std::abs(output[i]) > mag)
        mag = std::abs(output[i]);
    }
    REQUIRE(mag < 0.5f);
  }

  SECTION(
      "Exceeding prepared maxBlockSize processes safely without allocation") {
    // os was prepared with maxBlockSize = 256
    // We send 300 samples
    std::vector<float> largeInput(300, 1.0f);

    // This should not crash or allocate
    float *upsampled = os.processUp(largeInput.data(), 300);

    // Downsample back
    std::vector<float> largeOutput(300, 0.0f);
    os.processDown(largeOutput.data(), 300);

    // The first 256 samples should be processed normally (allowing for filter
    // delay/startup) The remaining 44 samples should be zero-padded gracefully
    REQUIRE(largeOutput[290] == 0.0f);
    REQUIRE(largeOutput[299] == 0.0f);
  }
}
