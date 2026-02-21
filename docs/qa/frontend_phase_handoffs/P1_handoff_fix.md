# Frontend Phase Handoff: P1 (Domain Constraint Core) - FIXED

**Phase ID**: P1  
**Status Transition**: `Planned` -> `Review`  

## 1. Changed Files
- `docs/qa/frontend_phase_handoffs/P1_handoff_fix.md` (this file)

*(Note: As P1 is primarily a backend phase, the frontend role is support and contract alignment. No codebase source files were modified.)*

## 2. Test Commands & Results
- N/A (Frontend support phase only. No runtime UI code was implemented that requires tests.)

## 3. UI Contract Checklist (Aligned with P1 Schema Freeze)
The frontend requires the following domain schema constraints to be frozen in P1 before P5 UI wiring can begin. This contract has been explicitly aligned with `docs/spec/p1_schema_freeze.md`.

### Expected Macro IDs
The domain must expose APVTS parameters for these 4 canonical macros. The frontend will map them 0.0 - 1.0. The target for P5 remains 10 macros, but these 4 are the strict requirement for P1.
1. `macro.neuro_formant` (Squelch) - Controls 2-3 notch filters & wavefold res.
2. `macro.fm_metal` (Foghorn) - Controls inharmonic FM depth (β).
3. `macro.roller_dynamics` (Wobble) - Controls 24dB filter subdivisions/resonance.
4. `macro.liquid_depth` (Warmth) - Controls 12dB LP, tube sat, cuts diodes.

### Style-Mode Control Behavior
- **Parameter ID**: `style.mode`
- **Expected Values**: Discrete/Stepped corresponding to the frozen MVP active style set: `Tech`, `Neuro`, and `Dark`.
- **Frontend Behavior**: Interpolation (50-100ms morph) will be handled by the **Backend** `StyleModeMorph` and `ConstraintEngine` as per the spec. The UI simply sends the discrete target value. UI will animate visual feedback if the backend exposes the morph state.

### Parameter Display Map (Normalized -> Display Units)
- **Macros**: 0.0 - 1.0 -> 0% - 100%
- **Style Mode**: `style.mode` -> Strings: "Tech", "Neuro", "Dark"
- **LFO Sync Rates**: 0.0 - 1.0 -> Strings: "1/32", "1/16", "1/8", "1/4", etc.

### UI Binding Points Dependent on P1 Freeze
Frontend cannot proceed with P5 wiring without strict IDs for:
- 4 core `ConstraintEngine` macro parameter mappings (listed above)
- `style.mode` selection parameter
- Additional expected base parameters like `env.amp.att` and `env.amp.rel`

## 4. Known Constraints / Open Questions
- **Open Question**: Will the `ConstraintEngine` expose a read-only parameter for the *current* interpolated morph state (e.g. `style.morph_progress`) so the UI can draw smooth transition animations during the 50-100ms style switch?
- **Constraint Validated**: UI will not implement runtime binding that bypasses the Domain limits. All knobs will be strictly bound to the APVTS parameters as defined in the schema freeze. Frontend runtime implementation is blocked until the backend resubmits the corrected P1 codebase.

## 5. Changes Made for Schema Freeze Alignment
- Updated macro IDs to the canonical dot-format (e.g., `macro_neuro_formant` -> `macro.neuro_formant`).
- Updated the style mode expectation to strictly match the MVP frozen set: `Tech`, `Neuro`, `Dark`.
- Clarified that exactly 4 macros are expected for the P1 freeze, while the remaining 6 are deferred to P5 target scope.

## 6. ADR Proposal
- No architectural changes proposed. The frontend fully aligns with the Domain boundary constraint and the macro-first UX methodology as corrected by the orchestration review.
