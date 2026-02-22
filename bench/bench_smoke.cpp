#include <benchmark/benchmark.h>

static void BM_Identity(benchmark::State &state) {
  for (auto _ : state) {
    benchmark::DoNotOptimize(1.0f);
  }
}

BENCHMARK(BM_Identity);
BENCHMARK_MAIN();
