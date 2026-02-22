#pragma once
#include "../theme/Theme.h"
#include "ImageSlider.h"
#include "UIAssets.h"
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
    // 1. Primary Macros
    addSlider(UIAssets::ui_macro_knob_neuro_formant_idle_v001_png,
              UIAssets::ui_macro_knob_neuro_formant_idle_v001_pngSize,
              UIAssets::ui_macro_knob_neuro_formant_hover_v001_png,
              UIAssets::ui_macro_knob_neuro_formant_hover_v001_pngSize,
              UIAssets::ui_macro_knob_neuro_formant_active_v001_png,
              UIAssets::ui_macro_knob_neuro_formant_active_v001_pngSize,
              "Neuro Formant");

    addSlider(UIAssets::ui_macro_knob_fm_metal_idle_v001_png,
              UIAssets::ui_macro_knob_fm_metal_idle_v001_pngSize,
              UIAssets::ui_macro_knob_fm_metal_hover_v001_png,
              UIAssets::ui_macro_knob_fm_metal_hover_v001_pngSize,
              UIAssets::ui_macro_knob_fm_metal_active_v001_png,
              UIAssets::ui_macro_knob_fm_metal_active_v001_pngSize, "FM Metal");

    addSlider(UIAssets::ui_macro_knob_roller_dynamics_idle_v001_png,
              UIAssets::ui_macro_knob_roller_dynamics_idle_v001_pngSize,
              UIAssets::ui_macro_knob_roller_dynamics_hover_v001_png,
              UIAssets::ui_macro_knob_roller_dynamics_hover_v001_pngSize,
              UIAssets::ui_macro_knob_roller_dynamics_active_v001_png,
              UIAssets::ui_macro_knob_roller_dynamics_active_v001_pngSize,
              "Roller Dynamics");

    addSlider(UIAssets::ui_macro_knob_liquid_depth_idle_v001_png,
              UIAssets::ui_macro_knob_liquid_depth_idle_v001_pngSize,
              UIAssets::ui_macro_knob_liquid_depth_hover_v001_png,
              UIAssets::ui_macro_knob_liquid_depth_hover_v001_pngSize,
              UIAssets::ui_macro_knob_liquid_depth_active_v001_png,
              UIAssets::ui_macro_knob_liquid_depth_active_v001_pngSize,
              "Liquid Depth");

    // 2. Advanced Macros
    addSlider(UIAssets::ui_macro_knob_sub_punch_idle_v001_png,
              UIAssets::ui_macro_knob_sub_punch_idle_v001_pngSize,
              UIAssets::ui_macro_knob_sub_punch_hover_v001_png,
              UIAssets::ui_macro_knob_sub_punch_hover_v001_pngSize,
              UIAssets::ui_macro_knob_sub_punch_active_v001_png,
              UIAssets::ui_macro_knob_sub_punch_active_v001_pngSize,
              "Sub Punch");

    addSlider(UIAssets::ui_macro_knob_fm_pressure_idle_v001_png,
              UIAssets::ui_macro_knob_fm_pressure_idle_v001_pngSize,
              UIAssets::ui_macro_knob_fm_pressure_hover_v001_png,
              UIAssets::ui_macro_knob_fm_pressure_hover_v001_pngSize,
              UIAssets::ui_macro_knob_fm_pressure_active_v001_png,
              UIAssets::ui_macro_knob_fm_pressure_active_v001_pngSize,
              "FM Pressure");

    addSlider(UIAssets::ui_macro_knob_cutoff_motion_idle_v001_png,
              UIAssets::ui_macro_knob_cutoff_motion_idle_v001_pngSize,
              UIAssets::ui_macro_knob_cutoff_motion_hover_v001_png,
              UIAssets::ui_macro_knob_cutoff_motion_hover_v001_pngSize,
              UIAssets::ui_macro_knob_cutoff_motion_active_v001_png,
              UIAssets::ui_macro_knob_cutoff_motion_active_v001_pngSize,
              "Cutoff");

    addSlider(UIAssets::ui_macro_knob_fold_bite_idle_v001_png,
              UIAssets::ui_macro_knob_fold_bite_idle_v001_pngSize,
              UIAssets::ui_macro_knob_fold_bite_hover_v001_png,
              UIAssets::ui_macro_knob_fold_bite_hover_v001_pngSize,
              UIAssets::ui_macro_knob_fold_bite_active_v001_png,
              UIAssets::ui_macro_knob_fold_bite_active_v001_pngSize,
              "Fold Bite");

    addSlider(UIAssets::ui_macro_knob_table_drift_idle_v001_png,
              UIAssets::ui_macro_knob_table_drift_idle_v001_pngSize,
              UIAssets::ui_macro_knob_table_drift_hover_v001_png,
              UIAssets::ui_macro_knob_table_drift_hover_v001_pngSize,
              UIAssets::ui_macro_knob_table_drift_active_v001_png,
              UIAssets::ui_macro_knob_table_drift_active_v001_pngSize,
              "Table Drift");

    addSlider(UIAssets::ui_macro_knob_smash_glue_idle_v001_png,
              UIAssets::ui_macro_knob_smash_glue_idle_v001_pngSize,
              UIAssets::ui_macro_knob_smash_glue_hover_v001_png,
              UIAssets::ui_macro_knob_smash_glue_hover_v001_pngSize,
              UIAssets::ui_macro_knob_smash_glue_active_v001_png,
              UIAssets::ui_macro_knob_smash_glue_active_v001_pngSize,
              "Smash Glue");

    primaryFrameImg = juce::ImageCache::getFromMemory(
        UIAssets::ui_panel_macro_primary_frame_base_v001_png,
        UIAssets::ui_panel_macro_primary_frame_base_v001_pngSize);

    advancedFrameImg = juce::ImageCache::getFromMemory(
        UIAssets::ui_panel_macro_advanced_frame_base_v001_png,
        UIAssets::ui_panel_macro_advanced_frame_base_v001_pngSize);
  }

  void addSlider(const void *idle, int idleSize, const void *hover,
                 int hoverSize, const void *active, int activeSize,
                 const juce::String &labelText) {
    auto *slider =
        new ImageSlider(idle, idleSize, hover, hoverSize, active, activeSize);
    addAndMakeVisible(slider);
    sliders.add(slider);

    auto *label = new juce::Label();
    label->setJustificationType(juce::Justification::centred);
    label->setColour(juce::Label::textColourId, Theme::textPrimary);
    label->setText(labelText, juce::dontSendNotification);
    addAndMakeVisible(label);
    labels.add(label);
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
    if (primaryFrameImg.isValid()) {
      g.drawImage(primaryFrameImg, primaryBounds.toFloat(),
                  juce::RectanglePlacement::stretchToFit);
    }

    if (advancedFrameImg.isValid()) {
      g.drawImage(advancedFrameImg, advancedBounds.toFloat(),
                  juce::RectanglePlacement::stretchToFit);
    }
  }

  juce::Slider &getSlider(MacroIndex idx) { return *sliders[(int)idx]; }

private:
  juce::Image primaryFrameImg;
  juce::Image advancedFrameImg;

  juce::Rectangle<int> primaryBounds;
  juce::Rectangle<int> advancedBounds;

  juce::OwnedArray<juce::Slider> sliders;
  juce::OwnedArray<juce::Label> labels;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MacroPanel)
};

} // namespace ui
} // namespace dnb_bass
