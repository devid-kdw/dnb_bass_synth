#include "PresetMigration.h"
#include "PresetSchema.h"
#include <string>

namespace dnb::preset {

bool PresetMigration::migrateToCurrent(juce::ValueTree &state) {
  if (!state.isValid() ||
      state.getType().toString() != juce::String(std::string(schema::presetTag))) {
    return false; // Not our preset format
  }

  // Attempt to read version, defaulting to 0 if missing.
  int version = state.getProperty(juce::String(std::string(schema::versionAttr)), 0);

  // Apply migrations sequentially
  if (version < 1) {
    migrateV0toV1(state);
    version = 1;
    // Update the version tag to reflect successful migration
    state.setProperty(juce::String(std::string(schema::versionAttr)), version, nullptr);
  }

  // Future migrations can be chained here:
  // if (version < 2) { migrateV1toV2(state); version = 2; ... }

  return true;
}

void PresetMigration::migrateV0toV1(juce::ValueTree &state) {
  if (state.getNumChildren() == 0)
    return;
  auto innerTree = state.getChild(0);

  // Proper APVTS traversal for old parameter keys inside the inner tree
  for (int i = 0; i < innerTree.getNumChildren(); ++i) {
    auto child = innerTree.getChild(i);
    if (child.getType().toString() == "PARAM") {
      auto idString = child.getProperty("id").toString();

      if (idString == "macro.roller_dyn") {
        child.setProperty("id", juce::String(std::string(keys::macroRollerDynamics)), nullptr);
      }

      // Cleanup dead nodes so they don't pollute the new tree
      if (idString == "sub.shape" || idString == "sub.phase" || idString == "sys.xover" ||
          idString == "osc.fm.ratio" || idString == "fx.ott.mix") {
        // Ignored by APVTS
      }
    }
  }
}

} // namespace dnb::preset
