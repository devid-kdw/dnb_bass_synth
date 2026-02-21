#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

class DnBBassSynthAudioProcessor;

class DnBBassSynthAudioProcessorEditor final : public juce::AudioProcessorEditor
{
public:
    explicit DnBBassSynthAudioProcessorEditor(DnBBassSynthAudioProcessor&);
    ~DnBBassSynthAudioProcessorEditor() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    DnBBassSynthAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DnBBassSynthAudioProcessorEditor)
};
