# P6 -> P7 Gate Deviations and Required Fixes

Date: 2026-02-22  
Owner: Orchestrator  
Purpose: authoritative backlog that must be closed before moving to P7

## 1. Scope
This list consolidates known deviations after P6 remediation and defines required closure actions.

## 2. Deviation Backlog

### G-P6P7-001 - Master plan status drift
Current issue:
- `docs/master_implementation_plan.md` phase board and update log are not aligned with actual P5/P6 review state.

Required fix:
1. Update phase board statuses.
2. Add P5/P6 entries in phase update log with evidence.
3. Update next delegation queue away from stale P5-start wording.

Owner: Orchestrator  
Severity: High

### G-P6P7-002 - Backend P6 handoff evidence mismatch
Current issue:
- `docs/qa/backend_phase_handoffs/P6_handoff.md` still contains outdated wording and a verification command that does not discover tests (`ctest -R preset` case mismatch).

Required fix:
1. Correct wording to match current JSON + legacy XML fallback behavior.
2. Use valid verification command (`ctest -R Preset` or equivalent evidence).

Owner: Backend/DSP  
Severity: Medium

### G-P6P7-003 - Plugin version tag mismatch risk
Current issue:
- Serialized state uses hardcoded `"plugin_version": "1.0.0"` while project version is currently `0.1.0`.

Required fix:
1. Derive plugin version from build/version source of truth (single source).
2. Add test asserting payload/version consistency.

Owner: Backend/DSP  
Severity: High

### G-P6P7-004 - Macro contract drift (10 target vs 4 active)
Current issue:
- Knowledge indicates 10 macro MVP target; active implementation currently uses 4 primary macros (+ style morph).

Required fix:
1. Adopt `docs/spec/macro_10_contract_proposal.md` as implementation target.
2. Implement additional 6 macros with domain/runtime/test coverage.
3. Ensure no dead host-visible parameters.

Owner: Backend/DSP + Frontend/UI  
Severity: High

### G-P6P7-005 - Deferred ADR conflicts with Macro-10 implementation target
Current issue:
- `ADR-005-defer-remaining-6-mvp-macros.md` encodes defer path. If project proceeds with Macro-10 implementation, ADR status must be updated.

Required fix:
1. Supersede or amend ADR-005 with explicit transition decision.
2. Keep architecture rationale and migration consequences documented.

Owner: Orchestrator + Backend/DSP  
Severity: Medium

### G-P6P7-006 - P6 gate evidence fragmentation
Current issue:
- P6 evidence is spread across multiple handoffs and audits, making gate acceptance ambiguous.

Required fix:
1. Produce one final acceptance review note after fixes:
   - `docs/qa/p6_final_gate_review.md`
2. Include closure map for all open G-P6P7 findings.

Owner: Orchestrator  
Severity: Medium

## 3. Exit Criteria for P7 Start
P7 can start only when:
1. `G-P6P7-001`..`G-P6P7-006` are closed.
2. Build and full tests pass.
3. Updated master plan reflects real status and next queue.
4. Macro-10 contract implementation is either complete or explicitly split into approved incremental gate with no false P7-ready claim.

## 4. Closure Update (2026-02-22)
All items are now closed with evidence:

1. `G-P6P7-001` -> closed by master plan status/log update:
   - `docs/master_implementation_plan.md`
2. `G-P6P7-002` -> closed by corrected handoff evidence command:
   - `docs/qa/backend_phase_handoffs/P6_handoff.md`
3. `G-P6P7-003` -> closed by build-version single source wiring:
   - `src/Config.h.in`
   - `src/preset/PresetSchema.h`
   - `tests/unit/test_preset_manager.cpp`
4. `G-P6P7-004` -> closed by backend+frontend Macro-10 implementation:
   - `src/domain/*`, `src/app/*`, `src/engine/*`, `src/ui/*`, tests
5. `G-P6P7-005` -> closed by ADR supersede + active contract docs:
   - `docs/adr/ADR-005-defer-remaining-6-mvp-macros.md`
   - `docs/spec/mvp_macro_contract.md`
6. `G-P6P7-006` -> closed by consolidated gate review:
   - `docs/qa/p6_final_gate_review.md`
