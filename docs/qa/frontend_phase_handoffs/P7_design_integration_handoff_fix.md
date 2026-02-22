# P7 Design Integration Handoff Fix

Status: `Review`  
Phase: `P7`  
Agent: Frontend/UI  
Date: 2026-02-22  
Proposed status transition: `Review`

## 1. Changed Files
- `src/ui/bindings/BindingLayer.h`
- `docs/qa/frontend_phase_handoffs/P7_design_integration_handoff.md`
- `docs/qa/frontend_phase_handoffs/P7_design_integration_handoff_fix.md`

## 2. Closure Map
| Finding ID | Closure | Evidence |
|---|---|---|
| `F-P7R-001` | Closed | `style.mode` binding in `src/ui/bindings/BindingLayer.h` replaced with deterministic 3-state attachment (`Tech=0`, `Neuro=1`, `Dark=2`) on APVTS choice param; bool `ButtonAttachment` semantics removed. |
| `F-P7R-002` | Closed | `docs/qa/frontend_phase_handoffs/P7_design_integration_handoff.md` replaced placeholder asset names with real manifest IDs, refreshed test outputs to exact current results (`45/45`), and includes full runtime control map. |

## 3. Runtime Evidence Map (`ui_control -> param_id -> asset_file`)

### 3.1 Global and visual surfaces
| UI Control ID | Param ID | Asset File(s) |
|---|---|---|
| `ui.root.background.main` | `n/a` | `ui_background_root_main_base_v001.png` |
| `ui.root.background.noise` | `n/a` | `ui_background_root_noise_base_v001.png` |
| `ui.panel.header_titleplate` | `n/a` | `ui_panel_header_titleplate_base_v001.png` |
| `ui.panel.macro_primary` | `n/a` | `ui_panel_macro_primary_frame_base_v001.png` |
| `ui.panel.macro_advanced` | `n/a` | `ui_panel_macro_advanced_frame_base_v001.png` |
| `ui.panel.style_selector` | `n/a` | `ui_panel_style_selector_frame_base_v001.png` |
| `ui.panel.style_morph` | `n/a` | `ui_panel_style_morph_frame_base_v001.png` |
| `ui.visual.scope.grid` | `n/a` | `ui_visual_scope_grid_main_base_v001.png` |
| `ui.visual.scope.wave_overlay` | `n/a` | `ui_visual_scope_wave_overlay_base_v001.png` |
| `ui.visual.scope.spectrum_overlay` | `n/a` | `ui_visual_scope_spectrum_overlay_base_v001.png` |
| `ui.visual.scope.frame_glow` | `n/a` | `ui_visual_scope_frame_glow_active_v001.png` |

### 3.2 APVTS-bound controls
| UI Control ID | Param ID | Asset File(s) |
|---|---|---|
| `ui.macro.primary.neuro_formant` | `macro.neuro_formant` | `ui_macro_knob_neuro_formant_idle_v001.png`, `ui_macro_knob_neuro_formant_hover_v001.png`, `ui_macro_knob_neuro_formant_active_v001.png` |
| `ui.macro.primary.fm_metal` | `macro.fm_metal` | `ui_macro_knob_fm_metal_idle_v001.png`, `ui_macro_knob_fm_metal_hover_v001.png`, `ui_macro_knob_fm_metal_active_v001.png` |
| `ui.macro.primary.roller_dynamics` | `macro.roller_dynamics` | `ui_macro_knob_roller_dynamics_idle_v001.png`, `ui_macro_knob_roller_dynamics_hover_v001.png`, `ui_macro_knob_roller_dynamics_active_v001.png` |
| `ui.macro.primary.liquid_depth` | `macro.liquid_depth` | `ui_macro_knob_liquid_depth_idle_v001.png`, `ui_macro_knob_liquid_depth_hover_v001.png`, `ui_macro_knob_liquid_depth_active_v001.png` |
| `ui.macro.advanced.sub_punch` | `macro.sub_punch` | `ui_macro_knob_sub_punch_idle_v001.png`, `ui_macro_knob_sub_punch_hover_v001.png`, `ui_macro_knob_sub_punch_active_v001.png` |
| `ui.macro.advanced.fm_pressure` | `macro.fm_pressure` | `ui_macro_knob_fm_pressure_idle_v001.png`, `ui_macro_knob_fm_pressure_hover_v001.png`, `ui_macro_knob_fm_pressure_active_v001.png` |
| `ui.macro.advanced.cutoff_motion` | `macro.cutoff_motion` | `ui_macro_knob_cutoff_motion_idle_v001.png`, `ui_macro_knob_cutoff_motion_hover_v001.png`, `ui_macro_knob_cutoff_motion_active_v001.png` |
| `ui.macro.advanced.fold_bite` | `macro.fold_bite` | `ui_macro_knob_fold_bite_idle_v001.png`, `ui_macro_knob_fold_bite_hover_v001.png`, `ui_macro_knob_fold_bite_active_v001.png` |
| `ui.macro.advanced.table_drift` | `macro.table_drift` | `ui_macro_knob_table_drift_idle_v001.png`, `ui_macro_knob_table_drift_hover_v001.png`, `ui_macro_knob_table_drift_active_v001.png` |
| `ui.macro.advanced.smash_glue` | `macro.smash_glue` | `ui_macro_knob_smash_glue_idle_v001.png`, `ui_macro_knob_smash_glue_hover_v001.png`, `ui_macro_knob_smash_glue_active_v001.png` |
| `ui.style.mode.tech` | `style.mode` | `ui_style_mode_tech_idle_v001.png`, `ui_style_mode_tech_selected_v001.png`, `ui_style_mode_tech_disabled_v001.png` |
| `ui.style.mode.neuro` | `style.mode` | `ui_style_mode_neuro_idle_v001.png`, `ui_style_mode_neuro_selected_v001.png`, `ui_style_mode_neuro_disabled_v001.png` |
| `ui.style.mode.dark` | `style.mode` | `ui_style_mode_dark_idle_v001.png`, `ui_style_mode_dark_selected_v001.png`, `ui_style_mode_dark_disabled_v001.png` |
| `ui.style_morph.slider` | `macro.style_morph` | `ui_style_morph_track_main_base_v001.png`, `ui_style_morph_thumb_main_base_v001.png`, `ui_style_morph_glow_main_active_v001.png` |

## 4. Test Commands and Results
1. `tools/scripts/init_submodules.sh`
   - Result: pass (`[init_submodules] done`)
2. `cmake --build build --parallel`
   - Result: pass (`[100%] Built target DnBBassSynth_VST3`)
3. `cd build && ctest --output-on-failure`
   - Result: pass (`100% tests passed, 0 tests failed out of 45`)

## 5. Contract Checks
1. No legacy morph parameter ID reference in frontend runtime binding code.
   - Command: `rg -n "(^|[^A-Za-z0-9_])style[.]morph([^A-Za-z0-9_]|$)" src/ui src/app`
   - Result: empty output (pass)
2. All asset files referenced in this handoff map exist in `assets/ui/designer/p7/manifests/p7_ui_png_manifest.csv`.
   - Result: pass (`53/53` referenced assets found in manifest)

## 6. Architecture Boundary Confirmation
- No runtime UI -> DSP bypass introduced.
- APVTS remains the single frontend write path (`BindingLayer` attachments only).
- Domain contract IDs preserved (`style.mode`, `macro.style_morph`, `macro.*`).
- No dead APVTS controls in frontend scope (`14/14` bound controls are live).

## Status
Status proposed: **Review**.
