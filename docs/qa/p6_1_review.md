# P6.1 Review (Macro-10 + P7 Gate)

Date: 2026-02-22  
Reviewer: Orchestrator  
Decision: **NO-GO for P7 (P6.1 remains `Review`)**

## 1. Scope Reviewed
- Backend and frontend P6.1 implementation outputs
- Active code changes since commit `21e1369`
- P6/P6.1 handoff packets
- Plan and gate documents:
  - `docs/implementation_plan.md`
  - `docs/master_implementation_plan.md`
  - `docs/qa/p6_to_p7_gate_deviations.md`
  - `docs/spec/macro_10_contract_proposal.md`
- Knowledge extracts:
  - `docs/qa/knowledge_extract/knowledge_pdf_extract_fresh.txt`
  - `docs/qa/knowledge_extract/supplement_fresh.txt`
  - `docs/qa/knowledge_extract/techstack_fresh.txt`

## 2. Verification Executed
1. `tools/scripts/init_submodules.sh` -> PASS
2. `cmake --build build --parallel` -> PASS
3. `cd build && ctest --output-on-failure` -> PASS (`40/40`)
4. `cd build && ctest --output-on-failure -R Preset` -> PASS (`5/5`)
5. `cd build && ctest --output-on-failure -R preset` -> **No tests found** (evidence mismatch)

## 3. What Is Good
1. Macro-10 code path exists end-to-end (domain -> app/APVTS -> engine -> UI).
2. 6 additional macro IDs are present and bound:
   - `macro.sub_punch`
   - `macro.fm_pressure`
   - `macro.cutoff_motion`
   - `macro.fold_bite`
   - `macro.table_drift`
   - `macro.smash_glue`
3. Preset/state JSON wrapper + legacy XML fallback is implemented.
4. Regression suite is green locally (`40/40`).

## 4. Findings (Blockers)

### F-P6.1-001 (High) - FM Pressure style behavior does not match accepted P6.1 macro contract
Evidence:
- Contract expects style-dependent progression (`Tech < Neuro < Dark`) in `docs/spec/macro_10_contract_proposal.md`.
- Runtime currently mutes FM pressure unless Dark path is active:
  - `src/domain/ConstraintEngine.cpp` (FM pressure gate)
  - `src/domain/StyleMode.h` (`Neuro` has `enableFMMetal=false`)
- Unit test currently enforces Neuro=0 behavior:
  - `tests/unit/test_macro_constraints.cpp`
Impact:
- Contract drift remains for one of the 6 new macros.

### F-P6.1-002 (Medium) - Domain output safety clamp drift on `filterCutoff`
Evidence:
- `out.filterCutoff` gets post-adjusted (`+ cutoff_motion`) near return path without a final domain clamp in `src/domain/ConstraintEngine.cpp`.
Impact:
- Domain layer no longer guarantees fully sanitized cutoff output, relying on downstream clamp in `engine`.

### F-P6.1-003 (Medium) - Frontend UX contract not split into primary 4 + advanced 6 surface
Evidence:
- Proposal states primary 4 + advanced access for remaining macros (`docs/spec/macro_10_contract_proposal.md`).
- UI currently exposes all 10 equally in one panel/grid:
  - `src/ui/components/MacroPanel.h`
  - `src/ui/layout/MainLayout.h`
Impact:
- Partial mismatch with macro-first UX hierarchy from P6.1 intent.

### F-P6.1-004 (High) - Gate evidence integrity still inconsistent (`G-P6P7-002` not closed)
Evidence:
- `docs/qa/backend_phase_handoffs/P6_handoff.md` still uses invalid check command (`ctest -R preset`) that returns no tests.
- Same handoff states XML wrapper naming that does not match current schema constants in `src/preset/PresetSchema.h`.
Impact:
- Backend evidence packet is not fully reliable for gate closure.

### F-P6.1-005 (High) - Orchestration gate docs are still open (`G-P6P7-001`, `G-P6P7-006`)
Evidence:
- `docs/master_implementation_plan.md` phase board still shows `P5`/`P6` as `Planned`.
- Final consolidated gate note is missing (`docs/qa/p6_final_gate_review.md` not present).
Impact:
- Formal gate process is incomplete; P7 cannot be declared open.

## 5. Non-Blocking Risk

### R-P6.1-001 (Medium) - `plugin_version` still hardcoded in source
Evidence:
- `src/preset/PresetSchema.h` uses literal `"0.1.0"` instead of deriving from build/version source.
Impact:
- Future drift risk if project version changes and schema constant is not updated.

## 6. Gate Status vs Deviation Backlog
- `G-P6P7-004`: **Partially closed** (major implementation done, contract details still drifted in FM/style + UX split)
- `G-P6P7-003`: **Partially closed** (value now aligned to current version, but single-source rule still weak)
- `G-P6P7-002`: **Open** (evidence command mismatch remains in active handoff)
- `G-P6P7-001`: **Open**
- `G-P6P7-005`: **Partially closed** (ADR marked superseded, but remains textually contradictory)
- `G-P6P7-006`: **Open** (final unified gate report still missing)

## 7. Final Decision
P6.1 is **not fully closed** yet. Project is **not ready for P7 delegation** until findings `F-P6.1-001`..`F-P6.1-005` are remediated and the gate backlog is explicitly closed in a final acceptance note.
