#include "PluginProcessor.h"
#include "PluginEditor.h"

#include "../domain/ParameterSpec.h"
#include "../domain/StyleMode.h"
#include "../preset/PresetManager.h"
#include <algorithm>
#include <cmath>
#include <string>

DnBBassSynthAudioProcessor::DnBBassSynthAudioProcessor()
    : AudioProcessor(BusesProperties().withOutput("Output", juce::AudioChannelSet::stereo(), true)),
      apvts(*this, nullptr, "PARAMETERS", createParameterLayout()) {

  using namespace dnb::domain::parameters;
  styleModeParam = apvts.getRawParameterValue(std::string(styleMode.id));
  attackParam = apvts.getRawParameterValue(std::string(ampAttack.id));
  releaseParam = apvts.getRawParameterValue(std::string(ampRelease.id));

  macroNeuroFormantParam = apvts.getRawParameterValue(std::string(macroNeuroFormant.id));
  macroFmMetalParam = apvts.getRawParameterValue(std::string(macroFmMetal.id));
  macroRollerDynParam = apvts.getRawParameterValue(std::string(macroRollerDyn.id));
  macroLiquidDepthParam = apvts.getRawParameterValue(std::string(macroLiquidDepth.id));
  macroStyleMorphParam = apvts.getRawParameterValue(std::string(macroStyleMorph.id));
  macroSubPunchParam = apvts.getRawParameterValue(std::string(macroSubPunch.id));
  macroFmPressureParam = apvts.getRawParameterValue(std::string(macroFmPressure.id));
  macroCutoffMotionParam = apvts.getRawParameterValue(std::string(macroCutoffMotion.id));
  macroFoldBiteParam = apvts.getRawParameterValue(std::string(macroFoldBite.id));
  macroTableDriftParam = apvts.getRawParameterValue(std::string(macroTableDrift.id));
  macroSmashGlueParam = apvts.getRawParameterValue(std::string(macroSmashGlue.id));
}

DnBBassSynthAudioProcessor::~DnBBassSynthAudioProcessor() = default;

void DnBBassSynthAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {
  synthEngine.prepare(sampleRate, static_cast<size_t>(samplesPerBlock));
}

void DnBBassSynthAudioProcessor::releaseResources() {}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DnBBassSynthAudioProcessor::isBusesLayoutSupported(const BusesLayout &layouts) const {
  return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::mono() ||
         layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}
#endif

void DnBBassSynthAudioProcessor::processBlock(juce::AudioBuffer<float> &buffer,
                                              juce::MidiBuffer &midiMessages) {
  juce::ScopedNoDenormals noDenormals;

  // 1. Parameter Mapping (RT-Safe, no allocations)
  dnb::domain::RawInputParams rawParams;
  if (styleModeParam != nullptr) {
    const int styleIndex = std::clamp(static_cast<int>(styleModeParam->load()),
                                      static_cast<int>(dnb::domain::style::Mode::Tech),
                                      static_cast<int>(dnb::domain::style::Mode::Dark));
    rawParams.activeStyle = static_cast<dnb::domain::style::Mode>(styleIndex);
  }
  if (attackParam != nullptr) {
    rawParams.ampAttack = attackParam->load();
  }
  if (releaseParam != nullptr) {
    rawParams.ampRelease = releaseParam->load();
  }
  if (macroNeuroFormantParam != nullptr) {
    rawParams.macroNeuroFormant = macroNeuroFormantParam->load();
  }
  if (macroFmMetalParam != nullptr) {
    rawParams.macroFmMetal = macroFmMetalParam->load();
  }
  if (macroRollerDynParam != nullptr) {
    rawParams.macroRollerDynamics = macroRollerDynParam->load();
  }
  if (macroLiquidDepthParam != nullptr) {
    rawParams.macroLiquidDepth = macroLiquidDepthParam->load();
  }
  if (macroStyleMorphParam != nullptr) {
    const float currentTarget = macroStyleMorphParam->load();
    if (std::abs(synthEngine.getStyleMorph() - currentTarget) > 0.001f) {
      synthEngine.startStyleMorph(currentTarget);
    }
  }
  if (macroSubPunchParam != nullptr) {
    rawParams.macroSubPunch = macroSubPunchParam->load();
  }
  if (macroFmPressureParam != nullptr) {
    rawParams.macroFmPressure = macroFmPressureParam->load();
  }
  if (macroCutoffMotionParam != nullptr) {
    rawParams.macroCutoffMotion = macroCutoffMotionParam->load();
  }
  if (macroFoldBiteParam != nullptr) {
    rawParams.macroFoldBite = macroFoldBiteParam->load();
  }
  if (macroTableDriftParam != nullptr) {
    rawParams.macroTableDrift = macroTableDriftParam->load();
  }
  if (macroSmashGlueParam != nullptr) {
    rawParams.macroSmashGlue = macroSmashGlueParam->load();
  }

  // Update style morph target based on some logic or leave as is if no style
  // switch UI exists yet. For now, feed the macros to constraint engine
  dnb::domain::ResolvedParams resolvedParams = constraintEngine.process(rawParams);

  // Set parameters to the engine (this cascades through VoiceManager to Voice)
  synthEngine.setParameters(resolvedParams);

  // Allow engine to progress any style morph state smoothly
  synthEngine.updateStyleMorphProgress();

  // 2. MIDI processing
  for (const auto meta : midiMessages) {
    const auto msg = meta.getMessage();
    if (msg.isNoteOn()) {
      synthEngine.processMidiEvent(msg.getNoteNumber(), msg.getFloatVelocity(), true);
    } else if (msg.isNoteOff()) {
      synthEngine.processMidiEvent(msg.getNoteNumber(), 0.0f, false);
    }
  }

  // 3. Audio generation
  auto *outL = buffer.getWritePointer(0);
  auto *outR = buffer.getNumChannels() > 1 ? buffer.getWritePointer(1) : nullptr;

  if (outR != nullptr) {
    synthEngine.processBlock(outL, outR, buffer.getNumSamples());
  } else {
    // Mono fallback
    synthEngine.processBlock(outL, outL, buffer.getNumSamples());
  }

  // UI meter feed (lock-free): smoothed output level for visual scope overlay.
  double sumSq = 0.0;
  const int n = buffer.getNumSamples();
  if (n > 0) {
    if (outR != nullptr) {
      for (int i = 0; i < n; ++i) {
        const float mono = 0.5f * (outL[i] + outR[i]);
        sumSq += static_cast<double>(mono * mono);
      }
    } else {
      for (int i = 0; i < n; ++i) {
        sumSq += static_cast<double>(outL[i] * outL[i]);
      }
    }

    const float rms = static_cast<float>(std::sqrt(sumSq / static_cast<double>(n)));
    const float normalized = juce::jlimit(0.0f, 1.0f, rms * 4.0f);
    const float prev = uiOutputLevel.load(std::memory_order_relaxed);
    uiOutputLevel.store((prev * 0.82f) + (normalized * 0.18f), std::memory_order_relaxed);
  } else {
    const float prev = uiOutputLevel.load(std::memory_order_relaxed);
    uiOutputLevel.store(prev * 0.9f, std::memory_order_relaxed);
  }

  // Clear any extra output channels that the synth engine doesn't write to
  const auto outputChannels = getTotalNumOutputChannels();
  for (auto channel = 2; channel < outputChannels; ++channel) {
    buffer.clear(channel, 0, buffer.getNumSamples());
  }
}

juce::AudioProcessorEditor *DnBBassSynthAudioProcessor::createEditor() {
  return new DnBBassSynthAudioProcessorEditor(*this);
}

bool DnBBassSynthAudioProcessor::hasEditor() const {
  return true;
}

const juce::String DnBBassSynthAudioProcessor::getName() const {
  return JucePlugin_Name;
}

bool DnBBassSynthAudioProcessor::acceptsMidi() const {
  return true;
}

bool DnBBassSynthAudioProcessor::producesMidi() const {
  return false;
}

bool DnBBassSynthAudioProcessor::isMidiEffect() const {
  return false;
}

double DnBBassSynthAudioProcessor::getTailLengthSeconds() const {
  return 0.0;
}

int DnBBassSynthAudioProcessor::getNumPrograms() {
  return 1;
}

int DnBBassSynthAudioProcessor::getCurrentProgram() {
  return 0;
}

void DnBBassSynthAudioProcessor::setCurrentProgram(int) {}

const juce::String DnBBassSynthAudioProcessor::getProgramName(int) {
  return {};
}

void DnBBassSynthAudioProcessor::changeProgramName(int, const juce::String &) {}

void DnBBassSynthAudioProcessor::getStateInformation(juce::MemoryBlock &destData) {
  dnb::preset::PresetManager::saveStateInformation(apvts, destData);
}

void DnBBassSynthAudioProcessor::setStateInformation(const void *data, int sizeInBytes) {
  dnb::preset::PresetManager::loadStateInformation(data, sizeInBytes, apvts);
}

juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter() {
  return new DnBBassSynthAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout
DnBBassSynthAudioProcessor::createParameterLayout() {
  juce::AudioProcessorValueTreeState::ParameterLayout layout;

  using namespace dnb::domain::parameters;

  // Style Mode
  layout.add(std::make_unique<juce::AudioParameterChoice>(
      juce::ParameterID{juce::String(std::string(styleMode.id)), 1},
      juce::String(std::string(styleMode.name)), juce::StringArray{"Tech", "Neuro", "Dark"},
      static_cast<int>(styleMode.defaultVal)));

  // Envelope
  layout.add(std::make_unique<juce::AudioParameterFloat>(
      juce::ParameterID{juce::String(std::string(ampAttack.id)), 1},
      juce::String(std::string(ampAttack.name)),
      juce::NormalisableRange<float>(ampAttack.minVal, ampAttack.maxVal, 0.1f),
      ampAttack.defaultVal));

  layout.add(std::make_unique<juce::AudioParameterFloat>(
      juce::ParameterID{juce::String(std::string(ampRelease.id)), 1},
      juce::String(std::string(ampRelease.name)),
      juce::NormalisableRange<float>(ampRelease.minVal, ampRelease.maxVal, 1.0f),
      ampRelease.defaultVal));

  // Macros
  layout.add(std::make_unique<juce::AudioParameterFloat>(
      juce::ParameterID{juce::String(std::string(macroNeuroFormant.id)), 1},
      juce::String(std::string(macroNeuroFormant.name)),
      juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.0f));

  layout.add(std::make_unique<juce::AudioParameterFloat>(
      juce::ParameterID{juce::String(std::string(macroFmMetal.id)), 1},
      juce::String(std::string(macroFmMetal.name)),
      juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.0f));

  layout.add(std::make_unique<juce::AudioParameterFloat>(
      juce::ParameterID{juce::String(std::string(macroRollerDyn.id)), 1},
      juce::String(std::string(macroRollerDyn.name)),
      juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.0f));

  layout.add(std::make_unique<juce::AudioParameterFloat>(
      juce::ParameterID{juce::String(std::string(macroLiquidDepth.id)), 1},
      juce::String(std::string(macroLiquidDepth.name)),
      juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.0f));

  layout.add(std::make_unique<juce::AudioParameterFloat>(
      juce::ParameterID{juce::String(std::string(macroStyleMorph.id)), 1},
      juce::String(std::string(macroStyleMorph.name)),
      juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.0f));

  layout.add(std::make_unique<juce::AudioParameterFloat>(
      juce::ParameterID{juce::String(std::string(macroSubPunch.id)), 1},
      juce::String(std::string(macroSubPunch.name)),
      juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.0f));

  layout.add(std::make_unique<juce::AudioParameterFloat>(
      juce::ParameterID{juce::String(std::string(macroFmPressure.id)), 1},
      juce::String(std::string(macroFmPressure.name)),
      juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.0f));

  layout.add(std::make_unique<juce::AudioParameterFloat>(
      juce::ParameterID{juce::String(std::string(macroCutoffMotion.id)), 1},
      juce::String(std::string(macroCutoffMotion.name)),
      juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.0f));

  layout.add(std::make_unique<juce::AudioParameterFloat>(
      juce::ParameterID{juce::String(std::string(macroFoldBite.id)), 1},
      juce::String(std::string(macroFoldBite.name)),
      juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.0f));

  layout.add(std::make_unique<juce::AudioParameterFloat>(
      juce::ParameterID{juce::String(std::string(macroTableDrift.id)), 1},
      juce::String(std::string(macroTableDrift.name)),
      juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.0f));

  layout.add(std::make_unique<juce::AudioParameterFloat>(
      juce::ParameterID{juce::String(std::string(macroSmashGlue.id)), 1},
      juce::String(std::string(macroSmashGlue.name)),
      juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.0f));

  return layout;
}
