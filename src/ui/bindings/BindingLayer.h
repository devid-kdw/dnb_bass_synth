#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include <memory>
#include <vector>

#include "../../domain/ParameterSpec.h"
#include "../components/MacroPanel.h"
#include "../components/StyleMorphControl.h"
#include "../components/StyleSelector.h"

namespace dnb_bass {
namespace ui {

// Handles the JUCE APVTS SliderAttachment lifecycle for UI elements.
// Restricts binding only to domain-sanctioned string IDs.
class BindingLayer {
public:
  BindingLayer(juce::AudioProcessorValueTreeState &vts, MacroPanel &macroPanel,
               StyleMorphControl &styleMorph, StyleSelector &styleSelector)
      : apvts(vts) {
    using namespace dnb::domain::parameters;

    // 1. Bind Macros
    bindSlider(macroPanel.getSlider(MacroPanel::NeuroFormant),
               std::string(macroNeuroFormant.id));
    bindSlider(macroPanel.getSlider(MacroPanel::FmMetal),
               std::string(macroFmMetal.id));
    bindSlider(macroPanel.getSlider(MacroPanel::RollerDynamics),
               std::string(macroRollerDyn.id));
    bindSlider(macroPanel.getSlider(MacroPanel::LiquidDepth),
               std::string(macroLiquidDepth.id));

    // 2. Bind Style Morph Slider
    bindSlider(styleMorph.getSlider(), std::string(macroStyleMorph.id));

    // 3. Bind Style Selector
    bindComboBox(styleSelector.getComboBox(), std::string(styleMode.id));
  }

private:
  void bindSlider(juce::Slider &slider, const std::string &paramID) {
    sliderAttachments.push_back(
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            apvts, juce::String(paramID), slider));
  }

  void bindComboBox(juce::ComboBox &comboBox, const std::string &paramID) {
    comboBoxAttachments.push_back(
        std::make_unique<
            juce::AudioProcessorValueTreeState::ComboBoxAttachment>(
            apvts, juce::String(paramID), comboBox));
  }

  juce::AudioProcessorValueTreeState &apvts;
  std::vector<
      std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>>
      sliderAttachments;
  std::vector<
      std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment>>
      comboBoxAttachments;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BindingLayer)
};

} // namespace ui
} // namespace dnb_bass
