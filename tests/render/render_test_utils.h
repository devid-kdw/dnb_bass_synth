#pragma once
#include "../../src/engine/SynthEngine.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_dsp/juce_dsp.h>

using namespace dnb::engine;
using namespace dnb::domain;

// Utilities for render tests
inline void applyTestParams(SynthEngine &engine,
                            std::function<void(ResolvedParams &)> mutator = nullptr) {
  ResolvedParams params;

  // Default safe baseline for tests
  params.filterCutoff = 1000.0f;
  params.fmRatio = 1.41f;
  params.fmDepth = 0.5f;
  params.subTransientEnv = 0.5f;
  params.subPhase = 0.0f;
  params.distAmount = 0.0f;

  if (mutator) {
    mutator(params);
  }
  engine.setParameters(params);
}
