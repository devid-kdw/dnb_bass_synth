#pragma once
#include <juce_gui_basics/juce_gui_basics.h>

namespace dnb_bass {
namespace ui {

class ImageMorphSlider : public juce::Slider {
public:
  ImageMorphSlider(const void *trackImgData, int trackImgSize, const void *thumbImgData,
                   int thumbImgSize, const void *glowImgData, int glowImgSize)
      : trackImg(juce::ImageCache::getFromMemory(trackImgData, trackImgSize)),
        thumbImg(juce::ImageCache::getFromMemory(thumbImgData, thumbImgSize)),
        glowImg(juce::ImageCache::getFromMemory(glowImgData, glowImgSize)) {

    setSliderStyle(juce::Slider::LinearHorizontal);
    setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
  }

  void paint(juce::Graphics &g) override {
    auto bounds = getLocalBounds().toFloat();
    const float val = juce::jlimit(0.0f, 1.0f, (float)valueToProportionOfLength(getValue()));

    // Draw base track
    if (trackImg.isValid()) {
      g.drawImage(trackImg, bounds, juce::RectanglePlacement::stretchToFit);
    }

    const float progressY = bounds.getCentreY();
    const float progressStart = bounds.getX() + 6.0f;
    const float progressEnd = bounds.getRight() - 6.0f;
    const float progressX = progressStart + (progressEnd - progressStart) * val;
    g.setColour(juce::Colours::white.withAlpha(0.26f));
    g.drawLine(progressStart, progressY, progressEnd, progressY, 2.0f);
    g.setColour(juce::Colour::fromRGB(90, 220, 255).withAlpha(0.95f));
    g.drawLine(progressStart, progressY, progressX, progressY, 2.2f);

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
      const float thumbSize = juce::jlimit(18.0f, bounds.getHeight(), bounds.getHeight() * 0.9f);

      // Calculate thumb X center relative to slider bounds
      // Usable width ensures the center of the thumb reaches edges without
      // clipping
      const float usableWidth = bounds.getWidth() - thumbSize;
      const float thumbX =
          (bounds.getX() + thumbSize / 2.0f) + (val * usableWidth) - (thumbSize / 2.0f);

      juce::Rectangle<float> thumbBounds(thumbX, bounds.getCentreY() - (thumbSize / 2.0f),
                                         thumbSize, thumbSize);
      g.drawImage(thumbImg, thumbBounds, juce::RectanglePlacement::stretchToFit);
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
