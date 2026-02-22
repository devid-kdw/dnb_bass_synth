#pragma once
#include "../theme/Theme.h"
#include "ImageToggleButton.h"
#include "UIAssets.h"
#include <juce_gui_basics/juce_gui_basics.h>

namespace dnb_bass {
namespace ui {

class StyleSelector : public juce::Component {
public:
  StyleSelector() {
    frameImg = juce::ImageCache::getFromMemory(
        UIAssets::ui_panel_style_selector_frame_base_v001_png,
        UIAssets::ui_panel_style_selector_frame_base_v001_pngSize);

    techButton = std::make_unique<ImageToggleButton>(
        "Tech", UIAssets::ui_style_mode_tech_idle_v001_png,
        UIAssets::ui_style_mode_tech_idle_v001_pngSize,
        UIAssets::ui_style_mode_tech_selected_v001_png,
        UIAssets::ui_style_mode_tech_selected_v001_pngSize,
        UIAssets::ui_style_mode_tech_disabled_v001_png,
        UIAssets::ui_style_mode_tech_disabled_v001_pngSize);

    neuroButton = std::make_unique<ImageToggleButton>(
        "Neuro", UIAssets::ui_style_mode_neuro_idle_v001_png,
        UIAssets::ui_style_mode_neuro_idle_v001_pngSize,
        UIAssets::ui_style_mode_neuro_selected_v001_png,
        UIAssets::ui_style_mode_neuro_selected_v001_pngSize,
        UIAssets::ui_style_mode_neuro_disabled_v001_png,
        UIAssets::ui_style_mode_neuro_disabled_v001_pngSize);

    darkButton = std::make_unique<ImageToggleButton>(
        "Dark", UIAssets::ui_style_mode_dark_idle_v001_png,
        UIAssets::ui_style_mode_dark_idle_v001_pngSize,
        UIAssets::ui_style_mode_dark_selected_v001_png,
        UIAssets::ui_style_mode_dark_selected_v001_pngSize,
        UIAssets::ui_style_mode_dark_disabled_v001_png,
        UIAssets::ui_style_mode_dark_disabled_v001_pngSize);

    techButton->setRadioGroupId(100);
    neuroButton->setRadioGroupId(100);
    darkButton->setRadioGroupId(100);

    addAndMakeVisible(techButton.get());
    addAndMakeVisible(neuroButton.get());
    addAndMakeVisible(darkButton.get());
  }

  void paint(juce::Graphics &g) override {
    if (frameImg.isValid()) {
      g.drawImage(frameImg, getLocalBounds().toFloat(),
                  juce::RectanglePlacement::stretchToFit);
    }
  }

  void resized() override {
    auto bounds =
        getLocalBounds().reduced(10, 20); // Inner padding for the frame
    int w = bounds.getWidth() / 3;

    techButton->setBounds(bounds.removeFromLeft(w).reduced(5));
    neuroButton->setBounds(bounds.removeFromLeft(w).reduced(5));
    darkButton->setBounds(bounds.reduced(5));
  }

  juce::ToggleButton &getTechButton() { return *techButton; }
  juce::ToggleButton &getNeuroButton() { return *neuroButton; }
  juce::ToggleButton &getDarkButton() { return *darkButton; }

private:
  juce::Image frameImg;
  std::unique_ptr<ImageToggleButton> techButton;
  std::unique_ptr<ImageToggleButton> neuroButton;
  std::unique_ptr<ImageToggleButton> darkButton;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StyleSelector)
};

} // namespace ui
} // namespace dnb_bass
