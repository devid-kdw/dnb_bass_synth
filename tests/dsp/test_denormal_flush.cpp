#include "../../src/dsp/core/DenormalFlush.h"
#include <catch2/catch_test_macros.hpp>

using namespace dnb::dsp::core;

TEST_CASE("ScopedDenormalFlush behavior", "[dsp][core][safety]") {
  SECTION("RAII instantiates without crashing on any arch") {
    REQUIRE_NOTHROW([]() { ScopedDenormalFlush flushGuard; }());
  }

  SECTION("Scalar flush removes subnormals") {
    float normalVal = 1.0f;
    ScopedDenormalFlush::flush(normalVal);
    REQUIRE(normalVal == 1.0f);

    float subnormalVal = 1e-16f;
    ScopedDenormalFlush::flush(subnormalVal);
    REQUIRE(subnormalVal == 0.0f);

    float negSubnormalVal = -1e-16f;
    ScopedDenormalFlush::flush(negSubnormalVal);
    REQUIRE(negSubnormalVal == 0.0f);
  }
}
