# P7 Fix Review (Gate Before P8)

Date: 2026-02-22  
Owner: Orchestrator

## 1. Scope
This document defines required remediation items after P7 review.
All items must be closed before phase transition `P7 -> Done` and before starting P8.

## 2. Findings to Close

### F-P7R-001 (Frontend) - style.mode binding semantics risk
Severity: High

Problem:
- UI currently binds 3 style toggle buttons directly to one `style.mode` APVTS choice parameter via `ButtonAttachment` pattern.
- This is bool-semantic wiring against a 3-state enum contract (`Tech=0`, `Neuro=1`, `Dark=2`).

Required closure:
1. Implement deterministic 3-state mapping for `style.mode`.
2. Preserve canonical IDs and bidirectional sync UI <-> APVTS.
3. Keep `macro.style_morph` mapping unchanged and canonical.

### F-P7R-002 (Frontend) - handoff evidence drift
Severity: Medium

Problem:
- P7 frontend handoff contains placeholder/non-manifest asset IDs and stale test count statements.

Required closure:
1. Update handoff with real asset IDs used in runtime UI.
2. Report exact test commands and exact pass count.
3. Include full mapping table `ui_control -> param_id -> asset_file`.

### F-P7R-003 (Backend) - aliasing QA evidence gap
Severity: Medium

Problem:
- Existing aliasing render test claims aliasing behavior but currently validates only NaN/Inf and peak amplitude.

Required closure:
1. Replace/add test assertions with measurable aliasing-oriented metric (e.g. spectral band energy / foldback metric).
2. Keep deterministic thresholds and clear test rationale.
3. Ensure comments and test name match actual verification logic.

### F-P7R-004 (Backend) - backend handoff evidence drift
Severity: Medium

Problem:
- Handoff summaries are not strict enough about exact command outputs/counts/measurement context.

Required closure:
1. Re-run bench and test commands with exact reproducible CLI.
2. Record exact results and measurement context (Debug/Release).
3. Publish corrected backend handoff with closure map for all backend findings.

## 3. Global Constraints
1. No work outside `/Users/grzzi/Desktop/dnb_bass_synth`.
2. No bypass of `domain/ConstraintEngine`.
3. No new unapproved dependencies.
4. No scope creep into P8 feature work.

## 4. Exit Criteria
P7 can transition to `Done` only when:
1. `F-P7R-001` and `F-P7R-002` are closed by frontend handoff fix.
2. `F-P7R-003` and `F-P7R-004` are closed by backend handoff fix.
3. Build + ctest pass after fixes.
4. Orchestrator review confirms no residual conflicts with knowledge documents.

## 5. Closure Status
Status: **Closed (accepted)**  
Accepted on: 2026-02-22

Acceptance evidence:
1. `docs/qa/frontend_phase_handoffs/P7_design_integration_handoff_fix.md`
2. `docs/qa/backend_phase_handoffs/P7_qa_handoff_fix.md`
3. `docs/qa/p7_final_gate_review.md`
