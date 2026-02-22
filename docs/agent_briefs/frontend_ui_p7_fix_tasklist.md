# Frontend UI P7 Fix Tasklist

Last updated: 2026-02-22  
Root: `/Users/grzzi/Desktop/dnb_bass_synth`

## 1. Mandatory Inputs
1. `docs/qa/p7_fix_review.md`
2. `docs/master_implementation_plan.md`
3. `docs/project_rules.md`
4. `docs/spec/ui_graphic_asset_contract.md`
5. `docs/agent_briefs/frontend_ui_agent_brief.md`
6. `docs/qa/frontend_phase_handoffs/P7_design_integration_handoff.md`
7. `docs/qa/design_phase_handoffs/P7_design_handoff.md`
8. `docs/qa/design_phase_handoffs/P7_design_handoff_fix.md`
9. `assets/ui/designer/p7/manifests/p7_ui_png_manifest.csv`
10. `assets/ui/designer/p7/manifests/p7_ui_control_asset_map.md`
11. `src/domain/ParameterSpec.h`

## 2. Fix Scope
### 2.1 Close `F-P7R-001`
1. Fix style mode UI binding semantics for `style.mode` (3-state mapping).
2. Keep canonical style order: `Tech=0`, `Neuro=1`, `Dark=2`.
3. Keep morph binding canonical: `macro.style_morph`.

### 2.2 Close `F-P7R-002`
1. Correct P7 frontend handoff evidence with real runtime asset IDs.
2. Replace stale/inaccurate test counts with actual command outputs.
3. Include complete mapping table:
   - `ui_control -> param_id -> asset_file`

## 3. Verification
1. `tools/scripts/init_submodules.sh`
2. `cmake --build build --parallel`
3. `cd build && ctest --output-on-failure`
4. Contract checks:
   - no legacy `style.morph` in frontend binding/mapping docs
   - all asset files referenced by frontend handoff exist in manifest

## 4. Required Output
Create fix handoff:
- `docs/qa/frontend_phase_handoffs/P7_design_integration_handoff_fix.md`

Handoff must include:
1. changed files
2. closure map for `F-P7R-001`, `F-P7R-002`
3. exact test commands + exact results
4. evidence table `ui_control -> param_id -> asset_file`
5. confirmation: no runtime bypass, no dead controls
6. proposed status: `Review`
