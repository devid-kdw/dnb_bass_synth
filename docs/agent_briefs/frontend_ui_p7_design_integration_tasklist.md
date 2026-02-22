# Frontend P7 Design Integration Tasklist

Last updated: 2026-02-22  
Root: `/Users/grzzi/Desktop/dnb_bass_synth`

## 1. Inputs
Mandatory inputs:
1. `docs/spec/ui_graphic_asset_contract.md`
2. `docs/qa/design_phase_handoffs/P7_design_handoff.md`
3. `assets/ui/designer/p7/manifests/p7_ui_png_manifest.csv`
4. `assets/ui/designer/p7/manifests/p7_ui_control_asset_map.md`
5. `docs/agent_briefs/frontend_ui_agent_brief.md`
6. `docs/project_rules.md`

## 2. Implementation Steps
1. Validate manifest count and naming compliance before code changes.
2. Integrate approved assets from `assets/ui/designer/p7/exports/png/`.
3. Populate runtime asset path under `assets/ui/runtime/p7/`.
4. Implement asset-loading/wiring in UI layer without bypassing APVTS/domain.
5. Keep macro-first hierarchy:
   - 4 primary macros visually dominant
   - 6 advanced macros visually secondary
6. Keep style controls canonical: `Tech`, `Neuro`, `Dark`.

## 3. Validation
1. Confirm each used file exists in designer manifest.
2. Confirm no UI control references missing PNG states.
3. Build and test:
   - `tools/scripts/init_submodules.sh`
   - `cmake --build build --parallel`
   - `cd build && ctest --output-on-failure`

## 4. Required Output
Create handoff:
- `docs/qa/frontend_phase_handoffs/P7_design_integration_handoff.md`

Handoff must include:
1. changed files
2. `ui_control -> param_id -> asset_file` mapping
3. manifest compliance confirmation
4. known visual or technical limitations
5. proposed status transition (`Planned -> Review`)
