#pragma once
#include <juce_gui_basics/juce_gui_basics.h>

namespace dnb_bass {
namespace ui {

class ImageSlider : public juce::Slider {
public:
  // We take exactly 3 state images directly matching the graphic design
  // contract
  ImageSlider(const void *idleImgData, int idleImgSize,
              const void *hoverImgData, int hoverImgSize,
              const void *activeImgData, int activeImgSize)
      : idleImg(juce::ImageCache::getFromMemory(idleImgData, idleImgSize)),
        hoverImg(juce::ImageCache::getFromMemory(hoverImgData, hoverImgSize)),
        activeImg(
            juce::ImageCache::getFromMemory(activeImgData, activeImgSize)) {

    setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
  }

  void paint(juce::Graphics &g) override {
    auto bounds = getLocalBounds().toFloat();
    float val = (float)getValue();

    juce::Image *targetImg = &idleImg;

    if (isMouseButtonDown()) {
      targetImg = &activeImg;
    } else if (isMouseOverOrDragging()) {
      targetImg = &hoverImg;
    }

    if (targetImg->isValid()) {
      // The designer exported static knobs. We need to rotate them according to
      // value. Standard JUCE rotation is 5/4 PI to 11/4 PI.
      float startAngle = 5.0f * juce::MathConstants<float>::pi / 4.0f;
      float endAngle = 11.0f * juce::MathConstants<float>::pi / 4.0f;
      float currentAngle = startAngle + val * (endAngle - startAngle);

      auto transform = juce::AffineTransform::rotation(
          currentAngle, bounds.getCentreX(), bounds.getCentreY());

      // Ensure rotation fits within square cell bounds gracefully, draw bounds
      // scaled if image is too large, but assume it fits to avoid artifacting
      // if possible.
      g.drawImageTransformed(*targetImg, transform);
    }
  }

private:
  juce::Image idleImg;
  juce::Image hoverImg;
  juce::Image activeImg;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ImageSlider)
};

} // namespace ui
} // namespace dnb_bass
