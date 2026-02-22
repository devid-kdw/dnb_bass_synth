# UI Graphic Designer P8 Redesign Tasklist

Last updated: 2026-02-22  
Root: `/Users/grzzi/Desktop/dnb_bass_synth`

## 1. Mandatory Inputs
1. `docs/spec/ui_graphic_asset_contract.md`
2. `docs/qa/p8_gate_review.md`
3. `assets/ui/designer/p7/manifests/p7_ui_png_manifest.csv`
4. `assets/ui/designer/p7/manifests/p7_ui_control_asset_map.md`
5. Orchestrator-provided reference image path (inside repo)
6. All 4 knowledge docs under `knowledge/`

## 2. Redesign Scope
1. Redesign visual treatment of the existing asset pack only.
2. Keep contract invariants:
   - exactly 60 PNG files
   - canonical naming formula
   - canonical control IDs and mapping semantics
3. Keep macro-first hierarchy:
   - primary/performance: 4 macro controls
   - advanced: 6 macro controls

## 3. Constraints
1. No modifications in `src/`.
2. No new UI controls beyond existing manifest scope.
3. No count drift, no naming drift, no path drift.

## 4. Verification Checklist
1. PNG count in export folder equals 60.
2. Manifest row count equals 60 (excluding header).
3. Each manifest file exists on disk.
4. Naming regex from contract passes for all rows.

## 5. Required Output
1. Updated PNG package in `assets/ui/designer/p7/exports/png/`
2. Updated manifest `assets/ui/designer/p7/manifests/p7_ui_png_manifest.csv`
3. Updated map (if needed) `assets/ui/designer/p7/manifests/p7_ui_control_asset_map.md`
4. Preview board `assets/ui/designer/p7/previews/p8_redesign_before_after.png`
5. Handoff `docs/qa/design_phase_handoffs/P8_design_redesign_handoff.md`

