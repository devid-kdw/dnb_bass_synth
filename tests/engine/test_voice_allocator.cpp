#include "../../src/engine/VoiceManager.h"
#include <catch2/catch_test_macros.hpp>
#include <vector>

using namespace dnb::engine;

TEST_CASE("VoiceManager block processing and mono rules", "[engine]") {
  VoiceManager manager;
  manager.prepare(44100.0, 256);

  SECTION("Starts inactive") {
    std::vector<float> sub(64, 0.0f);
    std::vector<float> chars(64, 0.0f);
    bool active = manager.processBlock(sub.data(), chars.data(), 64);
    REQUIRE(active == false);
  }

  SECTION("Note On activates voice and processes sound") {
    manager.noteOn(60, 1.0f);

    std::vector<float> sub(64, 0.0f);
    std::vector<float> chars(64, 0.0f);
    bool active = manager.processBlock(sub.data(), chars.data(), 64);

    REQUIRE(active == true);

    // Voice should have produced some non-zero output if it's active
    bool generated = false;
    for (float s : sub) {
      if (std::abs(s) > 0.0001f) {
        generated = true;
        break;
      }
    }
    REQUIRE(generated == true);
  }

  SECTION("Legato behavior glides note smoothly") {
    manager.noteOn(60, 1.0f);

    // Simulate some frames passing
    std::vector<float> tempSub(64, 0.0f), tempChar(64, 0.0f);
    manager.processBlock(tempSub.data(), tempChar.data(), 64);

    // Trigger second note (legato)
    manager.noteOn(62, 1.0f);

    // Make sure voice remains active and doesn't get completely restarted
    // i.e., sub amplitude shouldn't drop to 0 instantaneously
    manager.processBlock(tempSub.data(), tempChar.data(), 64);
    REQUIRE(std::abs(tempSub[63]) > 0.0001f); // Still driving

    // Release 60, should stay on 62
    manager.noteOff(60);
    manager.processBlock(tempSub.data(), tempChar.data(), 64);

    // Output should still be active and non-zero because 62 is held
    bool active = manager.processBlock(tempSub.data(), tempChar.data(), 64);
    REQUIRE(active == true);
  }
}
