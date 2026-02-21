#pragma once

#include "../dsp/dist/Saturator.h"
#include "../dsp/dist/Wavefolder.h"
#include "../dsp/filters/CrossoverLR4.h"
#include "../dsp/filters/StateVariableFilter.h"
#include "../dsp/osc/CharacterOscillator.h"
#include "../dsp/osc/SubOscillator.h"
#include <vector>

namespace dnb::engine {

class Voice {
public:
  enum class State { Idle, Attack, Release };

  Voice() = default;

  void prepare(double newSampleRate, size_t maxBlockSize) {
    sampleRate = newSampleRate;

    subOsc.prepare(sampleRate);
    charOsc.prepare(sampleRate, maxBlockSize);
    crossover.prepare(sampleRate);
    svf.prepare(sampleRate);
    saturator.prepare(sampleRate, maxBlockSize);
    wavefolder.prepare(sampleRate, maxBlockSize);

    // Default routing params
    crossover.setFrequency(120.0f); // Default mono cutoff

    charBuffer.resize(maxBlockSize, 0.0f);

    state = State::Idle;
    envVal = 0.0f;
  }

  void noteOn(int noteNumber, float velocity) {
    currentNote = noteNumber;
    currentVelocity = velocity;

    float freq = 440.0f * std::pow(2.0f, (noteNumber - 69.0f) / 12.0f);
    subOsc.setFrequency(freq);
    charOsc.setFrequency(freq);

    // Phase lock only on distinct note-on triggers (not legato morphs)
    subOsc.resetPhase();
    charOsc.resetPhase();

    state = State::Attack;
  }

  void updatePitch(int noteNumber) {
    currentNote = noteNumber;
    float freq = 440.0f * std::pow(2.0f, (noteNumber - 69.0f) / 12.0f);
    subOsc.setFrequency(freq);
    charOsc.setFrequency(freq);
  }

  void noteOff() { state = State::Release; }

  void processBlock(float *subOut, float *charOut, size_t numSamples) {
    if (state == State::Idle) {
      for (size_t i = 0; i < numSamples; ++i) {
        subOut[i] = 0.0f;
        charOut[i] = 0.0f;
      }
      return;
    }

    // A fast block-level envelope to prevent harsh clicking.
    float attackIncr = 1.0f / static_cast<float>(sampleRate * 0.005);  // 5ms
    float releaseDecr = 1.0f / static_cast<float>(sampleRate * 0.015); // 15ms

    // Run the block processors that support block processing
    // Character path needs intermediate buffer
    size_t clampedSamples = std::min(numSamples, charBuffer.size());

    charOsc.processBlock(charBuffer.data(), clampedSamples);

    // Optionally route through SVF/Wavefolder here. For now, just saturator.
    saturator.processBlock(charBuffer.data(), clampedSamples);

    for (size_t i = 0; i < clampedSamples; ++i) {
      // Env update
      if (state == State::Attack) {
        envVal += attackIncr;
        if (envVal >= 1.0f)
          envVal = 1.0f;
      } else if (state == State::Release) {
        envVal -= releaseDecr;
        if (envVal <= 0.0f) {
          envVal = 0.0f;
          state = State::Idle;
        }
      }

      float subS = subOsc.process();
      float charS = charBuffer[i];

      // Use crossover to high-pass the character band so it doesn't clash with
      // sub
      float dummyLow, charHigh;
      crossover.process(charS, dummyLow, charHigh);
      charS = charHigh;

      subOut[i] = subS * envVal * currentVelocity;
      charOut[i] = charS * envVal * currentVelocity;
    }

    // Fill remaining output with zero if numSamples > capacity
    for (size_t i = clampedSamples; i < numSamples; ++i) {
      subOut[i] = 0.0f;
      charOut[i] = 0.0f;
    }
  }

  [[nodiscard]] bool isActive() const { return state != State::Idle; }

  [[nodiscard]] int getNote() const { return currentNote; }

private:
  double sampleRate = 44100.0;
  State state = State::Idle;
  int currentNote = -1;
  float currentVelocity = 0.0f;
  float envVal = 0.0f;

  dsp::osc::SubOscillator subOsc;
  dsp::osc::CharacterOscillator charOsc;
  dsp::filters::CrossoverLR4 crossover;
  dsp::filters::StateVariableFilter svf;
  dsp::dist::Saturator saturator;
  dsp::dist::Wavefolder wavefolder;
  std::vector<float> charBuffer;
};

} // namespace dnb::engine
