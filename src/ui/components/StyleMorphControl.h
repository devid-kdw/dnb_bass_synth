#pragma once
#include "../theme/Theme.h"
#include "ImageMorphSlider.h"
#include "UIAssets.h"
#include <juce_gui_basics/juce_gui_basics.h>
#include <memory>

namespace dnb_bass {
namespace ui {

// Dedicated slider controlling the 0.0-1.0 style_morph backend parameter.
// Visually represents the Tech (0.0) -> Neuro (0.5) -> Dark (1.0) spectrum.
class StyleMorphControl : public juce::Component {
public:
  StyleMorphControl() {
    frameImg = juce::ImageCache::getFromMemory(
        UIAssets::ui_panel_style_morph_frame_base_v001_png,
        UIAssets::ui_panel_style_morph_frame_base_v001_pngSize);

    morphSlider = std::make_unique<ImageMorphSlider>(
        UIAssets::ui_style_morph_track_main_base_v001_png,
        UIAssets::ui_style_morph_track_main_base_v001_pngSize,
        UIAssets::ui_style_morph_thumb_main_base_v001_png,
        UIAssets::ui_style_morph_thumb_main_base_v001_pngSize,
        UIAssets::ui_style_morph_glow_main_active_v001_png,
        UIAssets::ui_style_morph_glow_main_active_v001_pngSize);

    addAndMakeVisible(morphSlider.get());
  }

  void resized() override {
    if (morphSlider != nullptr) {
      // Frame has inherent padding, fit slider into logical track zone
      morphSlider->setBounds(getLocalBounds().reduced(20, 25));
    }
  }

  void paint(juce::Graphics &g) override {
    if (frameImg.isValid()) {
      g.drawImage(frameImg, getLocalBounds().toFloat(),
                  juce::RectanglePlacement::stretchToFit);
    }
  }

  juce::Slider &getSlider() { return *morphSlider; }

private:
  juce::Image frameImg;
  std::unique_ptr<ImageMorphSlider> morphSlider;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StyleMorphControl)
};

} // namespace ui
} // namespace dnb_bass
