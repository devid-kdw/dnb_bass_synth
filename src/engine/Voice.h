#pragma once

#include "../domain/ConstraintEngine.h"
#include "../domain/DnBLimits.h"
#include "../dsp/dist/Saturator.h"
#include "../dsp/dist/Wavefolder.h"
#include "../dsp/filters/CrossoverLR4.h"
#include "../dsp/filters/StateVariableFilter.h"
#include "../dsp/osc/CharacterOscillator.h"
#include "../dsp/osc/SubOscillator.h"
#include <algorithm>
#include <cmath>
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

    currentParams = defaultResolvedParams();
    setParameters(currentParams);

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
    subOsc.resetPhase(currentParams.subPhase);
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

  void setParameters(const domain::ResolvedParams &params) {
    currentParams = params;
    crossover.setFrequency(params.xoverFreq);
    charOsc.setFMRatio(params.fmRatio);
    charOsc.setFMDepth(std::clamp(0.2f + (params.distAmount * 0.6f), 0.0f, 1.0f));

    const float drive = 1.0f + (params.distAmount * 5.0f) + (params.ottDepth * 2.0f);
    saturator.setParameters(dsp::dist::Saturator::Type::SoftClip, drive);

    const float safeCutoff = std::clamp(params.filterCutoff, 40.0f, 8000.0f);
    const float resonance = std::clamp(0.15f + params.ottDepth * 0.6f, 0.0f, 0.95f);
    svf.setParameters(dsp::filters::StateVariableFilter::Mode::LowPass, safeCutoff,
                      resonance);
  }

  void processBlock(float *subOut, float *charOut, size_t numSamples) {
    if (state == State::Idle) {
      for (size_t i = 0; i < numSamples; ++i) {
        subOut[i] = 0.0f;
        charOut[i] = 0.0f;
      }
      return;
    }

    // A fast block-level envelope to prevent harsh clicking, driven by domain
    // params. Ensure we don't divide by zero if a parameter somehow bypasses
    // domain clamp.
    float safeAttack = std::max(0.1f, currentParams.ampAttack);
    float safeRelease = std::max(1.0f, currentParams.ampRelease);
    float attackIncr =
        1.0f / static_cast<float>(sampleRate * (safeAttack / 1000.0f));
    float releaseDecr =
        1.0f / static_cast<float>(sampleRate * (safeRelease / 1000.0f));

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

      // Macro/style-controlled tone shaping on character path.
      charS = svf.process(charS);
      const float ottDrive = 1.0f + (currentParams.ottDepth * 5.0f);
      const float ottWet = currentParams.ottDepth;
      const float ottProcessed = std::tanh(charS * ottDrive);
      charS = (charS * (1.0f - ottWet)) + (ottProcessed * ottWet);

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
  static domain::ResolvedParams defaultResolvedParams() {
    return domain::ResolvedParams{
        dnb::domain::limits::defaultAttackMs,
        dnb::domain::limits::defaultReleaseMs,
        dnb::domain::limits::subPhaseLockDeg,
        dnb::domain::limits::defaultCrossoverHz,
        dnb::domain::limits::defaultFMRatio,
        dnb::domain::limits::defaultOttMix,
        1000.0f,
        0.0f};
  }

  double sampleRate = 44100.0;
  State state = State::Idle;
  int currentNote = -1;
  float currentVelocity = 0.0f;
  float envVal = 0.0f;

  domain::ResolvedParams currentParams;

  dsp::osc::SubOscillator subOsc;
  dsp::osc::CharacterOscillator charOsc;
  dsp::filters::CrossoverLR4 crossover;
  dsp::filters::StateVariableFilter svf;
  dsp::dist::Saturator saturator;
  dsp::dist::Wavefolder wavefolder;
  std::vector<float> charBuffer;
};

} // namespace dnb::engine
