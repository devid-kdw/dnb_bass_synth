# MVP Macro Contract

Date: 2026-02-22  
Scope: Canonical MVP Macro Definitions  
Status: Active (post P6.1 remediation)

## 1. Source of Truth
This contract is derived from explicit mentions in the following knowledge documents:
1. `knowledge/DNB Bass Synth VST Plugin Research.pdf`
2. `knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx`
3. `knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx`

## 2. P1 Frozen Macro Set (Historical Baseline)
The following 4 macros were explicitly defined and implemented as part of the P1 constraint freeze:

| Name | ID | Description |
|---|---|---|
| **Neuro-Formant (Squelch)** | `macro.neuro_formant` | Automates multiple asymmetrical notch filters and wavefold resolution. |
| **FM Metal / Foghorn** | `macro.fm_metal` | Modulates through curated inharmonic FM ratios (e.g. 1.41, 7:10). |
| **Roller Dynamics (Wobble)** | `macro.roller_dynamics` | Controls subdivisions and resonance of the main 24dB filter. |
| **Liquid Depth (Warmth)** | `macro.liquid_depth` | Activates 12dB (2-pole) low-pass filter and tube saturation. |

## 3. Current Active MVP Macro-10 Set
Following P6.1 closure, the active MVP contract is a **10 macro** set:

1. `macro.neuro_formant`
2. `macro.fm_metal`
3. `macro.roller_dynamics`
4. `macro.liquid_depth`
5. `macro.sub_punch`
6. `macro.fm_pressure`
7. `macro.cutoff_motion`
8. `macro.fold_bite`
9. `macro.table_drift`
10. `macro.smash_glue`

Implementation reference for the additional 6 macros:
- `docs/spec/macro_10_contract_proposal.md`

Historical defer decision is retained only as context in:
- `docs/adr/ADR-005-defer-remaining-6-mvp-macros.md` (`Status: Superseded`)
