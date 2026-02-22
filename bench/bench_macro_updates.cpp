#include "../src/domain/ConstraintEngine.h"
#include <benchmark/benchmark.h>

using namespace dnb::domain;

static void BM_ConstraintEngine_Process(benchmark::State &state) {
  ConstraintEngine engine;
  RawInputParams input;

  input.macroNeuroFormant = 0.3f;
  input.macroFmMetal = 0.8f;
  input.macroRollerDynamics = 0.9f;
  input.macroLiquidDepth = 0.2f;
  input.macroSubPunch = 0.7f;
  input.macroFmPressure = 0.6f;
  input.macroCutoffMotion = 0.4f;
  input.macroFoldBite = 0.5f;
  input.macroTableDrift = 0.3f;
  input.macroSmashGlue = 0.9f;
  input.activeStyle = style::Mode::Dark;

  for (auto _ : state) {
    // Change one parameter slightly to force re-evaluation if needed
    input.macroNeuroFormant = static_cast<float>(rand()) / RAND_MAX;

    benchmark::DoNotOptimize(engine.process(input));
  }
}

BENCHMARK(BM_ConstraintEngine_Process)->Unit(benchmark::kNanosecond);
BENCHMARK_MAIN();
