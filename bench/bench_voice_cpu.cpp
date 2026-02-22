#include "../src/engine/NoteStack.h"
#include "../src/engine/VoiceManager.h"
#include "../src/preset/PresetSchema.h"
#include <benchmark/benchmark.h>
#include <juce_audio_basics/juce_audio_basics.h>

using namespace dnb::engine;
using namespace dnb::domain;

static void BM_VoiceManager_ProcessBlock(benchmark::State &state) {
  VoiceManager manager;
  manager.prepare(44100.0, 512);

  // Create a mock resolved parameters object
  ResolvedParams params;

  // Simulate macro activity effects (resolved values)
  params.filterCutoff = 1000.0f;
  params.fmRatio = 1.41f;
  params.fmDepth = 0.9f;
  params.subTransientEnv = 0.8f;
  params.subPhase = 0.0f;
  params.distAmount = 1.0f;

  manager.setParameters(params);

  // Force voice active
  manager.noteOn(36, 1.0f);

  juce::AudioBuffer<float> block(2, 512);

  for (auto _ : state) {
    block.clear();
    benchmark::DoNotOptimize(manager.processBlock(
        block.getWritePointer(0), block.getWritePointer(1), 512));
    benchmark::ClobberMemory();
  }
}

BENCHMARK(BM_VoiceManager_ProcessBlock)->Unit(benchmark::kMicrosecond);
BENCHMARK_MAIN();
