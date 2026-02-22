#pragma once
#include "UIAssets.h"
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
    bgImg = juce::ImageCache::getFromMemory(
        UIAssets::ui_background_root_main_base_v001_png,
        UIAssets::ui_background_root_main_base_v001_pngSize);

    noiseImg = juce::ImageCache::getFromMemory(
        UIAssets::ui_background_root_noise_base_v001_png,
        UIAssets::ui_background_root_noise_base_v001_pngSize);

    titlePlateImg = juce::ImageCache::getFromMemory(
        UIAssets::ui_panel_header_titleplate_base_v001_png,
        UIAssets::ui_panel_header_titleplate_base_v001_pngSize);

    addAndMakeVisible(styleSelector);
    addAndMakeVisible(styleMorph);
    addAndMakeVisible(visualFeedback);
    addAndMakeVisible(macroPanel);
  }

  void resized() override {
    auto bounds =
        getLocalBounds().reduced(20, 25); // General padding matching design

    // The header is now an image plate, we define its bounds but draw it in
    // paint
    titlePlateBounds = bounds.removeFromTop(45).withWidth(400).withX(
        bounds.getX() + (bounds.getWidth() - 400) / 2);
    bounds.removeFromTop(10);

    // Style Selector
    styleSelector.setBounds(bounds.removeFromTop(45).withWidth(280).withX(
        bounds.getX() + (bounds.getWidth() - 280) / 2));
    bounds.removeFromTop(15);

    // Style Morph Slider
    styleMorph.setBounds(bounds.removeFromTop(60).withWidth(320).withX(
        bounds.getX() + (bounds.getWidth() - 320) / 2));
    bounds.removeFromTop(20);

    // Visual Feedback Area
    visualFeedback.setBounds(bounds.removeFromTop(140).withWidth(420).withX(
        bounds.getX() + (bounds.getWidth() - 420) / 2));
    bounds.removeFromTop(20);

    // Canonical MVP macros + Advanced Macros (10 Total)
    // Fits rest of area
    macroPanel.setBounds(
        bounds.withWidth(bounds.getWidth() - 20).withX(bounds.getX() + 10));
  }

  void paint(juce::Graphics &g) override {
    auto bounds = getLocalBounds().toFloat();

    if (bgImg.isValid()) {
      g.drawImage(bgImg, bounds, juce::RectanglePlacement::stretchToFit);
    }

    if (noiseImg.isValid()) {
      g.drawImage(noiseImg, bounds, juce::RectanglePlacement::stretchToFit);
    }

    if (titlePlateImg.isValid()) {
      g.drawImage(titlePlateImg, titlePlateBounds.toFloat(),
                  juce::RectanglePlacement::stretchToFit);
    }
  }

  StyleMorphControl &getStyleMorphControl() { return styleMorph; }
  StyleSelector &getStyleSelector() { return styleSelector; }
  MacroPanel &getMacroPanel() { return macroPanel; }

private:
  juce::Image bgImg;
  juce::Image noiseImg;
  juce::Image titlePlateImg;
  juce::Rectangle<int> titlePlateBounds;

  StyleSelector styleSelector;
  StyleMorphControl styleMorph;
  VisualFeedbackView visualFeedback;
  MacroPanel macroPanel;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainLayout)
};

} // namespace ui
} // namespace dnb_bass
