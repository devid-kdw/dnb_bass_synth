#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <memory>

#include "../ui/bindings/BindingLayer.h"
#include "../ui/layout/MainLayout.h"

class DnBBassSynthAudioProcessor;

class DnBBassSynthAudioProcessorEditor final
    : public juce::AudioProcessorEditor {
public:
  explicit DnBBassSynthAudioProcessorEditor(DnBBassSynthAudioProcessor &);
  ~DnBBassSynthAudioProcessorEditor() override;

  void paint(juce::Graphics &g) override;
  void resized() override;

private:
  DnBBassSynthAudioProcessor &audioProcessor;

  dnb_bass::ui::MainLayout mainLayout;
  std::unique_ptr<dnb_bass::ui::BindingLayer> bindingLayer;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DnBBassSynthAudioProcessorEditor)
};
