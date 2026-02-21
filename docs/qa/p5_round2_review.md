# P5 Round-2 Review (Gate Remediation)

Date: 2026-02-21  
Owner: Orchestrator  
Phase status: `P5 -> Review` (Round-2 required before `Done`)

## 1. Scope Reviewed
- `src/app/*`
- `src/domain/*`
- `src/engine/*`
- `src/ui/*`
- `docs/qa/backend_phase_handoffs/P5_handoff_fix.md`
- `docs/qa/frontend_phase_handoffs/P5_handoff_fix.md`

## 2. Findings

### `F-P5R2-001` - Active APVTS contract still has no-op/dead paths (High)
Problem:
- Multiple exposed APVTS parameters are declared/cached but not proven as effective runtime controls.
- Current P5 baseline must not ship with host-facing false affordances.

Required closure:
- For every exposed APVTS parameter choose one:
  1) `wired`: deterministic runtime effect through domain-approved path, or
  2) `deferred`: remove from active APVTS for P5 and document defer reason.
- Mandatory macro contract for P5 must remain explicit and non-dead:
  - `macro.neuro_formant`
  - `macro.fm_metal`
  - `macro.roller_dynamics`
  - `macro.liquid_depth`
  - `macro.style_morph`

### `F-P5R2-002` - Missing evidence tests for P5 remediation claims (High)
Problem:
- Existing tests do not prove APVTS/domain style-mode mapping correctness.
- Existing tests do not prove style morph audible/runtime delta beyond state progression.

Required closure:
- Add tests that prove:
  1) style mode mapping is deterministic and bounded (`Tech/Neuro/Dark`),
  2) style morph changes rendered output under controlled conditions,
  3) restored/kept macros are not dead (especially `macro.roller_dynamics`).

### `F-P5R2-003` - Contract naming and macro-set drift (Medium)
Problem:
- UI/backend display naming currently uses `Neurofunk` while canonical MVP set is `Tech/Neuro/Dark`.
- Frontend macro panel drifted from canonical 4-macro MVP set.

Required closure:
- Canonical MVP style naming must be `Tech`, `Neuro`, `Dark`.
- Frontend macro surface must expose canonical 4 macro controls in P5.

## 3. Gate Decision
P5 cannot move to `Done` until `F-P5R2-001`, `F-P5R2-002`, and `F-P5R2-003` are closed and re-verified.
