# P7 Design Handoff Fix

Status: `Review`  
Phase: `P7`  
Agent: UI Graphic Designer  
Date: 2026-02-22  
Proposed status transition: `Planned -> Review`

## 1. Remediation Scope
- Closed design mapping blocker before frontend P7 start.
- No PNG redesign, no file count/naming changes.

## 2. Changed Files
- `assets/ui/designer/p7/manifests/p7_ui_control_asset_map.md`
- `docs/qa/design_phase_handoffs/P7_design_handoff.md`
- `docs/qa/design_phase_handoffs/P7_design_handoff_fix.md`

## 3. Blocker Closure Map
- `style.morph` -> `macro.style_morph` for:
  - `ui.style.morph.track`
  - `ui.style.morph.thumb`
  - `ui.style.morph.glow`
- Decorative panel binding cleanup:
  - `ui.panel.style_morph` Param ID set to `n/a`

## 4. Verification Commands and Results
1. No legacy ID left in control map (exact token check):
```bash
rg -n '`style\.morph`' /Users/grzzi/Desktop/dnb_bass_synth/assets/ui/designer/p7/manifests/p7_ui_control_asset_map.md
```
Result: empty output (pass)

2. Canonical ID exists for morph controls:
```bash
rg -n 'macro\.style_morph' /Users/grzzi/Desktop/dnb_bass_synth/assets/ui/designer/p7/manifests/p7_ui_control_asset_map.md
```
Result:
- line 43: `ui.style.morph.track` -> `macro.style_morph`
- line 44: `ui.style.morph.thumb` -> `macro.style_morph`
- line 45: `ui.style.morph.glow` -> `macro.style_morph`

3. PNG package count unchanged:
```bash
find /Users/grzzi/Desktop/dnb_bass_synth/assets/ui/designer/p7/exports/png -type f -name '*.png' | wc -l
```
Result: `60`

## 5. Compliance Confirmation
- PNG count remains exactly `60`: `YES`
- Naming formula unchanged: `YES`
- No scope creep / no redesign changes: `YES`
- `src/` code untouched (read-only canonical ID check only): `YES`
