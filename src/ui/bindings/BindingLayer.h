#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include <array>
#include <atomic>
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
    bindSlider(macroPanel.getSlider(MacroPanel::NeuroFormant), std::string(macroNeuroFormant.id));
    bindSlider(macroPanel.getSlider(MacroPanel::FmMetal), std::string(macroFmMetal.id));
    bindSlider(macroPanel.getSlider(MacroPanel::RollerDynamics), std::string(macroRollerDyn.id));
    bindSlider(macroPanel.getSlider(MacroPanel::LiquidDepth), std::string(macroLiquidDepth.id));
    bindSlider(macroPanel.getSlider(MacroPanel::SubPunch), std::string(macroSubPunch.id));
    bindSlider(macroPanel.getSlider(MacroPanel::FmPressure), std::string(macroFmPressure.id));
    bindSlider(macroPanel.getSlider(MacroPanel::CutoffMotion), std::string(macroCutoffMotion.id));
    bindSlider(macroPanel.getSlider(MacroPanel::FoldBite), std::string(macroFoldBite.id));
    bindSlider(macroPanel.getSlider(MacroPanel::TableDrift), std::string(macroTableDrift.id));
    bindSlider(macroPanel.getSlider(MacroPanel::SmashGlue), std::string(macroSmashGlue.id));

    // 2. Bind Style Morph Slider
    bindSlider(styleMorph.getSlider(), std::string(macroStyleMorph.id));

    // 3. Bind Style Selector to 3-state APVTS choice (Tech/Neuro/Dark)
    styleModeAttachment = std::make_unique<StyleModeAttachment>(
        apvts, juce::String(std::string(styleMode.id)), styleSelector.getTechButton(),
        styleSelector.getNeuroButton(), styleSelector.getDarkButton());
  }

private:
  class StyleModeAttachment : private juce::AudioProcessorValueTreeState::Listener,
                              private juce::AsyncUpdater {
  public:
    StyleModeAttachment(juce::AudioProcessorValueTreeState &state, const juce::String &paramID,
                        juce::ToggleButton &techButton, juce::ToggleButton &neuroButton,
                        juce::ToggleButton &darkButton)
        : apvts(state), styleModeParamID(paramID), buttons{&techButton, &neuroButton, &darkButton},
          styleParameter(apvts.getParameter(styleModeParamID)) {
      if (buttons[modeTech] != nullptr) {
        buttons[modeTech]->onClick = [this] { setStyleMode(modeTech); };
      }
      if (buttons[modeNeuro] != nullptr) {
        buttons[modeNeuro]->onClick = [this] { setStyleMode(modeNeuro); };
      }
      if (buttons[modeDark] != nullptr) {
        buttons[modeDark]->onClick = [this] { setStyleMode(modeDark); };
      }

      apvts.addParameterListener(styleModeParamID, this);
      syncButtons(getCurrentModeIndex());
    }

    ~StyleModeAttachment() override {
      cancelPendingUpdate();
      apvts.removeParameterListener(styleModeParamID, this);
      for (auto *button : buttons) {
        if (button != nullptr) {
          button->onClick = nullptr;
        }
      }
    }

  private:
    static constexpr int modeTech = 0;
    static constexpr int modeNeuro = 1;
    static constexpr int modeDark = 2;

    void setStyleMode(const int modeIndex) {
      if (styleParameter == nullptr) {
        return;
      }

      const int clampedIndex = juce::jlimit(modeTech, modeDark, modeIndex);
      if (getCurrentModeIndex() == clampedIndex) {
        syncButtons(clampedIndex);
        return;
      }

      const float normalizedValue = styleParameter->convertTo0to1(static_cast<float>(clampedIndex));
      styleParameter->beginChangeGesture();
      styleParameter->setValueNotifyingHost(normalizedValue);
      styleParameter->endChangeGesture();
      syncButtons(clampedIndex);
    }

    int getCurrentModeIndex() const {
      if (styleParameter == nullptr) {
        return modeTech;
      }

      const float plainValue = styleParameter->convertFrom0to1(styleParameter->getValue());
      return juce::jlimit(modeTech, modeDark, juce::roundToInt(plainValue));
    }

    void syncButtons(const int activeModeIndex) {
      juce::ScopedValueSetter<bool> syncingFlag(isSynchronizing, true);
      for (int i = modeTech; i <= modeDark; ++i) {
        if (auto *button = buttons[static_cast<size_t>(i)]) {
          button->setToggleState(i == activeModeIndex, juce::dontSendNotification);
        }
      }
    }

    void parameterChanged(const juce::String &parameterID, const float newValue) override {
      if (parameterID != styleModeParamID || styleParameter == nullptr) {
        return;
      }

      pendingModeIndex.store(juce::jlimit(modeTech, modeDark, juce::roundToInt(newValue)),
                             std::memory_order_relaxed);
      triggerAsyncUpdate();
    }

    void handleAsyncUpdate() override {
      if (!isSynchronizing) {
        syncButtons(pendingModeIndex.load(std::memory_order_relaxed));
      }
    }

    juce::AudioProcessorValueTreeState &apvts;
    juce::String styleModeParamID;
    std::array<juce::ToggleButton *, 3> buttons;
    juce::RangedAudioParameter *styleParameter = nullptr;
    std::atomic<int> pendingModeIndex{modeTech};
    bool isSynchronizing = false;
  };

  void bindSlider(juce::Slider &slider, const std::string &paramID) {
    sliderAttachments.push_back(
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            apvts, juce::String(paramID), slider));
  }

  juce::AudioProcessorValueTreeState &apvts;
  std::unique_ptr<StyleModeAttachment> styleModeAttachment;
  std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>>
      sliderAttachments;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BindingLayer)
};

} // namespace ui
} // namespace dnb_bass
