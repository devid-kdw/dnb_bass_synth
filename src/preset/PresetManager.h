#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_data_structures/juce_data_structures.h>

namespace dnb::preset {

class PresetManager {
public:
  /**
   * Serializes the current APVTS into an XML-formatted memory block,
   * embedding the current SchemaVersion tag to ensure forward compatibility.
   *
   * @param apvts The current processor state.
   * @param destData Block where the XML bytes are written.
   */
  static void saveStateInformation(juce::AudioProcessorValueTreeState &apvts,
                                   juce::MemoryBlock &destData);

  /**
   * Deserializes an XML block, passes it through the PresetMigration layer,
   * and if valid, restores it into the APVTS. Unknown fields are ignored.
   *
   * @param data Raw byte array.
   * @param sizeInBytes Size of array.
   * @param apvts The processor state to restore into.
   */
  static void loadStateInformation(const void *data, int sizeInBytes,
                                   juce::AudioProcessorValueTreeState &apvts);
};

} // namespace dnb::preset
