#pragma once
#include <juce_gui_basics/juce_gui_basics.h>

namespace dnb_bass {
namespace ui {

class ImageSlider : public juce::Slider {
public:
  // We take exactly 3 state images directly matching the graphic design
  // contract
  ImageSlider(const void *idleImgData, int idleImgSize, const void *hoverImgData, int hoverImgSize,
              const void *activeImgData, int activeImgSize)
      : idleImg(juce::ImageCache::getFromMemory(idleImgData, idleImgSize)),
        hoverImg(juce::ImageCache::getFromMemory(hoverImgData, hoverImgSize)),
        activeImg(juce::ImageCache::getFromMemory(activeImgData, activeImgSize)) {

    setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    setDoubleClickReturnValue(true, 0.0);
    setRepaintsOnMouseActivity(true);
  }

  void paint(juce::Graphics &g) override {
    auto bounds = getLocalBounds().toFloat();
    float val = juce::jlimit(0.0f, 1.0f, (float)valueToProportionOfLength(getValue()));
    if (val <= 0.001f) {
      val = 0.0f;
    } else if (val >= 0.999f) {
      val = 1.0f;
    }
    constexpr float startAngle =
        3.0f * juce::MathConstants<float>::pi / 4.0f; // 135 deg (bottom-left)
    constexpr float endAngle =
        9.0f * juce::MathConstants<float>::pi / 4.0f; // 405 deg (bottom-right)

    juce::Image *targetImg = &idleImg;

    if (isMouseButtonDown()) {
      targetImg = &activeImg;
    } else if (isMouseOverOrDragging()) {
      targetImg = &hoverImg;
    }

    if (targetImg->isValid()) {
      // The designer exported static knobs. We need to rotate them according to
      // value. Standard JUCE rotation is 5/4 PI to 11/4 PI.
      const float currentAngle = startAngle + val * (endAngle - startAngle);

      const float imgW = (float)targetImg->getWidth();
      const float imgH = (float)targetImg->getHeight();
      if (imgW <= 0.0f || imgH <= 0.0f) {
        return;
      }

      // Fit the image to the available control bounds first, then rotate.
      const float scale = 0.9f * juce::jmin(bounds.getWidth() / imgW, bounds.getHeight() / imgH);
      auto transform = juce::AffineTransform::translation(-imgW * 0.5f, -imgH * 0.5f)
                           .scaled(scale)
                           .rotated(currentAngle)
                           .translated(bounds.getCentreX(), bounds.getCentreY());

      g.drawImageTransformed(*targetImg, transform, true);
    }

    // Value ring keeps the knob legible even if the skin state is dark.
    const float ringRadius =
        juce::jmax(8.0f, 0.44f * juce::jmin(bounds.getWidth(), bounds.getHeight()));
    const float ringThickness = juce::jmax(1.5f, ringRadius * 0.11f);

    juce::Path ringBackground;
    ringBackground.addCentredArc(bounds.getCentreX(), bounds.getCentreY(), ringRadius, ringRadius,
                                 0.0f, startAngle, endAngle, true);
    g.setColour(juce::Colours::white.withAlpha(0.22f));
    g.strokePath(ringBackground, juce::PathStrokeType(ringThickness, juce::PathStrokeType::curved,
                                                      juce::PathStrokeType::rounded));

    juce::Path ringValue;
    if (val > 0.0f) {
      ringValue.addCentredArc(bounds.getCentreX(), bounds.getCentreY(), ringRadius, ringRadius,
                              0.0f, startAngle, startAngle + val * (endAngle - startAngle), true);
    }
    juce::Colour ringColour = juce::Colour::fromRGB(80, 220, 255);
    if (val > 0.66f) {
      ringColour = juce::Colour::fromRGB(255, 120, 210);
    } else if (val > 0.33f) {
      ringColour = juce::Colour::fromRGB(255, 185, 95);
    }
    g.setColour(ringColour.withAlpha(0.95f));
    if (val > 0.0f) {
      g.strokePath(ringValue, juce::PathStrokeType(ringThickness, juce::PathStrokeType::curved,
                                                   juce::PathStrokeType::butt));
    }

    // Endpoint marker prevents perceived "short" glow at exact 100%.
    if (val > 0.0f) {
      const float endpointAngle = startAngle + val * (endAngle - startAngle);
      juce::Point<float> endpoint(bounds.getCentreX() + std::cos(endpointAngle) * ringRadius,
                                  bounds.getCentreY() + std::sin(endpointAngle) * ringRadius);
      g.setColour(ringColour.withAlpha(0.95f));
      g.fillEllipse(endpoint.x - ringThickness * 0.45f, endpoint.y - ringThickness * 0.45f,
                    ringThickness * 0.9f, ringThickness * 0.9f);
    }

    // Pointer line for immediate value readability.
    const float pointerAngle = startAngle + val * (endAngle - startAngle);
    const auto center = bounds.getCentre();
    const float innerR = juce::jmax(4.0f, ringRadius * 0.2f);
    const float outerR = juce::jmax(innerR + 2.0f, ringRadius * 0.82f);
    juce::Point<float> p0(center.x + std::cos(pointerAngle) * innerR,
                          center.y + std::sin(pointerAngle) * innerR);
    juce::Point<float> p1(center.x + std::cos(pointerAngle) * outerR,
                          center.y + std::sin(pointerAngle) * outerR);
    g.setColour(juce::Colours::white.withAlpha(0.85f));
    g.drawLine({p0, p1}, juce::jmax(1.5f, ringThickness * 0.45f));
  }

private:
  juce::Image idleImg;
  juce::Image hoverImg;
  juce::Image activeImg;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ImageSlider)
};

} // namespace ui
} // namespace dnb_bass
