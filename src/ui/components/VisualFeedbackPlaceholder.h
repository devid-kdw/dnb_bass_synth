#pragma once
#include <juce_gui_basics/juce_gui_basics.h>

namespace dnb_bass {
namespace ui {

// Placeholder for the Oscilloscope and Spectrum Analyzer (Real-time FFT/Wave)
// as required by the supplementary specification for visual feedback.
class VisualFeedbackPlaceholder : public juce::Component {
public:
  VisualFeedbackPlaceholder() {
    addAndMakeVisible(infoLabel);
    infoLabel.setText("[ DSP Visualization Area: FFT & Wavefold Notch Paths ]",
                      juce::dontSendNotification);
    infoLabel.setJustificationType(juce::Justification::centred);
    infoLabel.setFont(juce::FontOptions(14.0f, juce::Font::italic));
    infoLabel.setColour(juce::Label::textColourId, juce::Colour(0xff888888));
  }

  void resized() override { infoLabel.setBounds(getLocalBounds()); }

  void paint(juce::Graphics &g) override {
    auto bounds = getLocalBounds().toFloat();

    // Dark background for scope area
    g.setColour(juce::Colour(0xff0a0a0a));
    g.fillRoundedRectangle(bounds, 6.0f);

    // Mock sub wave (pure sine)
    g.setColour(juce::Colour(0xff00b0ff).withAlpha(0.6f));
    g.drawRoundedRectangle(bounds.reduced(1.0f), 6.0f, 1.0f);

    // Draw a simulated static sine wave center line
    g.setColour(juce::Colour(0xff333333));
    g.drawLine(0, bounds.getHeight() / 2, bounds.getWidth(),
               bounds.getHeight() / 2, 1.0f);
  }

private:
  juce::Label infoLabel;
};

} // namespace ui
} // namespace dnb_bass
