#pragma once

#include "VoiceManager.h"
#include <algorithm>
#include <cmath>
#include <vector>

namespace dnb::engine {

// Top-level engine. Binds MIDI/domain interactions and dispatches them
// to the VoiceManager. Provides the primary audio generation loop.
class SynthEngine {
public:
  SynthEngine() = default;

  void prepare(double sampleRate, size_t maxBlockSize) {
    this->sampleRate = sampleRate;
    this->maxBlockSize = maxBlockSize;

    // We expect maxBlockSize around 256 for internal loop optimization
    subBuffer.resize(maxBlockSize, 0.0f);
    charBuffer.resize(maxBlockSize, 0.0f);

    voiceManager.prepare(sampleRate, maxBlockSize);
  }

  void processMidiEvent(int noteNumber, float velocity, bool isNoteOn) {
    if (isNoteOn) {
      voiceManager.noteOn(noteNumber, velocity);
    } else {
      voiceManager.noteOff(noteNumber);
    }
  }

  // Master processing block. Call this from the plugin processor.
  // Assumes a stereo output format where left and right are summed.
  void processBlock(float *outL, float *outR, size_t numSamples) {
    if (numSamples == 0)
      return;

    // Ensure we don't exceed max block size in the buffer
    size_t clampedSamples = std::min(numSamples, maxBlockSize);

    // Render underlying voice
    bool active = voiceManager.processBlock(subBuffer.data(), charBuffer.data(),
                                            clampedSamples);

    if (!active) {
      for (size_t i = 0; i < numSamples; ++i) {
        outL[i] = 0.0f;
        outR[i] = 0.0f;
      }
      return;
    }

    // Final Mix Stage
    // Sub is strictly dual-mono (identical in L/R).
    // Character could theoretically encompass stereo widened neuro effects
    // later, but right now we treat it as mono.

    // Simple mixing strategy
    float subGain = 1.0f;
    float charGain = 0.8f; // Mixed slightly lower

    for (size_t i = 0; i < clampedSamples; ++i) {
      float mix = (subBuffer[i] * subGain) + (charBuffer[i] * charGain);
      outL[i] = mix;
      outR[i] = mix;
    }

    // Graceful degradation / clearing out of bound tail
    for (size_t i = clampedSamples; i < numSamples; ++i) {
      outL[i] = 0.0f;
      outR[i] = 0.0f;
    }
  }

  // Minimal deterministic style morph state surface
  void startStyleMorph(float targetMorphValue) {
    targetStyleMorph = std::clamp(targetMorphValue, 0.0f, 1.0f);
    styleMorphActive = true;
  }

  void updateStyleMorphProgress() {
    if (!styleMorphActive)
      return;

    // Smooth transition logic to target
    float diff = targetStyleMorph - currentStyleMorph;
    if (std::abs(diff) < 0.001f) {
      currentStyleMorph = targetStyleMorph;
      styleMorphActive = false;
    } else {
      currentStyleMorph += diff * 0.05f; // simple smoothing factor
    }
  }

  [[nodiscard]] float getStyleMorph() const { return currentStyleMorph; }

  [[nodiscard]] bool isStyleMorphActive() const { return styleMorphActive; }

  void reset() {
    voiceManager.clear();
    currentStyleMorph = 0.0f;
    targetStyleMorph = 0.0f;
    styleMorphActive = false;
  }

private:
  double sampleRate = 44100.0;
  size_t maxBlockSize = 256;

  VoiceManager voiceManager;

  // Internal busses mapping to phase 3 guidelines
  std::vector<float> subBuffer;
  std::vector<float> charBuffer;

  // Style morph state
  float currentStyleMorph = 0.0f;
  float targetStyleMorph = 0.0f;
  bool styleMorphActive = false;
};

} // namespace dnb::engine
