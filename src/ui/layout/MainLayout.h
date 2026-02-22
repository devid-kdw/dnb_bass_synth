#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>

#include "../components/MacroPanel.h"
#include "../components/StyleMorphControl.h"
#include "../components/StyleSelector.h"
#include "../components/VisualFeedbackView.h"

namespace dnb_bass {
namespace ui {

// Top-level UI layout bridging all visual components
class MainLayout : public juce::Component {
public:
  MainLayout() {
    addAndMakeVisible(headerLabel);
    headerLabel.setText("DnB Bass Synth VST3", juce::dontSendNotification);
    headerLabel.setFont(juce::FontOptions(24.0f, juce::Font::bold));
    headerLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(styleSelector);
    addAndMakeVisible(styleMorph);
    addAndMakeVisible(visualFeedback);
    addAndMakeVisible(macroPanel);
  }

  void resized() override {
    auto bounds = getLocalBounds().reduced(20);

    // Header
    headerLabel.setBounds(bounds.removeFromTop(40));
    bounds.removeFromTop(10);

    // Style Selector
    styleSelector.setBounds(bounds.removeFromTop(30).withWidth(250).withX(
        bounds.getX() + (bounds.getWidth() - 250) / 2));
    bounds.removeFromTop(10);

    // Style Morph Slider
    styleMorph.setBounds(bounds.removeFromTop(70).withWidth(300).withX(
        bounds.getX() + (bounds.getWidth() - 300) / 2));
    bounds.removeFromTop(20);

    // Visual Feedback Area
    visualFeedback.setBounds(bounds.removeFromTop(120));
    bounds.removeFromTop(20);

    // Canonical MVP macros + Advanced Macros (10 Total)
    macroPanel.setBounds(bounds.removeFromTop(250));
  }

  void paint(juce::Graphics &g) override { g.fillAll(Theme::background); }

  StyleMorphControl &getStyleMorphControl() { return styleMorph; }
  StyleSelector &getStyleSelector() { return styleSelector; }
  MacroPanel &getMacroPanel() { return macroPanel; }

private:
  juce::Label headerLabel;
  StyleSelector styleSelector;
  StyleMorphControl styleMorph;
  VisualFeedbackView visualFeedback;
  MacroPanel macroPanel;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainLayout)
};

} // namespace ui
} // namespace dnb_bass
