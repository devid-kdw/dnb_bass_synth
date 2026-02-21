#pragma once
#include <juce_audio_processors/juce_audio_processors.h>

namespace dnb_bass {
namespace ui {

// This is an interface-only binding layer designed for P2/P3.
// It will not perform actual runtime parameter lookups or listeners until P5.
class BindingLayerScaffold {
public:
  BindingLayerScaffold(juce::AudioProcessorValueTreeState &vts) : apvts(vts) {
    // P2 Rule: No direct reliance on non-frozen backend parameters.
    // We do NOT attempt to bind to 'macro.neuro_formant' or 'style.mode' yet.
    // The real bindings will be implemented in P5 when the contract is fully
    // stable.
  }

  ~BindingLayerScaffold() = default;

  // Future API shapes for P5 mapping
  /*
  void bindMacroKnob(juce::Slider& slider, const juce::String& paramID)
  {
      // Will create juce::AudioProcessorValueTreeState::SliderAttachment
  }

  void bindStyleSelector(juce::ComboBox& combo, const juce::String& paramID)
  {
      // Will create juce::AudioProcessorValueTreeState::ComboBoxAttachment
  }
  */

private:
  juce::AudioProcessorValueTreeState &apvts;
};

} // namespace ui
} // namespace dnb_bass
