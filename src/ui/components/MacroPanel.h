#pragma once
#include "../theme/Theme.h"
#include <juce_gui_basics/juce_gui_basics.h>

namespace dnb_bass {
namespace ui {

// The actual Macro Panel exposing reference to the sliders for param binding
class MacroPanel : public juce::Component {
public:
  enum MacroIndex {
    NeuroFormant = 0, // macro.neuro_formant
    FmMetal = 1,      // macro.fm_metal
    RollerDynamics = 2, // macro.roller_dynamics
    LiquidDepth = 3   // macro.liquid_depth
  };

  static constexpr int macroCount = 4;

  MacroPanel() {
    for (int i = 0; i < macroCount; ++i) {
      auto *slider = new juce::Slider();
      slider->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
      slider->setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
      addAndMakeVisible(slider);
      sliders.add(slider);

      auto *label = new juce::Label();
      label->setJustificationType(juce::Justification::centred);
      label->setColour(juce::Label::textColourId, Theme::textPrimary);
      addAndMakeVisible(label);
      labels.add(label);
    }

    labels[NeuroFormant]->setText("Neuro Formant", juce::dontSendNotification);
    labels[FmMetal]->setText("FM Metal", juce::dontSendNotification);
    labels[RollerDynamics]->setText("Roller Dynamics",
                                    juce::dontSendNotification);
    labels[LiquidDepth]->setText("Liquid Depth", juce::dontSendNotification);
  }

  void resized() override {
    auto bounds = getLocalBounds().reduced(20);
    int itemWidth = bounds.getWidth() / macroCount;

    for (int i = 0; i < macroCount; ++i) {
      auto area = bounds.removeFromLeft(itemWidth).reduced(5);
      labels[i]->setBounds(area.removeFromBottom(20));
      sliders[i]->setBounds(area);
    }
  }

  void paint(juce::Graphics &g) override {
    g.setColour(Theme::panelBackground);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 8.0f);

    g.setColour(Theme::textSecondary.withAlpha(0.2f));
    g.drawRoundedRectangle(getLocalBounds().toFloat(), 8.0f, 1.0f);
  }

  juce::Slider &getSlider(MacroIndex idx) { return *sliders[(int)idx]; }

private:
  juce::OwnedArray<juce::Slider> sliders;
  juce::OwnedArray<juce::Label> labels;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MacroPanel)
};

} // namespace ui
} // namespace dnb_bass
