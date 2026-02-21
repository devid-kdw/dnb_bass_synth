# Frontend Phase Handoff: P3 (Osc/Filter/Nonlinear DSP)

**Phase ID**: P3  
**Status Transition**: `Planned` -> `Review`  

## 1. Changed Files
- `src/ui/components/VisualFeedbackPlaceholder.h` (NEW)
- `src/ui/layout/MainLayoutScaffold.h`
- `docs/qa/frontend_p3_ux_feedback.md` (NEW)
- `docs/qa/frontend_phase_handoffs/P3_handoff.md` (this file)

## 2. Test Commands & Results
- N/A (Frontend scaffold + UX feedback role only. No runtime components wired that require tests.)

## 3. UI Scaffold Readiness & Feedback (For Backend Review)
The frontend has completed its P3 responsibilities:
1. **Layout Iteration**: Integrated a dedicated `VisualFeedbackPlaceholder` into the layout, positioned above the macro knobs. It's built to mock the sub-wave/FFT oscilloscope defined in the UX requirements.
2. **UX Feedback Note**: Compiled an extensive feedback map for the Backend (`docs/qa/frontend_p3_ux_feedback.md`), detailing exactly what structural elements the UI requires to animate the visualizers:
   - Data streams (FIFOs/queues) for raw sub sine and combined character signal FFT.
   - Live/computed parameters representing macro modulations (e.g., active cutoff for notch filters).
   - Ergonomics note regarding LFO string mappings and skewed/exponential knob maps.

## 4. Known Constraints / Open Questions
- **Constraint Validated**: UI retains restriction-first design; no direct DSP overrides are requested. All visual functionality depends strictly on data passed back from the canonical DSP/domain state.
- **Open Requirement**: Backend must agree to either expose real-time internal state parameters (`read_only` APVTS) or provide an alternate thread-safe method for UI visualization of style-morphing and formant transitions.

## 5. ADR Proposal
- No architectural changes proposed.
