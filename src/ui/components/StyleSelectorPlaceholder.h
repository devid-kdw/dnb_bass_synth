#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>

namespace dnb_bass {
namespace ui {

// Placeholder for the style selector defined in the P1 contract (Tech, Neuro,
// Dark)
class StyleSelectorPlaceholder : public juce::Component {
public:
  StyleSelectorPlaceholder() {
    addAndMakeVisible(comboInfo);
    comboInfo.setText("Style Mode:", juce::dontSendNotification);
    comboInfo.setJustificationType(juce::Justification::centredRight);

    addAndMakeVisible(styleCombo);
    styleCombo.addItem("Tech", 1);
    styleCombo.addItem("Neuro", 2);
    styleCombo.addItem("Dark", 3);
    styleCombo.setSelectedId(1, juce::dontSendNotification);

    // No runtime bindings here in P2 scaffold!
  }

  void resized() override {
    auto bounds = getLocalBounds().reduced(10);
    comboInfo.setBounds(bounds.removeFromLeft(bounds.getWidth() / 2));
    styleCombo.setBounds(bounds);
  }

  void paint(juce::Graphics &g) override {
    g.setColour(juce::Colour(0xff1e1e1e));
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 4.0f);

    g.setColour(juce::Colour(0xffe0e0e0));
    g.drawRoundedRectangle(getLocalBounds().toFloat(), 4.0f, 1.0f);
  }

private:
  juce::Label comboInfo;
  juce::ComboBox styleCombo;
};

} // namespace ui
} // namespace dnb_bass
