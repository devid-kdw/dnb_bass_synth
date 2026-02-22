# Frontend UI P8 Kickoff Tasklist

Last updated: 2026-02-22  
Root: `/Users/grzzi/Desktop/dnb_bass_synth`

## 1. Mandatory Inputs
1. `docs/qa/p7_post_gate_daw_hotfix_review.md`
2. `docs/qa/p7_final_gate_review.md`
3. `docs/master_implementation_plan.md`
4. `docs/implementation_plan.md`
5. `docs/project_rules.md`
6. `docs/spec/ui_graphic_asset_contract.md`
7. `docs/qa/current_version_daw_test_checklist.md`
8. `docs/agent_briefs/frontend_ui_agent_brief.md`
9. `docs/agent_briefs/frontend_ui_phase_tasklist.md`
10. `assets/ui/designer/p7/manifests/p7_ui_png_manifest.csv`
11. `assets/ui/designer/p7/manifests/p7_ui_control_asset_map.md`
12. `src/ui/bindings/BindingLayer.h`
13. `src/ui/components/ImageSlider.h`
14. `src/ui/components/VisualFeedbackView.h`
15. `.github/workflows/ci.yml`
16. `knowledge/DNB Bass Synth VST Plugin Research.pdf`
17. `knowledge/DNB bass synth document for developer.pdf`
18. `knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx`
19. `knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx`

## 2. P8 Frontend Scope (Support)

### 2.1 Frontend contract checks for CI
1. Ensure CI validates canonical parameter IDs for UI bindings.
2. Ensure legacy ID regressions are blocked (no `style.morph` usage).
3. Ensure style contract remains canonical (`Tech`, `Neuro`, `Dark`).

### 2.2 Asset integrity checks for CI
1. Ensure runtime used PNG assets are present in manifest.
2. Ensure no missing/dead UI state assets for in-scope controls.
3. Keep designer/runtime mapping deterministic.

### 2.3 DAW regression guard checks
1. Ensure knob endpoint behavior remains correct at `0%` and `100%`.
2. Ensure center visual panel does not regress into static/runtime overlay overlap.
3. Ensure checks are documented as reproducible CI or QA commands.

## 3. Constraints
1. No work outside `/Users/grzzi/Desktop/dnb_bass_synth`.
2. No new dependencies.
3. No runtime UI->DSP bypass.
4. No scope creep beyond P8 CI/CD and release hardening support.

## 4. Verification
1. `tools/scripts/init_submodules.sh`
2. `cmake --build build --parallel`
3. `cd build && ctest --output-on-failure`
4. Contract checks (example):
   - `rg -n "(^|[^A-Za-z0-9_])style[.]morph([^A-Za-z0-9_]|$)" src/ui src/app docs/qa`
5. Asset checks (example):
   - validate all runtime referenced assets exist in `assets/ui/designer/p7/manifests/p7_ui_png_manifest.csv`

## 5. Required Output
Create handoff:
- `docs/qa/frontend_phase_handoffs/P8_handoff.md`

Handoff must include:
1. changed files
2. closure map for frontend P8 scope
3. exact contract/asset/CI commands and results
4. confirmation: no runtime bypass and no dead controls
5. known limitations/open questions
6. proposed status: `Review`
