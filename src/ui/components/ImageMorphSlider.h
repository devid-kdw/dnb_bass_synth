#pragma once
#include <juce_gui_basics/juce_gui_basics.h>

namespace dnb_bass {
namespace ui {

class ImageMorphSlider : public juce::Slider {
public:
  ImageMorphSlider(const void *trackImgData, int trackImgSize,
                   const void *thumbImgData, int thumbImgSize,
                   const void *glowImgData, int glowImgSize)
      : trackImg(juce::ImageCache::getFromMemory(trackImgData, trackImgSize)),
        thumbImg(juce::ImageCache::getFromMemory(thumbImgData, thumbImgSize)),
        glowImg(juce::ImageCache::getFromMemory(glowImgData, glowImgSize)) {

    setSliderStyle(juce::Slider::LinearHorizontal);
    setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
  }

  void paint(juce::Graphics &g) override {
    auto bounds = getLocalBounds().toFloat();
    float val = (float)getValue(); // Normalised 0.0 to 1.0

    // Draw base track
    if (trackImg.isValid()) {
      g.drawImage(trackImg, bounds, juce::RectanglePlacement::stretchToFit);
    }

    // Draw active glow (opacity scales from 0.0 to 1.0 depending on value, or
    // just raw) Actually the design states 'canonical style control set', we'll
    // just draw the active glow when val > 0
    if (glowImg.isValid() && val > 0.01f) {
      g.setOpacity(val);
      g.drawImage(glowImg, bounds, juce::RectanglePlacement::stretchToFit);
      g.setOpacity(1.0f);
    }

    // Draw draggable thumb
    if (thumbImg.isValid()) {
      float thumbWidth =
          (float)thumbImg.getWidth(); // Real scale or relative scale
      float thumbHeight =
          bounds.getHeight() * 1.2f; // Thumb slightly larger than track

      // Calculate thumb X center relative to slider bounds
      // Usable width ensures the center of the thumb reaches edges without
      // clipping
      float usableWidth = bounds.getWidth() - thumbHeight;
      float thumbX = (bounds.getX() + thumbHeight / 2.0f) +
                     (val * usableWidth) - (thumbHeight / 2.0f);

      juce::Rectangle<float> thumbBounds(
          thumbX, bounds.getCentreY() - (thumbHeight / 2.0f), thumbHeight,
          thumbHeight);
      g.drawImage(thumbImg, thumbBounds,
                  juce::RectanglePlacement::stretchToFit);
    }
  }

private:
  juce::Image trackImg;
  juce::Image thumbImg;
  juce::Image glowImg;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ImageMorphSlider)
};

} // namespace ui
} // namespace dnb_bass
