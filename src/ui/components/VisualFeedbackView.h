#pragma once
#include "../theme/Theme.h"
#include "UIAssets.h"
#include <juce_gui_basics/juce_gui_basics.h>

namespace dnb_bass {
namespace ui {

// A mock view representing the Oscilloscope/Spectrum Analyzer.
// Since backend did not deliver the FIFOs, this just paints a static mock
// representation
class VisualFeedbackView : public juce::Component {
public:
  VisualFeedbackView() {
    gridImg = juce::ImageCache::getFromMemory(
        UIAssets::ui_visual_scope_grid_main_base_v001_png,
        UIAssets::ui_visual_scope_grid_main_base_v001_pngSize);

    waveImg = juce::ImageCache::getFromMemory(
        UIAssets::ui_visual_scope_wave_overlay_base_v001_png,
        UIAssets::ui_visual_scope_wave_overlay_base_v001_pngSize);

    spectrumImg = juce::ImageCache::getFromMemory(
        UIAssets::ui_visual_scope_spectrum_overlay_base_v001_png,
        UIAssets::ui_visual_scope_spectrum_overlay_base_v001_pngSize);

    glowImg = juce::ImageCache::getFromMemory(
        UIAssets::ui_visual_scope_frame_glow_active_v001_png,
        UIAssets::ui_visual_scope_frame_glow_active_v001_pngSize);
  }

  void resized() override { /* bounds are set by parent */ }

  void paint(juce::Graphics &g) override {
    auto bounds = getLocalBounds().toFloat();

    if (gridImg.isValid()) {
      g.drawImage(gridImg, bounds, juce::RectanglePlacement::stretchToFit);
    }

    // Simulate active scope with mock spectrum/wave depending on UI state
    // Since backend isn't feeding real FFT yet, we just paint the mock assets
    if (spectrumImg.isValid()) {
      g.setOpacity(0.5f);
      g.drawImage(spectrumImg, bounds, juce::RectanglePlacement::stretchToFit);
      g.setOpacity(1.0f);
    }

    if (waveImg.isValid()) {
      g.drawImage(waveImg, bounds, juce::RectanglePlacement::stretchToFit);
    }

    if (glowImg.isValid()) {
      g.drawImage(glowImg, bounds, juce::RectanglePlacement::stretchToFit);
    }
  }

private:
  juce::Image gridImg;
  juce::Image waveImg;
  juce::Image spectrumImg;
  juce::Image glowImg;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VisualFeedbackView)
};

} // namespace ui
} // namespace dnb_bass
