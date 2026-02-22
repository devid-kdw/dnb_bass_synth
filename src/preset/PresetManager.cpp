#include "PresetManager.h"
#include "PresetMigration.h"
#include "PresetSchema.h"
#include <nlohmann/json.hpp>
#include <string>

namespace dnb::preset {

void PresetManager::saveStateInformation(juce::AudioProcessorValueTreeState &apvts,
                                         juce::MemoryBlock &destData) {

  // 1. Get the current actual state from APVTS
  auto rawState = apvts.copyState();

  // 2. Wrap it inside our distinct namespace tag
  juce::ValueTree outerState{juce::Identifier(juce::String(std::string(schema::presetTag)))};

  // 3. Mark the version explicitly to protect loading
  outerState.setProperty(juce::String(std::string(schema::versionAttr)), schema::currentVersion,
                         nullptr);

  // 4. Attach the APVTS payload
  outerState.addChild(rawState, -1, nullptr);

  // 5. Serialize to XML block (RT-unsafe, must be called on message thread)
  std::unique_ptr<juce::XmlElement> xml(outerState.createXml());
  if (xml != nullptr) {
    auto data = xml->toString();

    // 6. Wrap in JSON as per P6 Alignment
    nlohmann::json root;
    root["plugin_version"] = schema::pluginVersion; // Assigned version tag
    root["schema_version"] = schema::currentVersion;
    root["state_xml"] = data.toStdString();

    std::string jsonStr = root.dump();
    destData.append(jsonStr.c_str(), jsonStr.size());
  }
}

void PresetManager::loadStateInformation(const void *data, int sizeInBytes,
                                         juce::AudioProcessorValueTreeState &apvts) {

  if (data == nullptr || sizeInBytes <= 0)
    return;

  std::string_view rawData(static_cast<const char *>(data), static_cast<size_t>(sizeInBytes));
  juce::String xmlString;

  // 1. Try to parse as JSON first (New Format)
  try {
    auto root = nlohmann::json::parse(rawData);
    if (root.contains("state_xml") && root["state_xml"].is_string()) {
      xmlString = juce::String(root["state_xml"].get<std::string>());
    } else {
      return; // Valid JSON but missing XML payload, treat as corrupted/empty.
    }
  } catch (const nlohmann::json::parse_error &) {
    // 2. Fallback: Parse as raw XML (Legacy V0 Format or pure corrupt data)
    xmlString = juce::String::createStringFromData(data, sizeInBytes);
  }

  // 3. Parse XML string into juce elements
  std::unique_ptr<juce::XmlElement> xmlState(juce::XmlDocument::parse(xmlString));

  if (xmlState != nullptr) {
    auto outerTree = juce::ValueTree::fromXml(*xmlState);

    // 4. Validate outer wrapper exists
    if (outerTree.isValid() &&
        outerTree.getType().toString() == juce::String(std::string(schema::presetTag))) {

      // 5. Apply schema migrations (V0/legacy to V1)
      if (PresetMigration::migrateToCurrent(outerTree)) {
        // 6. Extract nested APVTS payload
        auto innerTree = outerTree.getChildWithName(apvts.state.getType());

        if (innerTree.isValid()) {
          // APVTS safely ignores unexpected keys internally
          apvts.replaceState(innerTree);
        }
      }
    } else {
      // Fallback for V0 XML files saved before the PresetManager wrapper
      // existed Older versions just saved APVTS pure copyState() without our
      // wrapper
      if (outerTree.isValid() && outerTree.getType() == apvts.state.getType()) {

        // Wrap it so it can pass through the migration layer organically
        juce::ValueTree wrapper{juce::Identifier(juce::String(std::string(schema::presetTag)))};
        wrapper.setProperty(juce::String(std::string(schema::versionAttr)), 0, nullptr);
        wrapper.addChild(outerTree, -1, nullptr);

        if (PresetMigration::migrateToCurrent(wrapper)) {
          auto migratedInner = wrapper.getChildWithName(apvts.state.getType());
          if (migratedInner.isValid()) {
            apvts.replaceState(migratedInner);
          }
        }
      }
    }
  }
}

} // namespace dnb::preset
