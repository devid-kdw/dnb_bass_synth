#pragma once
#include "../theme/Theme.h"
#include <juce_gui_basics/juce_gui_basics.h>

namespace dnb_bass {
namespace ui {

// Dedicated slider controlling the 0.0-1.0 style_morph backend parameter.
// Visually represents the Tech (0.0) -> Neuro (0.5) -> Dark (1.0) spectrum.
class StyleMorphControl : public juce::Component {
public:
  StyleMorphControl() {
    addAndMakeVisible(morphSlider);
    morphSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    morphSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);

    addAndMakeVisible(techLabel);
    techLabel.setText("Tech", juce::dontSendNotification);
    techLabel.setColour(juce::Label::textColourId, Theme::accentTech);
    techLabel.setJustificationType(juce::Justification::centredLeft);

    addAndMakeVisible(neuroLabel);
    neuroLabel.setText("Neuro", juce::dontSendNotification);
    neuroLabel.setColour(juce::Label::textColourId, Theme::accentNeuro);
    neuroLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(darkLabel);
    darkLabel.setText("Dark", juce::dontSendNotification);
    darkLabel.setColour(juce::Label::textColourId, Theme::accentDark);
    darkLabel.setJustificationType(juce::Justification::centredRight);
  }

  void resized() override {
    auto bounds = getLocalBounds().reduced(10);
    auto labelBounds = bounds.removeFromBottom(20);

    techLabel.setBounds(labelBounds.withWidth(50));
    darkLabel.setBounds(
        labelBounds.withTrimmedLeft(labelBounds.getWidth() - 50));
    neuroLabel.setBounds(labelBounds);

    morphSlider.setBounds(bounds.reduced(0, 5));
  }

  void paint(juce::Graphics &g) override {
    g.setColour(Theme::panelBackground);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 4.0f);

    g.setColour(Theme::textSecondary.withAlpha(0.2f));
    g.drawRoundedRectangle(getLocalBounds().toFloat(), 4.0f, 1.0f);
  }

  juce::Slider &getSlider() { return morphSlider; }

private:
  juce::Slider morphSlider;
  juce::Label techLabel;
  juce::Label neuroLabel;
  juce::Label darkLabel;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StyleMorphControl)
};

} // namespace ui
} // namespace dnb_bass
