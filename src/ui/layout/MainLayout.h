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
    bgImg = juce::ImageCache::getFromMemory(UIAssets::ui_background_root_main_base_v001_png,
                                            UIAssets::ui_background_root_main_base_v001_pngSize);

    noiseImg =
        juce::ImageCache::getFromMemory(UIAssets::ui_background_root_noise_base_v001_png,
                                        UIAssets::ui_background_root_noise_base_v001_pngSize);

    titlePlateImg =
        juce::ImageCache::getFromMemory(UIAssets::ui_panel_header_titleplate_base_v001_png,
                                        UIAssets::ui_panel_header_titleplate_base_v001_pngSize);

    addAndMakeVisible(styleSelector);
    addAndMakeVisible(styleMorph);
    addAndMakeVisible(visualFeedback);
    addAndMakeVisible(macroPanel);
  }

  void resized() override {
    auto bounds = getLocalBounds().reduced(20, 22);

    const int sectionGap = 12;
    const int centeredWidth = juce::jmax(420, juce::jmin(bounds.getWidth() - 90, 760));

    titlePlateBounds = bounds.removeFromTop(52)
                           .withWidth(centeredWidth)
                           .withX(bounds.getX() + (bounds.getWidth() - centeredWidth) / 2);
    bounds.removeFromTop(sectionGap);

    styleSelector.setBounds(bounds.removeFromTop(92)
                                .withWidth(centeredWidth)
                                .withX(bounds.getX() + (bounds.getWidth() - centeredWidth) / 2));
    bounds.removeFromTop(sectionGap);

    styleMorph.setBounds(bounds.removeFromTop(82)
                             .withWidth(centeredWidth)
                             .withX(bounds.getX() + (bounds.getWidth() - centeredWidth) / 2));
    bounds.removeFromTop(sectionGap);

    visualFeedback.setBounds(bounds.removeFromTop(170)
                                 .withWidth(centeredWidth)
                                 .withX(bounds.getX() + (bounds.getWidth() - centeredWidth) / 2));
    bounds.removeFromTop(sectionGap);

    macroPanel.setBounds(bounds.reduced(6, 0));
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

    g.setFont(juce::Font(18.0f, juce::Font::bold));
    g.setColour(juce::Colours::white.withAlpha(0.92f));
    g.drawFittedText("DnB Bass Synth", titlePlateBounds.reduced(18, 6),
                     juce::Justification::centredLeft, 1);
  }

  StyleMorphControl &getStyleMorphControl() {
    return styleMorph;
  }
  StyleSelector &getStyleSelector() {
    return styleSelector;
  }
  MacroPanel &getMacroPanel() {
    return macroPanel;
  }
  VisualFeedbackView &getVisualFeedbackView() {
    return visualFeedback;
  }

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
