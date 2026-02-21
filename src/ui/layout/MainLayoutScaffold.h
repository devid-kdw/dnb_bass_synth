#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>

#include "../components/MacroPanelPlaceholder.h"
#include "../components/StyleSelectorPlaceholder.h"

namespace dnb_bass {
namespace ui {

// Top-level UI layout scaffold for P2
class MainLayoutScaffold : public juce::Component {
public:
  MainLayoutScaffold() {
    addAndMakeVisible(headerLabel);
    headerLabel.setText("DnB Bass Synth VST3 - MVP P2 Scaffold",
                        juce::dontSendNotification);
    headerLabel.setFont(juce::FontOptions(24.0f, juce::Font::bold));
    headerLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(styleSelector);
    addAndMakeVisible(macroPanel);
  }

  void resized() override {
    auto bounds = getLocalBounds().reduced(20);

    // Header
    headerLabel.setBounds(bounds.removeFromTop(40));
    bounds.removeFromTop(20);

    // Style Selector
    styleSelector.setBounds(bounds.removeFromTop(40).withWidth(300).withX(
        bounds.getX() + (bounds.getWidth() - 300) / 2));
    bounds.removeFromTop(40);

    // Macros
    macroPanel.setBounds(bounds.removeFromTop(150));
  }

  void paint(juce::Graphics &g) override {
    g.fillAll(juce::Colour(0xff121212)); // Theme::background placeholder
  }

private:
  juce::Label headerLabel;
  StyleSelectorPlaceholder styleSelector;
  MacroPanelPlaceholder macroPanel;
};

} // namespace ui
} // namespace dnb_bass
