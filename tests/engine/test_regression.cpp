#include "../../src/engine/SynthEngine.h"
#include "../../src/engine/VoiceManager.h"
#include <catch2/catch_test_macros.hpp>
#include <vector>

using namespace dnb::engine;

TEST_CASE("Voice block truncation regression", "[engine][regression]") {
  VoiceManager manager;
  // Use a small maxBlockSize
  manager.prepare(44100.0, 256);

  SECTION("Processing a block larger than maxBlockSize doesn't throw or leave "
          "hard silence tail") {
    manager.noteOn(60, 1.0f);

    // Process 1024 samples, which is larger than maxBlockSize 256
    std::vector<float> sub(1500, 1.0f);
    std::vector<float> chars(1500, 1.0f);

    bool active = manager.processBlock(sub.data(), chars.data(), 1500);
    REQUIRE(active == true);

    // The first 256 samples should be processed normally
    // The remainder up to 1500 should be explicitly zero-padded
    REQUIRE(std::abs(sub[100]) >
            0.0f); // Sub wave starts from 0 phase, index 100 is non-zero
    REQUIRE(sub[256] == 0.0f);  // Padded tail starts here
    REQUIRE(sub[1499] == 0.0f); // Padded tail ends here

    REQUIRE(chars[256] == 0.0f);
    REQUIRE(chars[1499] == 0.0f);
  }
}

TEST_CASE("SynthEngine Style Morph Surface", "[engine]") {
  SynthEngine engine;
  engine.prepare(44100.0, 256);

  SECTION("Starts at zero") {
    REQUIRE(engine.getStyleMorph() == 0.0f);
    REQUIRE(engine.isStyleMorphActive() == false);
  }

  SECTION("Updates progress towards target") {
    engine.startStyleMorph(1.0f);
    REQUIRE(engine.isStyleMorphActive() == true);

    engine.updateStyleMorphProgress();
    REQUIRE(engine.getStyleMorph() > 0.0f);
    REQUIRE(engine.getStyleMorph() < 1.0f);
  }
}
