#include "../../src/engine/NoteStack.h"
#include <catch2/catch_test_macros.hpp>

using namespace dnb::engine;

TEST_CASE("NoteStack basic functionality", "[engine]") {
  NoteStack stack;

  SECTION("Starts empty") {
    REQUIRE(stack.isEmpty() == true);
    REQUIRE(stack.isLegato() == false);
    REQUIRE(stack.getLatestNote().isActive == false);
  }

  SECTION("LIFO priority tracking") {
    stack.pushNote(60, 1.0f);
    REQUIRE(stack.isEmpty() == false);
    REQUIRE(stack.getLatestNote().noteNumber == 60);

    stack.pushNote(62, 0.8f);
    REQUIRE(stack.isLegato() == true);
    REQUIRE(stack.getLatestNote().noteNumber == 62); // Top priority

    // Pop latest, should revert to previous
    stack.popNote(62);
    REQUIRE(stack.isLegato() == false);
    REQUIRE(stack.getLatestNote().noteNumber == 60);

    // Pop old, should become empty
    stack.popNote(60);
    REQUIRE(stack.isEmpty() == true);
  }

  SECTION("Re-triggering same note pushes it to front") {
    stack.pushNote(60, 1.0f);
    stack.pushNote(62, 1.0f);
    REQUIRE(stack.getLatestNote().noteNumber == 62);

    stack.pushNote(60, 0.5f); // Hit 60 again
    REQUIRE(stack.getLatestNote().noteNumber == 60);
    REQUIRE(stack.getLatestNote().velocity == 0.5f);
  }

  SECTION("Clear stack works") {
    stack.pushNote(60, 1.0f);
    stack.pushNote(62, 1.0f);
    stack.clear();
    REQUIRE(stack.isEmpty() == true);
  }
}
