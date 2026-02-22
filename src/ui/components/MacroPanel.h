#pragma once
#include "../theme/Theme.h"
#include <juce_gui_basics/juce_gui_basics.h>

namespace dnb_bass {
namespace ui {

// The actual Macro Panel exposing reference to the sliders for param binding
class MacroPanel : public juce::Component {
public:
  enum MacroIndex {
    NeuroFormant = 0,   // macro.neuro_formant
    FmMetal = 1,        // macro.fm_metal
    RollerDynamics = 2, // macro.roller_dynamics
    LiquidDepth = 3,    // macro.liquid_depth
    SubPunch = 4,       // macro.sub_punch
    FmPressure = 5,     // macro.fm_pressure
    CutoffMotion = 6,   // macro.cutoff_motion
    FoldBite = 7,       // macro.fold_bite
    TableDrift = 8,     // macro.table_drift
    SmashGlue = 9       // macro.smash_glue
  };

  static constexpr int macroCount = 10;
  static constexpr int primaryCount = 4;
  static constexpr int advancedCount = 6;

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

    labels[SubPunch]->setText("Sub Punch", juce::dontSendNotification);
    labels[FmPressure]->setText("FM Pressure", juce::dontSendNotification);
    labels[CutoffMotion]->setText("Cutoff", juce::dontSendNotification);
    labels[FoldBite]->setText("Fold Bite", juce::dontSendNotification);
    labels[TableDrift]->setText("Table Drift", juce::dontSendNotification);
    labels[SmashGlue]->setText("Smash Glue", juce::dontSendNotification);
  }

  void resized() override {
    auto bounds = getLocalBounds().reduced(5);

    int totalHeight = bounds.getHeight();
    primaryBounds = bounds.removeFromTop(static_cast<int>(totalHeight * 0.45f));
    bounds.removeFromTop(10); // Spacing between panels
    advancedBounds = bounds;

    // Layout Primary Surface (4 macros)
    auto pArea = primaryBounds.reduced(10);
    int pWidth = pArea.getWidth() / primaryCount;
    for (int i = 0; i < primaryCount; ++i) {
      auto cell = pArea.removeFromLeft(pWidth).reduced(5);
      labels[i]->setBounds(cell.removeFromBottom(20));
      sliders[i]->setBounds(cell);
    }

    // Layout Advanced Surface (6 macros)
    auto aArea =
        advancedBounds.reduced(5).withTrimmedTop(25); // Space for title
    int aWidth = aArea.getWidth() / advancedCount;
    for (int i = primaryCount; i < macroCount; ++i) {
      auto cell = aArea.removeFromLeft(aWidth).reduced(2); // Tenser fit for 6
      labels[i]->setBounds(cell.removeFromBottom(20));
      sliders[i]->setBounds(cell);
    }
  }

  void paint(juce::Graphics &g) override {
    // Primary Surface Background
    g.setColour(Theme::panelBackground.brighter(0.05f));
    g.fillRoundedRectangle(primaryBounds.toFloat(), 8.0f);
    g.setColour(Theme::accentTech.withAlpha(0.6f));
    g.drawRoundedRectangle(primaryBounds.toFloat(), 8.0f, 2.0f);

    // Advanced Surface Background
    g.setColour(Theme::panelBackground.darker(0.1f));
    g.fillRoundedRectangle(advancedBounds.toFloat(), 8.0f);
    g.setColour(Theme::textSecondary.withAlpha(0.2f));
    g.drawRoundedRectangle(advancedBounds.toFloat(), 8.0f, 1.0f);

    // Advanced Label
    g.setColour(Theme::textSecondary);
    g.setFont(12.0f);
    g.drawText("ADVANCED MACROS", advancedBounds.withHeight(25),
               juce::Justification::centred);
  }

  juce::Slider &getSlider(MacroIndex idx) { return *sliders[(int)idx]; }

private:
  juce::Rectangle<int> primaryBounds;
  juce::Rectangle<int> advancedBounds;

  juce::OwnedArray<juce::Slider> sliders;
  juce::OwnedArray<juce::Label> labels;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MacroPanel)
};

} // namespace ui
} // namespace dnb_bass
