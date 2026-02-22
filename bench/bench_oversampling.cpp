#include "../src/dsp/core/Oversampler.h"
#include <benchmark/benchmark.h>
#include <juce_dsp/juce_dsp.h>

using namespace dnb::dsp::core;

static void BM_Oversampler_Process(benchmark::State &state) {
  Oversampler oversampler;
  size_t blockSize = 512;
  oversampler.prepare(44100.0, Oversampler::Factor::x2, blockSize);

  juce::AudioBuffer<float> block(1, static_cast<int>(blockSize));
  auto *channelData = block.getWritePointer(0);
  for (int i = 0; i < blockSize; ++i) {
    channelData[i] = std::sin(2.0f * juce::MathConstants<float>::pi * 440.0f * i / 44100.0f);
  }

  for (auto _ : state) {
    // Up-sample array
    float *upsampledData = oversampler.processUp(block.getReadPointer(0), blockSize);
    size_t upsampledLength = blockSize * 2;

    // Simulate nonlinear processing at 2x sample rate
    for (size_t i = 0; i < upsampledLength; ++i) {
      upsampledData[i] = std::tanh(upsampledData[i] * 2.0f);
    }

    // Down-sample back into original block
    oversampler.processDown(block.getWritePointer(0), blockSize);
    benchmark::ClobberMemory();
  }
}

BENCHMARK(BM_Oversampler_Process)->Unit(benchmark::kMicrosecond);
BENCHMARK_MAIN();
