# P1 Schema Freeze (Backend + Frontend Contract)

Date: 2026-02-21  
Owner: Orchestrator  
Scope: P1 Domain Constraint Core contract required before P5 UI wiring

## 1. Source of Truth
This freeze aligns with:
1. `knowledge/DNB bass synth document for developer.pdf`
2. `knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx`
3. `knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx`
4. `docs/project_rules.md`
5. `docs/master_implementation_plan.md`

## 2. Canonical Contract Decisions

### 2.1 Parameter ID Naming
Canonical ID convention for domain/APVTS-facing parameters:
- lower snake_case segments
- dot-separated namespace
- no spaces

Examples:
- `macro.neuro_formant`
- `macro.fm_metal`
- `macro.roller_dynamics`
- `macro.liquid_depth`
- `style.mode`
- `env.amp.att`
- `env.amp.rel`

### 2.2 MVP Style Set (Frozen)
For MVP contract, active style set is frozen to:
1. `Tech`
2. `Neuro`
3. `Dark`

Deferred (not active in MVP domain contract unless ADR-approved):
- `Liquid`
- `JumpUp`
- `Darkstep` aliases beyond `Dark`

### 2.3 Macro Set by Phase
P1 implemented macro contract is frozen to 4 canonical macros:
1. `macro.neuro_formant`
2. `macro.fm_metal`
3. `macro.roller_dynamics`
4. `macro.liquid_depth`

P5 target remains 10 macro controls (MVP UX objective), but additional 6 are not required to be implemented in P1.

### 2.4 FM Ratio Curated Set (P1)
To align with current MVP range strategy (1.0 to 8.23), freeze P1 curated set to:
- `1.00`
- `1.41`
- `2.33`
- `3.15`
- `7.10`
- `8.23`

Disallowed in P1 curated array:
- generic math constants with no documented curation purpose (`2.718`, `3.141`)

Note:
- ratios below 1.0 (e.g. `7:10`, `8:23`) can be introduced only with explicit parameter-range decision and ADR.

### 2.5 Raw Input Unit Semantics
`RawInputParams` semantics are frozen as:
- macro/style controls: normalized UI space (`0.0` to `1.0` or stepped enum)
- attack/release: resolved UI units in milliseconds before domain clamp

This must be explicitly documented in code comments.

### 2.6 Test Dependency Policy for P1
If `FetchContent` is retained for Catch2 in P1, backend must add a short ADR note explaining temporary policy and migration plan to the preferred dependency strategy.

## 3. Required Backend P1 Corrections
1. Align style enum/behavior to MVP frozen set (Tech/Neuro/Dark).
2. Align `allowedFMRatios` to frozen P1 curated set.
3. Rename `macro.roller_dyn` contract usage to `macro.roller_dynamics`.
4. Clarify raw input unit semantics in `ConstraintEngine` contracts.
5. Either wire `macroRollerDyn` in `ConstraintEngine` or explicitly defer with TODO + handoff note.
6. Add ADR note if continuing `FetchContent` strategy.

## 4. Required Frontend P1 Corrections
1. Update handoff contract IDs to canonical dot-format IDs.
2. Update style expectations to MVP frozen set (Tech/Neuro/Dark).
3. Update macro expectation: 4 required in P1, 10 target in P5.
4. Keep frontend runtime implementation blocked until backend resubmits corrected P1 contract.

## 5. Exit Criteria (P1 Close)
P1 can be moved to `Done` only when:
1. backend code + tests reflect this freeze,
2. frontend handoff reflects this freeze,
3. orchestrator review confirms no backend/frontend schema mismatch.
