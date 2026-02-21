#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>

namespace dnb_bass {
namespace ui {

// Placeholder for the macro panel defined in the P1 contract (4 core macros
// MVP)
class MacroPanelPlaceholder : public juce::Component {
public:
  MacroPanelPlaceholder() {
    for (int i = 0; i < 4; ++i) {
      auto *slider = new juce::Slider();
      slider->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
      slider->setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
      addAndMakeVisible(slider);
      sliders.add(slider);

      auto *label = new juce::Label();
      label->setJustificationType(juce::Justification::centred);
      addAndMakeVisible(label);
      labels.add(label);
    }

    labels[0]->setText("Squelch",
                       juce::dontSendNotification); // macro.neuro_formant
    labels[1]->setText("Foghorn", juce::dontSendNotification); // macro.fm_metal
    labels[2]->setText("Wobble",
                       juce::dontSendNotification); // macro.roller_dynamics
    labels[3]->setText("Warmth",
                       juce::dontSendNotification); // macro.liquid_depth

    // No runtime bindings in P2 scaffold!
  }

  void resized() override {
    auto bounds = getLocalBounds().reduced(20);
    int itemWidth = bounds.getWidth() / 4;

    for (int i = 0; i < 4; ++i) {
      auto area = bounds.removeFromLeft(itemWidth).reduced(5);
      labels[i]->setBounds(area.removeFromBottom(20));
      sliders[i]->setBounds(area);
    }
  }

  void paint(juce::Graphics &g) override {
    g.setColour(juce::Colour(0xff1e1e1e));
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 8.0f);

    g.setColour(juce::Colour(0xffe0e0e0));
    g.drawRoundedRectangle(getLocalBounds().toFloat(), 8.0f, 1.0f);
  }

private:
  juce::OwnedArray<juce::Slider> sliders;
  juce::OwnedArray<juce::Label> labels;
};

} // namespace ui
} // namespace dnb_bass
