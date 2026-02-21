#pragma once
#include "../theme/Theme.h"
#include <juce_gui_basics/juce_gui_basics.h>

namespace dnb_bass {
namespace ui {

// A mock view representing the Oscilloscope/Spectrum Analyzer.
// Since backend did not deliver the FIFOs, this just paints a static mock
// representation
class VisualFeedbackView : public juce::Component {
public:
  VisualFeedbackView() {
    addAndMakeVisible(infoLabel);
    infoLabel.setText("[ DSP Visualization Area: FFT & Wavefold Notch Paths ]",
                      juce::dontSendNotification);
    infoLabel.setJustificationType(juce::Justification::centred);
    infoLabel.setFont(juce::FontOptions(14.0f, juce::Font::italic));
    infoLabel.setColour(juce::Label::textColourId, Theme::textSecondary);
  }

  void resized() override { infoLabel.setBounds(getLocalBounds()); }

  void paint(juce::Graphics &g) override {
    auto bounds = getLocalBounds().toFloat();

    // Dark background for scope area
    g.setColour(juce::Colour(0xff0a0a0a));
    g.fillRoundedRectangle(bounds, 6.0f);

    // Mock sub wave (pure sine)
    g.setColour(Theme::accentTech.withAlpha(0.6f));
    g.drawRoundedRectangle(bounds.reduced(1.0f), 6.0f, 1.0f);

    // Draw a simulated static sine wave center line
    g.setColour(juce::Colour(0xff333333));
    g.drawLine(0, bounds.getHeight() / 2, bounds.getWidth(),
               bounds.getHeight() / 2, 1.0f);
  }

private:
  juce::Label infoLabel;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VisualFeedbackView)
};

} // namespace ui
} // namespace dnb_bass
