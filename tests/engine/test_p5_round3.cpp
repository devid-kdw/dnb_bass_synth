#include "../../src/domain/ConstraintEngine.h"
#include "../../src/engine/SynthEngine.h"
#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <cmath>
#include <vector>

namespace {

std::vector<float> renderWithRaw(const dnb::domain::RawInputParams &raw, size_t numSamples = 256) {
  dnb::domain::ConstraintEngine constraintEngine;
  dnb::engine::SynthEngine engine;
  engine.prepare(44100.0, numSamples);

  const auto resolved = constraintEngine.process(raw);
  engine.setParameters(resolved);
  engine.processMidiEvent(48, 1.0f, true);

  std::vector<float> left(numSamples, 0.0f);
  std::vector<float> right(numSamples, 0.0f);
  engine.processBlock(left.data(), right.data(), numSamples);
  return left;
}

std::vector<float> renderReleaseTail(const dnb::domain::RawInputParams &raw,
                                     size_t numSamples = 256) {
  dnb::domain::ConstraintEngine constraintEngine;
  dnb::engine::SynthEngine engine;
  engine.prepare(44100.0, numSamples);

  const auto resolved = constraintEngine.process(raw);
  engine.setParameters(resolved);
  engine.processMidiEvent(48, 1.0f, true);

  std::vector<float> preReleaseL(numSamples, 0.0f);
  std::vector<float> preReleaseR(numSamples, 0.0f);
  engine.processBlock(preReleaseL.data(), preReleaseR.data(), numSamples);

  engine.processMidiEvent(48, 0.0f, false);
  std::vector<float> releaseTailL(numSamples, 0.0f);
  std::vector<float> releaseTailR(numSamples, 0.0f);
  engine.processBlock(releaseTailL.data(), releaseTailR.data(), numSamples);
  return releaseTailL;
}

float absEnergy(const std::vector<float> &buffer, size_t start, size_t end) {
  const size_t safeStart = std::min(start, buffer.size());
  const size_t safeEnd = std::min(end, buffer.size());

  float sum = 0.0f;
  for (size_t i = safeStart; i < safeEnd; ++i) {
    sum += std::abs(buffer[i]);
  }
  return sum;
}

float diffEnergy(const std::vector<float> &a, const std::vector<float> &b) {
  const size_t n = std::min(a.size(), b.size());
  float sum = 0.0f;
  for (size_t i = 0; i < n; ++i) {
    sum += std::abs(a[i] - b[i]);
  }
  return sum;
}

} // namespace

TEST_CASE("P5 Round 3: style.mode impacts rendered audio", "[engine][p5][audio]") {
  dnb::domain::RawInputParams tech;
  tech.activeStyle = dnb::domain::style::Mode::Tech;
  tech.macroFmMetal = 1.0f;
  tech.macroNeuroFormant = 0.6f;

  auto dark = tech;
  dark.activeStyle = dnb::domain::style::Mode::Dark;

  const auto techRender = renderWithRaw(tech);
  const auto darkRender = renderWithRaw(dark);

  REQUIRE(diffEnergy(techRender, darkRender) > 0.01f);
}

TEST_CASE("P5 Round 3: envelope APVTS params impact rendered audio", "[engine][p5][audio]") {
  dnb::domain::RawInputParams fastAttack;
  fastAttack.ampAttack = dnb::domain::limits::minAttackMs;
  fastAttack.ampRelease = dnb::domain::limits::defaultReleaseMs;

  auto slowAttack = fastAttack;
  slowAttack.ampAttack = dnb::domain::limits::maxAttackMs;

  const auto fastAttackRender = renderWithRaw(fastAttack);
  const auto slowAttackRender = renderWithRaw(slowAttack);

  REQUIRE(absEnergy(fastAttackRender, 0, 16) > absEnergy(slowAttackRender, 0, 16));

  dnb::domain::RawInputParams shortRelease;
  shortRelease.ampAttack = dnb::domain::limits::minAttackMs;
  shortRelease.ampRelease = dnb::domain::limits::minReleaseMs;

  auto longRelease = shortRelease;
  longRelease.ampRelease = dnb::domain::limits::maxReleaseMs;

  const auto shortTail = renderReleaseTail(shortRelease);
  const auto longTail = renderReleaseTail(longRelease);

  REQUIRE(absEnergy(shortTail, 128, 256) < absEnergy(longTail, 128, 256));
}

TEST_CASE("P5 Round 3: macro.neuro_formant impacts rendered audio", "[engine][p5][audio]") {
  dnb::domain::RawInputParams low;
  low.macroNeuroFormant = 0.0f;

  auto high = low;
  high.macroNeuroFormant = 1.0f;

  const auto lowRender = renderWithRaw(low);
  const auto highRender = renderWithRaw(high);

  REQUIRE(diffEnergy(lowRender, highRender) > 0.01f);
}

TEST_CASE("P5 Round 3: macro.fm_metal impacts rendered audio", "[engine][p5][audio]") {
  dnb::domain::RawInputParams low;
  low.activeStyle = dnb::domain::style::Mode::Dark;
  low.macroFmMetal = 0.0f;

  auto high = low;
  high.macroFmMetal = 1.0f;

  const auto lowRender = renderWithRaw(low);
  const auto highRender = renderWithRaw(high);

  REQUIRE(diffEnergy(lowRender, highRender) > 0.01f);
}

TEST_CASE("P5 Round 3: macro.roller_dynamics impacts rendered audio", "[engine][p5][audio]") {
  dnb::domain::RawInputParams low;
  low.macroNeuroFormant = 0.8f;
  low.macroRollerDynamics = 0.0f;

  auto high = low;
  high.macroRollerDynamics = 1.0f;

  const auto lowRender = renderWithRaw(low);
  const auto highRender = renderWithRaw(high);

  REQUIRE(diffEnergy(lowRender, highRender) > 0.01f);
}

TEST_CASE("P5 Round 3: macro.liquid_depth impacts rendered audio", "[engine][p5][audio]") {
  dnb::domain::RawInputParams dry;
  dry.macroNeuroFormant = 1.0f;
  dry.macroLiquidDepth = 0.0f;

  auto wet = dry;
  wet.macroLiquidDepth = 1.0f;

  const auto dryRender = renderWithRaw(dry);
  const auto wetRender = renderWithRaw(wet);

  REQUIRE(diffEnergy(dryRender, wetRender) > 0.01f);
}

TEST_CASE("P6.1 Macro-10: macro.sub_punch impacts rendered audio", "[engine][p6][macro10][audio]") {
  dnb::domain::RawInputParams off;
  off.macroSubPunch = 0.0f;

  auto on = off;
  on.macroSubPunch = 1.0f;

  const auto offRender = renderWithRaw(off);
  const auto onRender = renderWithRaw(on);

  REQUIRE(diffEnergy(offRender, onRender) > 0.01f);
}

TEST_CASE("P6.1 Macro-10: macro.fm_pressure impacts rendered audio",
          "[engine][p6][macro10][audio]") {
  dnb::domain::RawInputParams off;
  off.activeStyle = dnb::domain::style::Mode::Dark; // Enable FM
  off.macroFmMetal = 1.0f;                          // Enable Metal
  off.macroFmPressure = 0.0f;

  auto on = off;
  on.macroFmPressure = 1.0f;

  const auto offRender = renderWithRaw(off);
  const auto onRender = renderWithRaw(on);

  REQUIRE(diffEnergy(offRender, onRender) > 0.01f);
}

TEST_CASE("P6.1 Macro-10: macro.cutoff_motion impacts rendered audio",
          "[engine][p6][macro10][audio]") {
  dnb::domain::RawInputParams off;
  off.macroNeuroFormant = 0.5f; // Gives base tone to filter
  off.macroCutoffMotion = 0.0f;

  auto on = off;
  on.macroCutoffMotion = 1.0f;

  const auto offRender = renderWithRaw(off);
  const auto onRender = renderWithRaw(on);

  REQUIRE(diffEnergy(offRender, onRender) > 0.01f);
}

TEST_CASE("P6.1 Macro-10: macro.fold_bite impacts rendered audio", "[engine][p6][macro10][audio]") {
  dnb::domain::RawInputParams off;
  off.activeStyle = dnb::domain::style::Mode::Neuro; // Encourages fold
  off.macroFoldBite = 0.0f;

  auto on = off;
  on.macroFoldBite = 1.0f;

  const auto offRender = renderWithRaw(off);
  const auto onRender = renderWithRaw(on);

  REQUIRE(diffEnergy(offRender, onRender) > 0.01f);
}

TEST_CASE("P6.1 Macro-10: macro.table_drift impacts rendered audio",
          "[engine][p6][macro10][audio]") {
  dnb::domain::RawInputParams off;
  off.macroTableDrift = 0.0f;

  auto on = off;
  on.macroTableDrift = 1.0f;

  const auto offRender = renderWithRaw(off);
  const auto onRender = renderWithRaw(on);

  REQUIRE(diffEnergy(offRender, onRender) > 0.01f);
}

TEST_CASE("P6.1 Macro-10: macro.smash_glue impacts rendered audio",
          "[engine][p6][macro10][audio]") {
  dnb::domain::RawInputParams off;
  off.macroNeuroFormant = 0.5f; // Add baseline OTT
  off.macroSmashGlue = 0.0f;

  auto on = off;
  on.macroSmashGlue = 1.0f;

  const auto offRender = renderWithRaw(off);
  const auto onRender = renderWithRaw(on);

  REQUIRE(diffEnergy(offRender, onRender) > 0.01f);
}
