#include "PluginProcessor.h"
#include "PluginEditor.h"

DnBBassSynthAudioProcessor::DnBBassSynthAudioProcessor()
    : AudioProcessor(BusesProperties().withOutput("Output", juce::AudioChannelSet::stereo(), true))
{
}

DnBBassSynthAudioProcessor::~DnBBassSynthAudioProcessor() = default;

void DnBBassSynthAudioProcessor::prepareToPlay(double, int)
{
}

void DnBBassSynthAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DnBBassSynthAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::mono()
        || layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}
#endif

void DnBBassSynthAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;

    const auto outputChannels = getTotalNumOutputChannels();
    for (auto channel = getTotalNumInputChannels(); channel < outputChannels; ++channel)
    {
        buffer.clear(channel, 0, buffer.getNumSamples());
    }
}

juce::AudioProcessorEditor* DnBBassSynthAudioProcessor::createEditor()
{
    return new DnBBassSynthAudioProcessorEditor(*this);
}

bool DnBBassSynthAudioProcessor::hasEditor() const
{
    return true;
}

const juce::String DnBBassSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DnBBassSynthAudioProcessor::acceptsMidi() const
{
    return true;
}

bool DnBBassSynthAudioProcessor::producesMidi() const
{
    return false;
}

bool DnBBassSynthAudioProcessor::isMidiEffect() const
{
    return false;
}

double DnBBassSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DnBBassSynthAudioProcessor::getNumPrograms()
{
    return 1;
}

int DnBBassSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DnBBassSynthAudioProcessor::setCurrentProgram(int)
{
}

const juce::String DnBBassSynthAudioProcessor::getProgramName(int)
{
    return {};
}

void DnBBassSynthAudioProcessor::changeProgramName(int, const juce::String&)
{
}

void DnBBassSynthAudioProcessor::getStateInformation(juce::MemoryBlock&)
{
}

void DnBBassSynthAudioProcessor::setStateInformation(const void*, int)
{
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DnBBassSynthAudioProcessor();
}
