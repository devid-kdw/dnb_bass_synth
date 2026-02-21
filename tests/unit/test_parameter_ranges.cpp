#include "../../src/domain/ConstraintEngine.h"
#include "../../src/domain/DnBLimits.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using namespace dnb::domain;

TEST_CASE("Envelope clamping respects min/max thresholds", "[domain][limits]") {
  SECTION("Attack limits") {
    REQUIRE(limits::clampAttack(-1.0f) == limits::minAttackMs);
    REQUIRE(limits::clampAttack(10.0f) == limits::maxAttackMs);
    REQUIRE(limits::clampAttack(2.0f) == 2.0f);
  }

  SECTION("Release limits") {
    REQUIRE(limits::clampRelease(0.0f) == limits::minReleaseMs);
    REQUIRE(limits::clampRelease(1000.0f) == limits::maxReleaseMs);
    REQUIRE(limits::clampRelease(150.0f) == 150.0f);
  }
}

TEST_CASE("DSP Critical values are completely locked", "[domain][limits]") {
  REQUIRE(limits::subPhaseLockDeg == 0.0f);

  SECTION("Crossover freq limits") {
    REQUIRE(limits::clampCrossover(50.0f) == 80.0f);
    REQUIRE(limits::clampCrossover(200.0f) == 150.0f);
  }
}

TEST_CASE("FM Ratio snaps to nearest valid harmonic", "[domain][limits]") {
  REQUIRE_THAT(limits::snapFMRatio(1.1f),
               Catch::Matchers::WithinAbs(1.00f, 0.01f));
  REQUIRE_THAT(limits::snapFMRatio(1.4f),
               Catch::Matchers::WithinAbs(1.41f, 0.01f));
  REQUIRE_THAT(limits::snapFMRatio(9.0f),
               Catch::Matchers::WithinAbs(8.23f, 0.01f));
}
