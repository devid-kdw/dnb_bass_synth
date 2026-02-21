# Frontend Phase Handoff: P1 (Domain Constraint Core)

**Phase ID**: P1  
**Status Transition**: `Planned` -> `Review`  

## 1. Changed Files
- `docs/qa/frontend_phase_handoffs/P1_handoff.md` (this file)

*(Note: As P1 is primarily a backend phase, the frontend role is support and contract alignment. No codebase source files were modified.)*

## 2. Test Commands & Results
- N/A (Frontend support phase only. No runtime UI code was implemented that requires tests. Knowledge base text data was extracted and analyzed.)

## 3. UI Contract Checklist (For Backend Review)
Based on the knowledge base (Research V2, Developer Doc, Supplementary Spec, Architecture), the Frontend requires the following domain schema constraints to be frozen in P1:

### Expected Macro IDs (10 Macros)
The domain must expose APVTS parameters for these macros. The frontend will map them 0.0 - 1.0.
1. `macro_neuro_formant` (Squelch) - Controls 2-3 notch filters & wavefold res.
2. `macro_fm_metal` (Foghorn) - Controls inharmonic FM depth (β).
3. `macro_roller_dynamics` (Wobble) - Controls 24dB filter subdivisions/resonance.
4. `macro_liquid_depth` (Warmth) - Controls 12dB LP, tube sat, cuts diodes.
5-10. `macro_5` through `macro_10` (To be defined by backend schema logic for sub volume, OTT depth, LFO rates, etc.)

### Style-Mode Control Behavior
- **Parameter ID**: `style_mode`
- **Expected Values**: Discrete/Stepped corresponding to the 3 styles (e.g., [0, 1, 2] for Tech, Neuro, Liquid).
- **Frontend Behavior**: Interpolation (50-100ms morph) will be handled by the **Backend** `StyleModeMorph` and `ConstraintEngine` as per the spec. The UI simply sends the discrete target value. UI will animate visual feedback if the backend exposes the morph state.

### Parameter Display Map (Normalized -> Display Units)
- **Macros**: 0.0 - 1.0 -> 0% - 100%
- **Style Mode**: 0.0 - 1.0 (internal discrete) -> Strings: "Tech", "Neuro", "Liquid"
- **LFO Sync Rates**: 0.0 - 1.0 -> Strings: "1/32", "1/16", "1/8", "1/4", etc.

### UI Binding Points Dependent on P1 Freeze
Frontend cannot proceed with P5 wiring without strict IDs for:
- `ConstraintEngine` macro parameter mappings
- `StyleMode` selection parameter
- LFO1 and LFO2 rate and depth bounds
- `ModMatrix` target parameters

## 4. Known Constraints / Open Questions
- **Open Question**: Will the `ConstraintEngine` expose a read-only parameter for the *current* interpolated morph state (e.g. `style_morph_progress`) so the UI can draw smooth transition animations during the 50-100ms style switch?
- **Constraint Validated**: UI will not implement runtime binding that bypasses the Domain limits. All knobs will be strictly bound to the Domain APVTS parameters.

## 5. ADR Proposal
- No architectural changes proposed. The frontend fully aligns with the Domain boundary constraint and the macro-first UX methodology.
