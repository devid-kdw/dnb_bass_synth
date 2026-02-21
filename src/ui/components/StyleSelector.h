#pragma once
#include "../theme/Theme.h"
#include <juce_gui_basics/juce_gui_basics.h>

namespace dnb_bass {
namespace ui {

class StyleSelector : public juce::Component {
public:
  StyleSelector() {
    addAndMakeVisible(label);
    label.setText("Style Mode", juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centredRight);
    label.setColour(juce::Label::textColourId, Theme::textPrimary);

    addAndMakeVisible(comboBox);
    comboBox.addItem("Tech", 1);
    comboBox.addItem("Neuro", 2);
    comboBox.addItem("Dark", 3);
  }

  void resized() override {
    auto bounds = getLocalBounds();
    label.setBounds(bounds.removeFromLeft(100).reduced(5, 0));
    comboBox.setBounds(bounds.reduced(0, 5));
  }

  juce::ComboBox &getComboBox() { return comboBox; }

private:
  juce::Label label;
  juce::ComboBox comboBox;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StyleSelector)
};

} // namespace ui
} // namespace dnb_bass
