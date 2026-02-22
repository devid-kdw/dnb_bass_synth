# P6 Alignment Audit (Pre-Gate)

Date: 2026-02-22  
Reviewer: Orchestrator  
Scope: P6 implementation vs. master plan + 4 knowledge docs

## 1. Source of Truth Used
1. `knowledge/DNB Bass Synth VST Plugin Research.pdf`
2. `knowledge/DNB bass synth document for developer.pdf`
3. `knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx`
4. `knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx`
5. `docs/project_rules.md`
6. `docs/master_implementation_plan.md`

## 2. Validation Snapshot
1. `tools/scripts/init_submodules.sh` -> PASS
2. `cmake --build build --parallel` -> PASS
3. `cd build && ctest --output-on-failure` -> PASS (`32/32`)

## 3. Findings

### F-P6A-001 - JSON migration layer missing (High)
Problem:
- P6 preset/state currently uses ValueTree + XML only.
- Knowledge stack requires explicit ValueTree + JSON migration layer.

Evidence:
- `src/preset/PresetManager.cpp`
- `src/preset/PresetMigration.cpp`
- `docs/qa/knowledge_extract/techstack_fresh.txt` (state serialization requirements)

Required closure:
- Add explicit JSON-backed migration path in preset/state pipeline (without breaking current host state flow).

### F-P6A-002 - Plugin version tag not persisted in state payload (High)
Problem:
- State wrapper stores schema version only; plugin version tag is missing.

Evidence:
- `src/preset/PresetSchema.h`
- `src/preset/PresetManager.cpp`
- `docs/qa/knowledge_extract/supplement_fresh.txt` (state version tagging requirement)

Required closure:
- Persist plugin version in serialized state and verify on load path.

### F-P6A-003 - Unknown-field forward-compat behavior not explicitly test-covered (Medium)
Problem:
- Corrupt data and legacy rename are tested, but unknown param/node tolerance has no explicit dedicated test.

Evidence:
- `tests/unit/test_preset_manager.cpp`
- `docs/qa/knowledge_extract/supplement_fresh.txt` (unknown params should be ignored)

Required closure:
- Add dedicated tests that inject unknown parameters/fields and prove safe ignore behavior.

### F-P6A-004 - MVP macro target drift (High)
Problem:
- Knowledge documents describe MVP target with 10 core macros, while active contract remains 4 macros (+ style morph).
- Current state must be explicitly aligned: either implemented now or formally deferred with ADR and plan update.

Evidence:
- `src/domain/ParameterSpec.h`
- `src/app/PluginProcessor.cpp`
- `docs/spec/p1_schema_freeze.md`
- `docs/qa/knowledge_extract/knowledge_pdf_extract_fresh.txt`

Required closure:
- Produce canonical MVP macro contract doc from knowledge sources.
- Close drift via one approved path:
  1. implement full MVP macro contract, or
  2. ADR-backed defer with explicit plan/risk update and no false MVP-ready claim.

### F-P6A-005 - P6 handoff integrity mismatches (Low)
Problem:
- Frontend P6 handoff contains `Neurofunk` naming in a canonical MVP context.
- Backend P6 handoff text includes inaccurate wrapper naming.

Evidence:
- `docs/qa/frontend_phase_handoffs/P6_handoff.md`
- `docs/qa/backend_phase_handoffs/P6_handoff.md`

Required closure:
- Correct both handoffs with evidence-backed wording only.

## 4. Gate Decision
P6 remains at `Review` and cannot be accepted as `Done` until `F-P6A-001`..`F-P6A-005` are closed and re-verified.

