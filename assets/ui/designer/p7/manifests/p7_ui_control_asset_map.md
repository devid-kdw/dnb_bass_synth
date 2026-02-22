# P7 UI Control -> Asset Map

Last updated: 2026-02-22  
Phase: P7  
Design mode: stylized neon navy (reference palette: cyan/magenta/amber)

## Global surfaces
| UI Control ID | Param ID | Asset File(s) | Notes |
|---|---|---|---|
| `ui.root.background.main` | `n/a` | `ui_background_root_main_base_v001.png` | Main shell background |
| `ui.root.background.noise` | `n/a` | `ui_background_root_noise_base_v001.png` | Secondary texture/noise layer |
| `ui.panel.header_titleplate` | `n/a` | `ui_panel_header_titleplate_base_v001.png` | Header frame plate |
| `ui.panel.macro_primary` | `n/a` | `ui_panel_macro_primary_frame_base_v001.png` | Frame for 4 primary macros |
| `ui.panel.macro_advanced` | `n/a` | `ui_panel_macro_advanced_frame_base_v001.png` | Frame for 6 advanced macros |
| `ui.panel.style_selector` | `n/a` | `ui_panel_style_selector_frame_base_v001.png` | Style mode button zone |
| `ui.panel.style_morph` | `n/a` | `ui_panel_style_morph_frame_base_v001.png` | Morph strip frame |
| `ui.panel.visual_feedback` | `n/a` | `ui_panel_visual_feedback_frame_base_v001.png` | Scope/feedback zone |

## Macro controls (primary surface: 4)
| UI Control ID | Param ID | Asset File(s) | Notes |
|---|---|---|---|
| `ui.macro.primary.neuro_formant` | `macro.neuro_formant` | `ui_macro_knob_neuro_formant_idle_v001.png`, `ui_macro_knob_neuro_formant_hover_v001.png`, `ui_macro_knob_neuro_formant_active_v001.png` | Primary macro |
| `ui.macro.primary.fm_metal` | `macro.fm_metal` | `ui_macro_knob_fm_metal_idle_v001.png`, `ui_macro_knob_fm_metal_hover_v001.png`, `ui_macro_knob_fm_metal_active_v001.png` | Primary macro |
| `ui.macro.primary.roller_dynamics` | `macro.roller_dynamics` | `ui_macro_knob_roller_dynamics_idle_v001.png`, `ui_macro_knob_roller_dynamics_hover_v001.png`, `ui_macro_knob_roller_dynamics_active_v001.png` | Primary macro |
| `ui.macro.primary.liquid_depth` | `macro.liquid_depth` | `ui_macro_knob_liquid_depth_idle_v001.png`, `ui_macro_knob_liquid_depth_hover_v001.png`, `ui_macro_knob_liquid_depth_active_v001.png` | Primary macro |

## Macro controls (advanced surface: 6)
| UI Control ID | Param ID | Asset File(s) | Notes |
|---|---|---|---|
| `ui.macro.advanced.sub_punch` | `macro.sub_punch` | `ui_macro_knob_sub_punch_idle_v001.png`, `ui_macro_knob_sub_punch_hover_v001.png`, `ui_macro_knob_sub_punch_active_v001.png` | Advanced macro |
| `ui.macro.advanced.fm_pressure` | `macro.fm_pressure` | `ui_macro_knob_fm_pressure_idle_v001.png`, `ui_macro_knob_fm_pressure_hover_v001.png`, `ui_macro_knob_fm_pressure_active_v001.png` | Advanced macro |
| `ui.macro.advanced.cutoff_motion` | `macro.cutoff_motion` | `ui_macro_knob_cutoff_motion_idle_v001.png`, `ui_macro_knob_cutoff_motion_hover_v001.png`, `ui_macro_knob_cutoff_motion_active_v001.png` | Advanced macro |
| `ui.macro.advanced.fold_bite` | `macro.fold_bite` | `ui_macro_knob_fold_bite_idle_v001.png`, `ui_macro_knob_fold_bite_hover_v001.png`, `ui_macro_knob_fold_bite_active_v001.png` | Advanced macro |
| `ui.macro.advanced.table_drift` | `macro.table_drift` | `ui_macro_knob_table_drift_idle_v001.png`, `ui_macro_knob_table_drift_hover_v001.png`, `ui_macro_knob_table_drift_active_v001.png` | Advanced macro |
| `ui.macro.advanced.smash_glue` | `macro.smash_glue` | `ui_macro_knob_smash_glue_idle_v001.png`, `ui_macro_knob_smash_glue_hover_v001.png`, `ui_macro_knob_smash_glue_active_v001.png` | Advanced macro |

## Style controls (canonical: Tech / Neuro / Dark)
| UI Control ID | Param ID | Asset File(s) | Notes |
|---|---|---|---|
| `ui.style.mode.tech` | `style.mode` | `ui_style_mode_tech_idle_v001.png`, `ui_style_mode_tech_selected_v001.png`, `ui_style_mode_tech_disabled_v001.png` | Canonical style mode |
| `ui.style.mode.neuro` | `style.mode` | `ui_style_mode_neuro_idle_v001.png`, `ui_style_mode_neuro_selected_v001.png`, `ui_style_mode_neuro_disabled_v001.png` | Canonical style mode |
| `ui.style.mode.dark` | `style.mode` | `ui_style_mode_dark_idle_v001.png`, `ui_style_mode_dark_selected_v001.png`, `ui_style_mode_dark_disabled_v001.png` | Canonical style mode |
| `ui.style.morph.track` | `macro.style_morph` | `ui_style_morph_track_main_base_v001.png` | Morph track base |
| `ui.style.morph.thumb` | `macro.style_morph` | `ui_style_morph_thumb_main_base_v001.png` | Morph thumb |
| `ui.style.morph.glow` | `macro.style_morph` | `ui_style_morph_glow_main_active_v001.png` | Active glow overlay |

## Visual feedback overlays
| UI Control ID | Param ID | Asset File(s) | Notes |
|---|---|---|---|
| `ui.visual.scope.grid` | `n/a` | `ui_visual_scope_grid_main_base_v001.png` | Scope grid layer |
| `ui.visual.scope.wave_overlay` | `n/a` | `ui_visual_scope_wave_overlay_base_v001.png` | Waveform overlay |
| `ui.visual.scope.spectrum_overlay` | `n/a` | `ui_visual_scope_spectrum_overlay_base_v001.png` | Spectrum overlay |
| `ui.visual.scope.frame_glow` | `n/a` | `ui_visual_scope_frame_glow_active_v001.png` | Active frame/glow layer |

## Support badges and status icons
| UI Control ID | Param ID | Asset File(s) | Notes |
|---|---|---|---|
| `ui.badge.macro_primary` | `n/a` | `ui_badge_macro_primary_base_v001.png` | Primary section label badge |
| `ui.badge.macro_advanced` | `n/a` | `ui_badge_macro_advanced_base_v001.png` | Advanced section label badge |
| `ui.icon.constraint_guard` | `n/a` | `ui_icon_constraint_guard_on_v001.png` | Domain/safety indicator |
| `ui.icon.mono_sub_lock` | `n/a` | `ui_icon_mono_sub_lock_on_v001.png` | Sub mono lock indicator |
| `ui.icon.oversample_indicator` | `n/a` | `ui_icon_oversample_indicator_on_v001.png` | Oversampling indicator |
| `ui.icon.warning_general` | `n/a` | `ui_icon_warning_general_on_v001.png` | Generic warning indicator |
