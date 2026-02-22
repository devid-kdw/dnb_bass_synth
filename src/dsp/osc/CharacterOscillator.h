#pragma once

#include "../core/Oversampler.h"
#include <algorithm>
#include <cmath>

namespace dnb::dsp::osc {

// Generates the mid/high Character band. Implements simple Phase Modification /
// FM capabilities to provide metallic neuro/jump-up layers.
class CharacterOscillator {
public:
  CharacterOscillator() = default;

  void prepare(double newSampleRate, size_t maxBlockSize = 256) {
    sampleRate = newSampleRate;
    // According to D-001 FM path needs OS
    os.prepare(sampleRate, core::Oversampler::Factor::x4, maxBlockSize);
    updateIncrements();
  }

  void setFrequency(float newFrequency) {
    frequency = newFrequency;
    updateIncrements();
  }

  void setFMRatio(float newRatio) {
    fmRatio = newRatio;
    updateIncrements();
  }

  void updateIncrements() {
    // OS rate = sampleRate * 4
    double osRate = sampleRate * 4.0;
    phaseIncrement = static_cast<float>(frequency * (2.0 * M_PI / osRate));
    fmIncrement =
        static_cast<float>((frequency * fmRatio) * (2.0 * M_PI / osRate));
  }

  void setFMDepth(float newDepth) {
    fmDepth = std::clamp(newDepth, 0.0f, 1.0f);
  }

  void setPMDepth(float newDepth) {
    pmDepth = std::clamp(newDepth, 0.0f, 1.0f);
  }

  void resetPhase() {
    currentPhase = 0.0f;
    fmPhase = 0.0f;
    os.reset();
  }

  // Process a block natively generating 4x samples
  void processBlock(float *buffer, size_t numSamples) {
    if (numSamples == 0)
      return;

    size_t safeSamples = std::min(numSamples, os.getCapacity());
    float *oversampled = os.getUpBuffer();
    size_t osSamples = safeSamples * 4;

    for (size_t i = 0; i < osSamples; ++i) {
      // Modulator (Sine)
      float modulator = std::sin(fmPhase);

      // Add Table Drift Phase Modulation
      float pmOffset =
          std::sin(currentPhase * 0.5f) * pmDepth * static_cast<float>(M_PI);

      // Carrier
      float output = std::sin(currentPhase + pmOffset +
                              (modulator * fmDepth * static_cast<float>(M_PI)));

      // Tick phases
      currentPhase += phaseIncrement;
      if (currentPhase >= static_cast<float>(2.0 * M_PI)) {
        currentPhase -= static_cast<float>(2.0 * M_PI);
      }

      fmPhase += fmIncrement;
      if (fmPhase >= static_cast<float>(2.0 * M_PI)) {
        fmPhase -= static_cast<float>(2.0 * M_PI);
      }

      oversampled[i] = output;
    }

    os.processDown(buffer, numSamples);
  }

private:
  double sampleRate = 44100.0;
  float frequency = 440.0f;

  // Core phase tracking
  float currentPhase = 0.0f;
  float phaseIncrement = 0.0f;

  // FM params
  float fmRatio = 1.0f;
  float fmDepth = 0.0f;
  float fmPhase = 0.0f;
  float fmIncrement = 0.0f;

  // PM params (Table Drift)
  float pmDepth = 0.0f;

  core::Oversampler os;
};

} // namespace dnb::dsp::osc
