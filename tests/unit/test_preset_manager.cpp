#include "../../src/domain/ParameterSpec.h"
#include "../../src/preset/PresetManager.h"
#include "../../src/preset/PresetSchema.h"
#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <juce_audio_processors/juce_audio_processors.h>
#include <nlohmann/json.hpp>

using namespace dnb::preset;
using namespace dnb::domain::parameters;

// Helper to create a dummy APVTS layout for testing
juce::AudioProcessorValueTreeState::ParameterLayout createDummyLayout() {
  juce::AudioProcessorValueTreeState::ParameterLayout layout;
  layout.add(std::make_unique<juce::AudioParameterFloat>(
      juce::ParameterID{juce::String(std::string(ampAttack.id)), 1},
      juce::String(std::string(ampAttack.name)),
      juce::NormalisableRange<float>(ampAttack.minVal, ampAttack.maxVal, 0.1f),
      ampAttack.defaultVal));
  layout.add(std::make_unique<juce::AudioParameterFloat>(
      juce::ParameterID{juce::String(std::string(macroRollerDyn.id)), 1},
      juce::String(std::string(macroRollerDyn.name)),
      juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.0f));
  return layout;
}

class DummyProcessor : public juce::AudioProcessor {
public:
  DummyProcessor() : apvts(*this, nullptr, "Parameters", createDummyLayout()) {}

  const juce::String getName() const override {
    return "Dummy";
  }
  void prepareToPlay(double, int) override {}
  void releaseResources() override {}
  void processBlock(juce::AudioBuffer<float> &, juce::MidiBuffer &) override {}
  juce::AudioProcessorEditor *createEditor() override {
    return nullptr;
  }
  bool hasEditor() const override {
    return false;
  }
  bool acceptsMidi() const override {
    return false;
  }
  bool producesMidi() const override {
    return false;
  }
  double getTailLengthSeconds() const override {
    return 0.0;
  }
  int getNumPrograms() override {
    return 1;
  }
  int getCurrentProgram() override {
    return 0;
  }
  void setCurrentProgram(int) override {}
  const juce::String getProgramName(int) override {
    return {};
  }
  void changeProgramName(int, const juce::String &) override {}
  void getStateInformation(juce::MemoryBlock &) override {}
  void setStateInformation(const void *, int) override {}

  juce::AudioProcessorValueTreeState apvts;
};

TEST_CASE("PresetManager Save and Load Roundtrip", "[preset]") {
  DummyProcessor proc1;
  DummyProcessor proc2;

  // Set non-default values in proc1
  proc1.apvts.getParameter(juce::String(std::string(ampAttack.id)))->setValueNotifyingHost(0.5f);
  proc1.apvts.getParameter(juce::String(std::string(macroRollerDyn.id)))
      ->setValueNotifyingHost(0.7f);

  // Save state
  juce::MemoryBlock data;
  PresetManager::saveStateInformation(proc1.apvts, data);
  REQUIRE(data.getSize() > 0);

  // Load state into proc2
  PresetManager::loadStateInformation(data.getData(), data.getSize(), proc2.apvts);

  // Values should match
  float attack2 = proc2.apvts.getParameter(juce::String(std::string(ampAttack.id)))->getValue();
  float roller2 =
      proc2.apvts.getParameter(juce::String(std::string(macroRollerDyn.id)))->getValue();

  REQUIRE(attack2 == Catch::Approx(0.5f));
  REQUIRE(roller2 == Catch::Approx(0.7f));
}

TEST_CASE("PresetMigration Legacy Up-conversion", "[preset]") {
  DummyProcessor proc;

  // Create a raw APVTS XML matching what older versions of JUCE would save
  // directly
  proc.apvts.getParameter(juce::String(std::string(ampAttack.id)))->setValueNotifyingHost(0.8f);

  // Notice we use the old ID name "macro.roller_dyn" here for legacy compat
  // test Because it's not in our dummy layout, we inject it directly into a
  // ValueTree
  auto rawTree = proc.apvts.copyState();

  juce::ValueTree oldParam("PARAM");
  oldParam.setProperty("id", "macro.roller_dyn", nullptr);
  oldParam.setProperty("value", 0.4f, nullptr);
  rawTree.addChild(oldParam, -1, nullptr);

  // Serialize literal XML
  std::unique_ptr<juce::XmlElement> xml(rawTree.createXml());
  juce::String xmlString = xml->toString();
  juce::MemoryBlock data(xmlString.toRawUTF8(), xmlString.getNumBytesAsUTF8());

  // Load into APVTS using PresetManager, which should trigger V0 -> V1
  // migration
  PresetManager::loadStateInformation(data.getData(), data.getSize(), proc.apvts);

  float attack = proc.apvts.getParameter(juce::String(std::string(ampAttack.id)))->getValue();
  float roller = proc.apvts.getParameter(juce::String(std::string(macroRollerDyn.id)))->getValue();

  REQUIRE(attack == Catch::Approx(0.8f));

  // If migration succeeded, the old "macro.roller_dyn" was mapped to the active
  // "macro.roller_dynamics" ID and successfully recovered.
  REQUIRE(roller == Catch::Approx(0.4f));
}

TEST_CASE("PresetManager graceful handling of corrupt XML/data", "[preset]") {
  DummyProcessor proc;

  // Store default attack
  float defaultAttack =
      proc.apvts.getParameter(juce::String(std::string(ampAttack.id)))->getValue();

  const char *badData = "<InvalidXML>>///";

  // Should not crash, should simply do nothing
  PresetManager::loadStateInformation(badData, strlen(badData), proc.apvts);

  // Values should be unchanged
  float currentAttack =
      proc.apvts.getParameter(juce::String(std::string(ampAttack.id)))->getValue();
  REQUIRE(currentAttack == defaultAttack);
}

TEST_CASE("PresetManager gracefully ignores unknown fields and parameters", "[preset]") {
  DummyProcessor proc;

  // Set up valid parameter load expectation
  proc.apvts.getParameter(juce::String(std::string(ampAttack.id)))->setValueNotifyingHost(0.5f);
  auto rawTree = proc.apvts.copyState();

  // Inject a completely unknown parameter
  juce::ValueTree unknownParam("PARAM");
  unknownParam.setProperty("id", "macro.non_existent_future_param", nullptr);
  unknownParam.setProperty("value", 0.99f, nullptr);
  rawTree.addChild(unknownParam, -1, nullptr);

  // Wrap it properly
  juce::ValueTree wrapper{juce::Identifier(juce::String(std::string(schema::presetTag)))};
  wrapper.setProperty(juce::String(std::string(schema::versionAttr)), 1, nullptr);
  wrapper.addChild(rawTree, -1, nullptr);

  std::unique_ptr<juce::XmlElement> xml(wrapper.createXml());

  // Create malicious/future JSON with unknown outer fields
  nlohmann::json root;
  root["plugin_version"] = "1.0.0";
  root["schema_version"] = 1;
  root["unknown_random_field"] = "should be ignored";
  root["state_xml"] = xml->toString().toStdString();

  std::string jsonStr = root.dump();

  // Reset processor before loading
  proc.apvts.getParameter(juce::String(std::string(ampAttack.id)))->setValueNotifyingHost(0.0f);

  // Attempt load - must not crash, must skip unknown JSON fields, must skip
  // unknown XML params
  PresetManager::loadStateInformation(jsonStr.c_str(), jsonStr.size(), proc.apvts);

  // Valid parameter must be accurately loaded
  float attack = proc.apvts.getParameter(juce::String(std::string(ampAttack.id)))->getValue();
  REQUIRE(attack == Catch::Approx(0.5f));
}

TEST_CASE("PresetManager saveState outputs canonical plugin version", "[preset]") {
  DummyProcessor proc;
  juce::MemoryBlock data;
  PresetManager::saveStateInformation(proc.apvts, data);

  std::string_view rawData(static_cast<const char *>(data.getData()), data.getSize());
  auto root = nlohmann::json::parse(rawData);

  REQUIRE(root.contains("plugin_version"));
  REQUIRE(root["plugin_version"].get<std::string>() == std::string(schema::pluginVersion));
}
