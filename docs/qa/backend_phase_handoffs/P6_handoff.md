# Phase 6 Handoff: Preset / State & Migration Layer

## Overview
This document marks the completion of the Phase 6 (P6) Preset layer implementation. The objective of P6 was to establish a robust, versioned state persistence mechanism that embeds a schema version in saved DAW projects and presets. This ensures long-term backward and forward compatibility as the synth's parameter schema evolves.

## Implementations details
- **Schema Management (`PresetSchema.h`)**: Defines current schema version (`currentVersion = 1`), XML wrapper tag (`DnBBassSynthState`) embedded in JSON payload, and canonical parameter IDs (e.g., `keys::macroRollerDynamics`, `keys::styleMode`).
- **Migration Engine (`PresetMigration.h/cpp`)**: intercepts loaded states. If a state lacks the version tag (V0), it applies `migrateV0toV1()`. This up-conversion specifically targets the P5 renaming of `macro.roller_dyn` to `macro.roller_dynamics`.
- **Serialization logic (`PresetManager.h/cpp`)**: Uses a JSON wrapper format (saving `plugin_version`, `schema_version`, and `state_xml`). Safely decodes both JSON format and legacy raw APVTS XML formats on load to avoid breaking backwards compatibility or causing fatal host crashes.
- **Plugin Integration**: In `PluginProcessor.cpp`, `getStateInformation` and `setStateInformation` have been wired to the `PresetManager` layer.

## Tests & Verification
- Unit test `PresetManager Save and Load Roundtrip` verifies that arbitrary values properly serialize and deserialize with the new JSON wrapper.
- Unit test `PresetMigration Legacy Up-conversion` synthesizes a V0 APVTS state with a deprecated ID (`macro.roller_dyn`) and verifies that `PresetManager` migrates the active parameter (`macro.roller_dynamics`) with the legacy value.
- Unit test `PresetManager graceful handling of corrupt XML/data` ensures that invalid XML strings fail safely without altering current plugin state or causing fatal host crashes.
- Command executed for testing: `ctest -R Preset` inside `/build`.

## Open Risks
- No significant immediate risks were identified.
- Future complexity relies on diligently updating the `PresetMigration::migrateToCurrent` pipeline whenever new schemas are introduced (V1 -> V2, etc.).

## Next Steps
- Switch attention to P7 (Modulation/Macro Backend) or Frontend UI Integration depending on product goals.
