#pragma once

#include <juce_data_structures/juce_data_structures.h>

namespace dnb::preset {

class PresetMigration {
public:
  /**
   * Applies necessary migrations to bring the given state tree up to the
   * current schema version definition.
   *
   * @param state The ValueTree containing the loaded preset state.
   * @return true if the migration was successful or not needed, false if
   * corrupted/unrecoverable.
   */
  static bool migrateToCurrent(juce::ValueTree &state);

private:
  static void migrateV0toV1(juce::ValueTree &state);
};

} // namespace dnb::preset
