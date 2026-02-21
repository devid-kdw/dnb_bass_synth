#include "PluginEditor.h"
#include "PluginProcessor.h"

DnBBassSynthAudioProcessorEditor::DnBBassSynthAudioProcessorEditor(
    DnBBassSynthAudioProcessor &p)
    : AudioProcessorEditor(&p), audioProcessor(p) {
  addAndMakeVisible(mainLayout);
  setSize(800, 600);

  // Initialize standard bindings tying the UI strictly to Domain/APVTS
  // parameters
  bindingLayer = std::make_unique<dnb_bass::ui::BindingLayer>(
      audioProcessor.getApvts(), mainLayout.getMacroPanel(),
      mainLayout.getStyleMorphControl(), mainLayout.getStyleSelector());
}

DnBBassSynthAudioProcessorEditor::~DnBBassSynthAudioProcessorEditor() = default;

void DnBBassSynthAudioProcessorEditor::paint(juce::Graphics &g) {
  // Painting is handled by child components recursively via MainLayout
  juce::ignoreUnused(g, audioProcessor);
}

void DnBBassSynthAudioProcessorEditor::resized() {
  mainLayout.setBounds(getLocalBounds());
}
