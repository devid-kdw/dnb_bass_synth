#pragma once

#include <atomic>
#include <juce_audio_processors/juce_audio_processors.h>

#include "../domain/ConstraintEngine.h"
#include "../engine/SynthEngine.h"

class DnBBassSynthAudioProcessor final : public juce::AudioProcessor {
public:
  DnBBassSynthAudioProcessor();
  ~DnBBassSynthAudioProcessor() override;

  void prepareToPlay(double sampleRate, int samplesPerBlock) override;
  void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
  bool isBusesLayoutSupported(const BusesLayout &layouts) const override;
#endif

  void processBlock(juce::AudioBuffer<float> &, juce::MidiBuffer &) override;

  juce::AudioProcessorEditor *createEditor() override;
  bool hasEditor() const override;

  const juce::String getName() const override;
  bool acceptsMidi() const override;
  bool producesMidi() const override;
  bool isMidiEffect() const override;
  double getTailLengthSeconds() const override;

  int getNumPrograms() override;
  int getCurrentProgram() override;
  void setCurrentProgram(int index) override;
  const juce::String getProgramName(int index) override;
  void changeProgramName(int index, const juce::String &newName) override;

  void getStateInformation(juce::MemoryBlock &destData) override;
  void setStateInformation(const void *data, int sizeInBytes) override;

  juce::AudioProcessorValueTreeState &getApvts() { return apvts; }

private:
  static juce::AudioProcessorValueTreeState::ParameterLayout
  createParameterLayout();

  juce::AudioProcessorValueTreeState apvts;

  dnb::domain::ConstraintEngine constraintEngine;
  dnb::engine::SynthEngine synthEngine;

  // Cached parameter pointers for RT-safe access
  std::atomic<float> *attackParam = nullptr;
  std::atomic<float> *releaseParam = nullptr;
  std::atomic<float> *macroNeuroFormantParam = nullptr;
  std::atomic<float> *macroFmMetalParam = nullptr;
  std::atomic<float> *macroRollerDynParam = nullptr;
  std::atomic<float> *macroLiquidDepthParam = nullptr;
  std::atomic<float> *macroStyleMorphParam = nullptr;
  std::atomic<float> *macroSubPunchParam = nullptr;
  std::atomic<float> *macroFmPressureParam = nullptr;
  std::atomic<float> *macroCutoffMotionParam = nullptr;
  std::atomic<float> *macroFoldBiteParam = nullptr;
  std::atomic<float> *macroTableDriftParam = nullptr;
  std::atomic<float> *macroSmashGlueParam = nullptr;
  std::atomic<float> *styleModeParam = nullptr;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DnBBassSynthAudioProcessor)
};
