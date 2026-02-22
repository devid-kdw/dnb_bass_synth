# DnB Bass Synth Master Implementation Plan

Last updated: 2026-02-22  
Plan owner: Orchestrator agent  
Update cadence: mandatory update after each completed phase handoff

## 1. Source of Truth
This master plan is governed by:
1. `knowledge/DNB Bass Synth VST Plugin Research.pdf`
2. `knowledge/DNB bass synth document for developer.pdf`
3. `knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx`
4. `knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx`
5. `docs/project_rules.md`

If conflict exists, no implementation proceeds before resolution and ADR note.

## 2. Status Legend
- `Planned`: phase defined, not started
- `In Progress`: work delegated and actively executed
- `Blocked`: waiting for dependency or conflict resolution
- `Review`: submitted by agent, waiting orchestration validation
- `Done`: acceptance criteria passed and handoff accepted

## 3. Master Phase Board
| Phase | Name | Status | Primary Owner | Depends On | Main Outputs |
|---|---|---|---|---|---|
| P0 | Foundation Setup | Done | Orchestrator | None | repo skeleton, rules, plans, briefs |
| P1 | Domain Constraint Core | Done | Backend/DSP | P0 | `src/domain/*` constraints, tests |
| P2 | DSP Core Primitives | Done | Backend/DSP | P1 | `src/dsp/core/*`, `src/dsp/safety/*` |
| P3 | Osc/Filter/Nonlinear DSP | Done | Backend/DSP | P2 | `src/dsp/osc/*`, `src/dsp/filters/*`, `src/dsp/dist/*` |
| P4 | Voice/Engine Orchestration | Done | Backend/DSP | P3 | `src/engine/*` deterministic voice path |
| P5 | App Wiring + Macro UI | Done | Frontend/UI + Backend | P1, P4 | `src/app/*`, `src/ui/*` bound to domain |
| P6 | Preset/State/Migration | Done | Backend/DSP | P5 | `src/preset/*`, state migration tests |
| P6.1 | Macro-10 Expansion + P7 Gate Closure | Done | Backend/DSP + Frontend/UI + Orchestrator | P6 | 6 new macros + gate backlog closure |
| P7 | QA + Render + Bench + UI Skin Integration | Done | Backend/DSP + Frontend/UI + UI Graphic Designer + Orchestrator | P6.1 | `tests/*`, `bench/*`, QA reports, stylized UI asset pack |
| P8 | CI/CD Hardening | Planned | Orchestrator | P7 | `.github/workflows/*`, CI gates |

## 4. Global Gate Conditions
No phase can move to `Done` unless all conditions pass:
1. `domain/ConstraintEngine` boundary respected (no bypass)
2. RT-safe rules respected for audio thread code
3. Required phase tests pass
4. Changed files and rationale documented in phase update log
5. ADR added for architecture-impacting decisions

## 5. Phase Details

## P1 - Domain Constraint Core
Goal: establish single authoritative mapping from UI/host params to DnB-safe DSP params.

Agent tasks:
1. Implement `ConstraintEngine`, style mode constraints, macro maps, parameter schema.
2. Encode hard constraints from developer spec (phase lock, release limits, FM ratio constraints, xover boundaries).
3. Add domain tests for clamp behavior, style-dependent mappings, macro-to-parameter consistency.

Expected outputs:
1. `src/domain/ConstraintEngine.*`
2. `src/domain/DnBLimits.*`
3. `src/domain/MacroMap.*`
4. `src/domain/StyleMode.*`
5. `tests/unit/test_parameter_ranges.cpp`
6. `tests/unit/test_macro_constraints.cpp`
7. `tests/unit/test_style_modes.cpp`

Acceptance checks:
1. All runtime control paths can be traced through domain layer.
2. No direct DSP parameter entry bypassing domain.
3. Unit tests pass.

## P2 - DSP Core Primitives
Goal: build RT-safe DSP infrastructure used by all later modules.

Agent tasks:
1. Implement anti-click ramp, smoother, denormal guard, NaN/Inf safety checks, DC blocker.
2. Implement oversampling interface abstraction for per-module use.
3. Validate no forbidden RT operations in hot paths.

Expected outputs:
1. `src/dsp/core/Smoother.*`
2. `src/dsp/core/DCBlocker.*`
3. `src/dsp/core/Oversampler.*`
4. `src/dsp/core/DenormalFlush.*`
5. `src/dsp/core/SanityCheck.*`
6. `src/dsp/safety/AntiClickRamp.*`

Acceptance checks:
1. DSP primitives compile and are unit-tested.
2. RT-safety checklist signed in phase update.

## P3 - Osc/Filter/Nonlinear DSP
Goal: implement core sound generation and character processing under DnB constraints.

Agent tasks:
1. Implement sub oscillator with deterministic phase behavior.
2. Implement character oscillators (wavetable/FM) and constrained nonlinear stages.
3. Implement filters and crossover path aligned with sub protection.
4. Apply per-module oversampling only to nonlinear stages requiring it.

Expected outputs:
1. `src/dsp/osc/*`
2. `src/dsp/filters/*`
3. `src/dsp/dist/*`
4. `tests/dsp/test_sub_phase_lock.cpp`
5. `tests/dsp/test_anti_click.cpp`
6. `tests/dsp/test_crossover_lr4.cpp`
7. `tests/dsp/test_oversampler.cpp`

Acceptance checks:
1. Sub path remains protected and mono-compatible in defined range.
2. Character path functional without violating constraints.
3. Aliasing and CPU baseline notes included.

## P4 - Voice/Engine Orchestration
Goal: deterministic note handling and render orchestration for mono/paraphonic behavior.

Agent tasks:
1. Implement `SynthEngine`, `VoiceManager`, `Voice`, `NoteStack`.
2. Implement legato/retrigger/steal policy per spec intent.
3. Integrate style-mode morph handling in engine-level parameter flow.

Expected outputs:
1. `src/engine/SynthEngine.*`
2. `src/engine/VoiceManager.*`
3. `src/engine/Voice.*`
4. `src/engine/NoteStack.*`

Acceptance checks:
1. Deterministic note lifecycle behavior in test scenarios.
2. No click regressions in note transitions.

## P5 - App Wiring + Macro UI
Goal: expose macro-first UX with strict domain-bound parameter flow.

Agent tasks (Frontend/UI):
1. Build macro-first views, mode selector, constrained controls.
2. Bind UI controls to domain-approved mappings only.
3. Implement style-mode behavior feedback without direct DSP bypass.

Agent tasks (Backend/DSP):
1. Provide stable parameter IDs and schema contract.
2. Wire app processor/editor integration path safely.

Expected outputs:
1. `src/app/PluginProcessor.*`
2. `src/app/PluginEditor.*`
3. `src/app/ParameterLayout.*`
4. `src/ui/components/*`
5. `src/ui/layout/*`
6. `src/ui/bindings/*`

Acceptance checks:
1. UI cannot set out-of-domain values.
2. Macro behavior matches style-mode constraints.

## P6 - Preset/State/Migration
Goal: stable save/load and forward-compatible state evolution.

Agent tasks:
1. Implement preset schema and migration layer.
2. Keep parameter ID stability guaranteed.
3. Add tests for backward/forward load behavior.

Expected outputs:
1. `src/preset/PresetManager.*`
2. `src/preset/PresetSchema.*`
3. `src/preset/PresetMigration.*`
4. state/preset tests in `tests/unit` and `tests/render` as needed

Acceptance checks:
1. Save/load deterministic.
2. Migration behavior validated and documented.

## P6.1 - Macro-10 Expansion + P7 Gate Closure
Goal: align runtime macro contract with knowledge target and close all pre-P7 deviations.

Agent tasks (Backend/DSP):
1. Implement 6 additional macros from `docs/spec/macro_10_contract_proposal.md`.
2. Wire new macro IDs through domain/engine/runtime path without dead/no-op exposure.
3. Add tests for mapping + rendered effect + style-bound behavior.
4. Fix P6 handoff evidence mismatches and version tagging consistency.

Agent tasks (Frontend/UI):
1. Expose/bind new macro controls according to macro contract proposal.
2. Keep performance-first UX (4 primary) while adding advanced-surface access to remaining macros.
3. Ensure no UI->DSP bypass and no stale binding IDs.

Agent tasks (Orchestrator):
1. Close process/documentation deviations from `docs/qa/p6_to_p7_gate_deviations.md`.
2. Publish final acceptance note `docs/qa/p6_final_gate_review.md`.
3. Update phase board/log statuses and next delegation queue.

Expected outputs:
1. Domain/app/ui/runtime support for all 10 macro controls
2. Updated handoffs and gate closure note
3. Updated master plan statuses/log

Acceptance checks:
1. No host-visible dead/no-op macro param.
2. P6->P7 deviation backlog closed.
3. Full build/test suite passes.

## P7 - QA + Render + Bench + UI Skin Integration
Goal: validate sonic correctness, constraints, CPU behavior, and integrate approved stylized UI asset pack.

Agent tasks:
1. Expand render regression tests and fixtures.
2. Add benchmark baselines for oversampling and voice CPU cost.
3. Run mandatory QA scenarios from developer and DSP docs.
4. Integrate UI design package from `docs/spec/ui_graphic_asset_contract.md`.
5. Validate frontend wiring against designer manifest and mapping files.

Expected outputs:
1. `tests/render/*`
2. `tests/dsp/*`
3. `bench/*`
4. QA summary note in `docs/qa/`
5. `assets/ui/designer/p7/exports/png/*`
6. `assets/ui/designer/p7/manifests/p7_ui_png_manifest.csv`
7. `assets/ui/runtime/p7/*`
8. `docs/qa/design_phase_handoffs/P7_design_handoff.md`

Acceptance checks:
1. Required scenario matrix complete.
2. Performance and aliasing constraints reported.
3. UI asset package count, naming, and mapping contract pass.

## P8 - CI/CD Hardening
Goal: automate quality gates and release artifact consistency.

Agent tasks:
1. Implement CI jobs for build/test/format/lint matrix.
2. Add release artifact workflow with checksums.
3. Ensure CI enforces phase quality gates.

Expected outputs:
1. `.github/workflows/ci.yml`
2. `.github/workflows/formatting.yml`
3. `.github/workflows/release.yml`

Acceptance checks:
1. CI jobs green on required targets.
2. Release artifacts generated reproducibly.

## 6. Mandatory Phase Update Protocol
After each phase handoff, orchestrator updates this file in four places:
1. `Last updated` date.
2. `Master Phase Board` status for that phase.
3. `Phase Update Log` with evidence.
4. `Open Risks` section if new blockers appear.

Required handoff packet from agent:
1. Changed file list.
2. Test commands and outcomes.
3. Known limitations.
4. Deviations from plan and ADR references.

## 7. Phase Update Log
| Date | Phase | Submitted By | Status Change | Evidence Summary | Next Action |
|---|---|---|---|---|---|
| 2026-02-21 | P0 | Orchestrator | Planned -> Done | Skeleton, rules, plan, briefs created | Start P1 backend delegation |
| 2026-02-21 | P1 | Backend/DSP + Orchestrator | Planned -> Review | Domain layer + tests delivered and validated (5/5 pass), review findings logged in `docs/qa/backend_p1_review.md` | Fix review findings, resubmit P1 |
| 2026-02-21 | P1 (Frontend support) | Frontend/UI + Orchestrator | Planned -> Review | Contract-alignment handoff reviewed; findings logged in `docs/qa/frontend_p1_review.md` | Reconcile schema/style/macro contract with backend before P5 |
| 2026-02-21 | P1 (Remediation) | Backend/DSP + Frontend/UI + Orchestrator | Review -> Done | Remediation accepted, tests pass, closure report in `docs/qa/p1_remediation_final_review.md` | Start P2 backend and keep frontend scaffold track |
| 2026-02-21 | P2 | Backend/DSP + Frontend/UI + Orchestrator | Planned -> Review | P2 delivered by both agents; review logged in `docs/qa/p2_review.md`, backend portability blocker found in `src/dsp/core/DenormalFlush.h` | Backend submits P2 portability+coverage fix, then re-review |
| 2026-02-21 | P2 (Remediation) | Backend/DSP + Frontend/UI + Orchestrator | Review -> Done | Remediation accepted, tests pass (11/11) and portability smoke compile passes; closure report in `docs/qa/p2_remediation_final_review.md` | Start P3 backend and continue frontend scaffold support |
| 2026-02-21 | P3 | Backend/DSP + Frontend/UI + Orchestrator | Planned -> Review | P3 delivered by both agents; review logged in `docs/qa/p3_review.md`, backend compile/integration blockers found in P3 modules | Backend submits P3 fix patch and re-review |
| 2026-02-21 | P3 (Remediation) | Backend/DSP + Frontend/UI + Orchestrator | Review -> Done | Remediation accepted, tests pass (17/17) and P3 header smoke compile passes; closure report in `docs/qa/p3_remediation_final_review.md` | Start P4 backend and continue frontend support |
| 2026-02-21 | Alignment (D-001/002/003) | Backend/DSP + TechStack/Repo + Orchestrator | In Progress -> Review | Alignment remediation reviewed in `docs/qa/alignment_remediation_review.md`; D-003 closed, D-001/D-002 partially unresolved | Close remaining alignment findings before P4 |
| 2026-02-21 | Alignment (F-ALIGN-001/002/003) | Backend/DSP + TechStack/Repo + Orchestrator | Review -> Done | Final review accepted in `docs/qa/alignment_remediation_final_review.md`; submodule pinning, strict test dependency policy, and RT-safe oversampler path verified | Unblock P4 and start engine orchestration |
| 2026-02-21 | P4 | Backend/DSP + Frontend/UI + Orchestrator | Planned -> Review | P4 handoff reviewed in `docs/qa/p4_review.md`; major RT/correctness findings identified (`F-P4-001`, `F-P4-002`) and one requirement gap (`F-P4-003`) | Backend submits P4 remediation patch, then re-review for P5 gate |
| 2026-02-21 | P4 (Remediation) | Backend/DSP + Frontend/UI + Orchestrator | Review -> Done | Remediation accepted in `docs/qa/p4_remediation_final_review.md`; RT-safe NoteStack, voice truncation fix, morph surface, and engine regression tests validated (`21/21`) | Start P5 app wiring + macro UI integration |
| 2026-02-22 | P5 | Backend/DSP + Frontend/UI + Orchestrator | Planned -> Done | App/APVTS wiring + macro UI integration completed and pushed in commit `21e1369` | Start P6 preset/state migration |
| 2026-02-22 | P6 | Backend/DSP + Frontend/UI + Orchestrator | Planned -> Done | Preset/state migration layer accepted via `docs/qa/backend_phase_handoffs/P6_handoff_fix.md` and `docs/qa/frontend_phase_handoffs/P6_handoff_fix.md` | Execute P6.1 macro contract closure |
| 2026-02-22 | P6.1 | Backend/DSP + Frontend/UI + Orchestrator | Planned -> Done | Final remediation accepted in `docs/qa/backend_phase_handoffs/P6_1_handoff_fix.md` and `docs/qa/frontend_phase_handoffs/P6_1_handoff_fix.md`; gate consolidated in `docs/qa/p6_final_gate_review.md` | Unblock P7 QA/render/bench |
| 2026-02-22 | P7 | Backend/DSP + Frontend/UI + UI Graphic Designer + Orchestrator | Planned -> Done | P7 remediation findings closed in `docs/qa/p7_fix_review.md`; acceptance captured in `docs/qa/p7_final_gate_review.md` with build pass, `ctest` 45/45, benchmark evidence, and UI asset contract validation (manifest/export/runtime 60/60). | Start P8 CI/CD hardening kickoff |

## 8. Open Risks and Blockers
| ID | Type | Description | Impact | Mitigation | Owner | Status |
|---|---|---|---|---|---|---|
| R-001 | Technical | Domain schema drift between backend and UI | High | Freeze contract at end of P1 before P5 full UI integration | Orchestrator | Mitigated |
| R-002 | Performance | Oversampling CPU spikes in nonlinear stacks | High | Per-module OS policy + bench gates in P7, baseline captured in `docs/qa/p7_final_gate_review.md` | Backend/DSP | Mitigated |
| R-003 | Quality | State migration regressions across versions | Medium | Version-tagged migration tests in P6 | Backend/DSP | Open |
| R-004 | Spec Alignment | P1 style/FM domain set diverges from documented MVP curated constraints | Medium | Resolve in P1 rework before marking phase Done | Backend/DSP + Orchestrator | Closed |
| R-005 | Contract | Frontend-backend mismatch in parameter IDs, macro set size, and style-set expectation | High | Create and sign off shared schema freeze artifact before P5 | Backend/DSP + Frontend/UI + Orchestrator | Closed |
| R-006 | Portability | `src/dsp/core/DenormalFlush.h` uses unconditional x86 intrinsics include and fails on non-x86 builds | High | Add architecture guards + no-op fallback + coverage test in P2 fix patch | Backend/DSP | Closed |
| R-007 | Integration | P3 modules (`StateVariableFilter`, `Saturator`, `Wavefolder`) are not compile-covered and currently fail include resolution in smoke compile | High | Fix include paths, add compile coverage/tests, rerun review gates | Backend/DSP | Closed |
| R-008 | DSP Correctness | `CrossoverLR4` HP denominator coefficients are used in process but not assigned in `setFrequency` | High | Assign HP denominator terms and add frequency-response assertions in tests | Backend/DSP | Closed |
| R-009 | RT-Safety | `Oversampler` can resize internal buffers in processing path (`getUpBuffer`/`processUp`) | High | Remove runtime resize and enforce preallocation from `prepare()` | Backend/DSP | Closed |
| R-010 | Reproducibility | `.gitmodules` declared but extern submodules are not pinned as gitlinks in repo index | High | Commit proper extern submodule gitlinks and verify clean configure path | TechStack/Repo | Closed |
| R-011 | Build Policy | Tests CMake allows binary-dir Catch2 fallback from `_deps`, weakening strict submodule-first policy | Medium | Remove fallback or gate behind explicit opt-in compat flag | TechStack/Repo | Closed |
| R-012 | RT-Safety | `NoteStack` can trigger `std::vector` growth during `insert(begin, ...)` before cap enforcement | High | Refactor to no-allocation fixed-capacity behavior and add stress test | Backend/DSP | Closed |
| R-013 | Audio Correctness | `Voice::processBlock` hard-truncates blocks above `1024` due fixed local buffer and zero-tail fill | High | Preallocate voice-owned buffer from `prepare(maxBlockSize)` and process full block | Backend/DSP | Closed |
| R-014 | Contract Gap | P4 required style-mode morph handling not exposed in engine path yet | Medium | Implement engine morph state/progress surface or approve explicit defer note before P5 | Backend/DSP + Orchestrator | Closed |
| R-015 | Contract Gap | P1 implemented 4 macros, but MVP knowledge docs require 10. Remaining 6 macros undocumented. | High | Temporary defer from ADR-005 superseded by P6.1 Macro-10 implementation and contract update. | Orchestrator | Closed (Superseded by P6.1) |
| R-016 | Gate Readiness | P6->P7 deviations remain open across docs, handoff integrity, and macro-target closure | High | Closed through `docs/qa/p6_final_gate_review.md` with full closure map and verification evidence | Backend/DSP + Frontend/UI + Orchestrator | Closed |

## 9. Next Delegation Queue
1. Start `P8 - CI/CD Hardening`.
2. Implement and validate workflow matrix for configure/build/test on required targets.
3. Add release artifact workflow with checksum generation and reproducibility checks.
