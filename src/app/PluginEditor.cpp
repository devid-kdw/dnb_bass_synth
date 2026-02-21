#include "PluginEditor.h"
#include "PluginProcessor.h"

DnBBassSynthAudioProcessorEditor::DnBBassSynthAudioProcessorEditor(DnBBassSynthAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    setSize(640, 360);
}

DnBBassSynthAudioProcessorEditor::~DnBBassSynthAudioProcessorEditor() = default;

void DnBBassSynthAudioProcessorEditor::paint(juce::Graphics& g)
{
    juce::ignoreUnused(audioProcessor);

    g.fillAll(juce::Colour::fromRGB(18, 18, 18));
    g.setColour(juce::Colours::white);
    g.setFont(18.0f);
    g.drawFittedText("DnB Bass Synth (alignment baseline)", getLocalBounds(), juce::Justification::centred, 1);
}

void DnBBassSynthAudioProcessorEditor::resized()
{
}
