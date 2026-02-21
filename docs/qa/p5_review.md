# P5 Review (App Wiring + Macro UI)

Date: 2026-02-21  
Owner: Orchestrator  
Phase status under review: `P5 -> Review` (not accepted as `Done`)

## 1. Scope Reviewed
- `src/app/*`
- `src/ui/*`
- `src/domain/*` (P5 wiring impact only)
- `src/engine/*` (style morph and parameter flow impact)
- `docs/agent_briefs/P5_handoff.md`
- `docs/qa/frontend_phase_handoffs/P5_handoff.md`

## 2. Findings

### `F-P5-001` - Style mode contract gap (High)
Problem:
- Canonical contract expects `style.mode` (schema freeze), but active app wiring does not expose or consume it end-to-end.
- `RawInputParams.activeStyle` remains effectively defaulted unless explicitly wired from host/UI path.

Impact:
- Style-dependent constraints can stay pinned to default behavior instead of explicit Tech/Neuro/Dark selection.
- P5 contract stability is incomplete for frontend binding.

Required closure:
- Add stable APVTS-facing style mode contract path (`style.mode`) and map it deterministically to `RawInputParams.activeStyle`.

### `F-P5-002` - Style morph not proven on audio path (High)
Problem:
- `macro.style_morph` state surface exists, but review evidence does not prove deterministic audio-path impact in current render flow.

Impact:
- Feature appears wired in UI/state but may behave as non-audible control under common scenarios.

Required closure:
- Ensure style morph affects rendered output in deterministic, test-covered path without violating domain gate or sub safety.

### `F-P5-003` - APVTS contract completeness gap (High)
Problem:
- Several exposed P5 parameters are not fully proven as end-to-end effective through domain/engine mapping.
- Exposed parameters must not remain dead/no-op from host automation perspective.

Impact:
- Host/UI automation contract drift and false affordances.

Required closure:
- For each exposed APVTS parameter in P5 contract: either
  1. wire through domain-sanctioned path to runtime behavior, or
  2. remove/defer from active layout with explicit documentation and contract update.

### `F-P5-004` - Handoff protocol mismatch (Medium)
Problem:
- Backend P5 handoff artifact is in `docs/agent_briefs/P5_handoff.md` instead of QA handoff path convention.

Impact:
- Phase audit trail inconsistency.

Required closure:
- Submit remediation handoff in `docs/qa/backend_phase_handoffs/P5_handoff_fix.md` with closure map and validation evidence.

## 3. Gate Decision
P5 cannot move to `Done` until `F-P5-001`, `F-P5-002`, `F-P5-003`, and `F-P5-004` are closed and re-verified.
