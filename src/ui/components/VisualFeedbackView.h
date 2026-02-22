#pragma once
#include "../theme/Theme.h"
#include "UIAssets.h"
#include <functional>
#include <juce_gui_basics/juce_gui_basics.h>
#include <utility>

namespace dnb_bass {
namespace ui {

// Lightweight visual scope/spectrum layer driven by output level.
class VisualFeedbackView : public juce::Component, private juce::Timer {
public:
  VisualFeedbackView() {
    frameImg =
        juce::ImageCache::getFromMemory(UIAssets::ui_panel_visual_feedback_frame_base_v001_png,
                                        UIAssets::ui_panel_visual_feedback_frame_base_v001_pngSize);

    gridImg =
        juce::ImageCache::getFromMemory(UIAssets::ui_visual_scope_grid_main_base_v001_png,
                                        UIAssets::ui_visual_scope_grid_main_base_v001_pngSize);

    glowImg =
        juce::ImageCache::getFromMemory(UIAssets::ui_visual_scope_frame_glow_active_v001_png,
                                        UIAssets::ui_visual_scope_frame_glow_active_v001_pngSize);

    startTimerHz(30);
  }

  void resized() override { /* bounds are set by parent */ }

  void setLevelProvider(std::function<float()> provider) {
    levelProvider = std::move(provider);
  }

  void paint(juce::Graphics &g) override {
    auto bounds = getLocalBounds().toFloat();

    if (frameImg.isValid()) {
      g.drawImage(frameImg, bounds, juce::RectanglePlacement::stretchToFit);
    }

    if (gridImg.isValid()) {
      g.drawImage(gridImg, bounds, juce::RectanglePlacement::stretchToFit);
    }

    if (glowImg.isValid()) {
      g.drawImage(glowImg, bounds, juce::RectanglePlacement::stretchToFit);
    }

    // Overlay a lightweight real-time response driven by processor output level.
    auto inner = bounds.reduced(12.0f, 10.0f);
    const float level = smoothedLevel;
    const int barCount = 36;
    const float barW = inner.getWidth() / static_cast<float>(barCount);
    const float baseY = inner.getBottom();
    for (int i = 0; i < barCount; ++i) {
      const float t = static_cast<float>(i) / static_cast<float>(barCount - 1);
      const float wobble = 0.4f + 0.6f * std::sin(phase + t * 8.0f);
      const float height = juce::jmax(2.0f, inner.getHeight() * level * wobble);
      const float x = inner.getX() + i * barW + 0.8f;
      juce::Rectangle<float> r(x, baseY - height, juce::jmax(1.0f, barW - 1.8f), height);
      juce::Colour c = juce::Colour::fromRGB(70, 220, 255).withAlpha(0.22f);
      if (i % 3 == 0) {
        c = juce::Colour::fromRGB(255, 95, 210).withAlpha(0.20f);
      }
      g.setColour(c);
      g.fillRoundedRectangle(r, 0.8f);
    }

    juce::Path waveform;
    const int points = 160;
    const float midY = inner.getCentreY();
    const float amp = inner.getHeight() * (0.12f + level * 0.35f);
    for (int i = 0; i < points; ++i) {
      const float t = static_cast<float>(i) / static_cast<float>(points - 1);
      const float x = inner.getX() + t * inner.getWidth();
      const float y = midY + amp * 0.6f * std::sin((t * 10.0f) + phase) +
                      amp * 0.4f * std::sin((t * 22.0f) + phase * 1.7f);
      if (i == 0) {
        waveform.startNewSubPath(x, y);
      } else {
        waveform.lineTo(x, y);
      }
    }
    g.setColour(juce::Colour::fromRGB(80, 230, 255).withAlpha(0.78f));
    g.strokePath(waveform, juce::PathStrokeType(1.65f));
  }

private:
  void timerCallback() override {
    float incoming = 0.0f;
    if (levelProvider) {
      incoming = juce::jlimit(0.0f, 1.0f, levelProvider());
    }
    smoothedLevel = (smoothedLevel * 0.84f) + (incoming * 0.16f);
    phase += 0.09f + smoothedLevel * 0.28f;
    repaint();
  }

  juce::Image frameImg;
  juce::Image gridImg;
  juce::Image glowImg;

  std::function<float()> levelProvider;
  float smoothedLevel = 0.0f;
  float phase = 0.0f;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VisualFeedbackView)
};

} // namespace ui
} // namespace dnb_bass
