#pragma once
#include <juce_gui_basics/juce_gui_basics.h>

namespace dnb_bass {
namespace ui {

class ImageToggleButton : public juce::ToggleButton {
public:
  // We take 3 state images directly matching the graphic design contract
  ImageToggleButton(const juce::String &buttonName, const void *idleImgData,
                    int idleImgSize, const void *selectedImgData,
                    int selectedImgSize, const void *disabledImgData,
                    int disabledImgSize)
      : juce::ToggleButton(buttonName),
        idleImg(juce::ImageCache::getFromMemory(idleImgData, idleImgSize)),
        selectedImg(
            juce::ImageCache::getFromMemory(selectedImgData, selectedImgSize)),
        disabledImg(juce::ImageCache::getFromMemory(disabledImgData,
                                                    disabledImgSize)) {}

  void paintButton(juce::Graphics &g, bool shouldDrawButtonAsHighlighted,
                   bool shouldDrawButtonAsDown) override {
    auto bounds = getLocalBounds().toFloat();
    juce::Image *targetImg = &idleImg;

    if (!isEnabled()) {
      targetImg = &disabledImg;
    } else if (getToggleState()) {
      targetImg = &selectedImg;
    }

    if (targetImg->isValid()) {
      g.drawImage(*targetImg, bounds, juce::RectanglePlacement::stretchToFit);
    }
  }

private:
  juce::Image idleImg;
  juce::Image selectedImg;
  juce::Image disabledImg;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ImageToggleButton)
};

} // namespace ui
} // namespace dnb_bass
