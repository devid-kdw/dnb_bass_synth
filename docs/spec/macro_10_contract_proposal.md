# Macro-10 Contract Proposal (MVP+)

Date: 2026-02-22  
Owner: Orchestrator  
Status: Proposal (implementation-target)

## 1. Source of Truth
This proposal is derived from:
1. `knowledge/DNB Bass Synth VST Plugin Research.pdf`
2. `knowledge/DNB bass synth document for developer.pdf`
3. `knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx`
4. `knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx`
5. `docs/project_rules.md`

## 2. Design Intent
Macro controls must remain:
1. Restriction-first (DnB-safe)
2. Domain-gated (`app/ui -> domain -> engine -> dsp`)
3. Musical-intent oriented (not raw DSP leakage)
4. Compatible with current roadmap:
   - Performance UI: 4 primary macros
   - Advanced UI: remaining macros with explicit guardrails

## 3. Locked Existing Macros (Do Not Change)
The following 4 remain canonical and unchanged:
1. `macro.neuro_formant`
2. `macro.fm_metal`
3. `macro.roller_dynamics`
4. `macro.liquid_depth`

## 4. Proposed Additional 6 Macros
All IDs follow canonical dot-namespace style and normalized range `0.0..1.0`.

### 4.1 `macro.sub_punch` (Sub Punch)
Primary intent:
- Control low-end transient weight and dynamic response without violating sub safety.

Proposed mapping:
1. `velocity -> sub level` depth
2. subtle sub-envelope transient emphasis
3. optional mild kick-space duck amount (bounded)

Why:
- Knowledge modulation matrix explicitly highlights velocity-driven sub dynamics and performance control.

### 4.2 `macro.fm_pressure` (FM Pressure)
Primary intent:
- Control FM intensity (depth/pressure), distinct from ratio-selection macro.

Proposed mapping:
1. FM depth (`beta`) amount
2. velocity-to-FM depth sensitivity
3. style-dependent cap (Tech < Neuro < Dark)

Why:
- Existing `macro.fm_metal` handles ratio flavor; this macro handles aggression/intensity.

### 4.3 `macro.cutoff_motion` (Cutoff Motion)
Primary intent:
- Master depth for animated filter movement (LFO/Env to cutoff).

Proposed mapping:
1. LFO1 -> character cutoff depth
2. envelope -> character cutoff depth
3. resonance motion moderation by style

Why:
- Knowledge matrix and roller behavior rely on controlled cutoff motion as a primary musical driver.

### 4.4 `macro.fold_bite` (Fold Bite)
Primary intent:
- Control wavefold articulation/bite while staying aliasing-safe.

Proposed mapping:
1. wavefolder threshold
2. envelope -> fold depth
3. optional high-band bite compensation with style caps

Why:
- Wavefolding is a core character mechanism in neuro/dark material.

### 4.5 `macro.table_drift` (Table Drift)
Primary intent:
- Organic spectral drift via wavetable motion.

Proposed mapping:
1. LFO2 -> wavetable position depth
2. drift randomness/slew amount
3. style-dependent drift ceiling

Why:
- Supplement matrix explicitly uses LFO2/wavetable-position drift for organic neuro texture.

### 4.6 `macro.smash_glue` (Smash Glue)
Primary intent:
- Control OTT/smash intensity as optional macro-compression character.

Proposed mapping:
1. OTT depth/mix
2. aftertouch -> OTT depth sensitivity
3. post-OTT safety compensation

Why:
- Knowledge documents isolate OTT as optional character layer and performance expression path.

## 5. Behavior Rules per Style (High-Level)
1. `Tech`: tighter caps, cleaner mid/high behavior
2. `Neuro`: expanded motion and formant/fold intensity
3. `Dark`: highest aggression ceilings within safety bounds

All style behavior must remain deterministic and domain-enforced.

## 6. Implementation Constraints
1. No dead APVTS params.
2. Every new macro must have:
   - domain mapping
   - engine/dsp runtime effect
   - at least one evidence test
3. No RT-unsafe operations in audio thread.
4. Existing 4 macros must preserve backward compatibility.

## 7. Verification Matrix (Required)
For each new macro:
1. Mapping test (`domain`)
2. Runtime effect test (`engine`/render delta)
3. Style-bound clamp test (`Tech/Neuro/Dark`)

## 8. Migration and Backward Compatibility
1. Preserve existing parameter IDs.
2. New macro IDs are additive (non-breaking).
3. State migration must load old projects without null behavior or crashes.

