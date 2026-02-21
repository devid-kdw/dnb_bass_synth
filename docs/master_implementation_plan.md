# DnB Bass Synth Master Implementation Plan

Last updated: 2026-02-21  
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
| P2 | DSP Core Primitives | Planned | Backend/DSP | P1 | `src/dsp/core/*`, `src/dsp/safety/*` |
| P3 | Osc/Filter/Nonlinear DSP | Planned | Backend/DSP | P2 | `src/dsp/osc/*`, `src/dsp/filters/*`, `src/dsp/dist/*` |
| P4 | Voice/Engine Orchestration | Planned | Backend/DSP | P3 | `src/engine/*` deterministic voice path |
| P5 | App Wiring + Macro UI | Planned | Frontend/UI + Backend | P1, P4 | `src/app/*`, `src/ui/*` bound to domain |
| P6 | Preset/State/Migration | Planned | Backend/DSP | P5 | `src/preset/*`, state migration tests |
| P7 | QA + Render + Bench | Planned | Backend/DSP + Orchestrator | P6 | `tests/*`, `bench/*`, QA reports |
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

## P7 - QA + Render + Bench
Goal: validate sonic correctness, constraints, and CPU behavior.

Agent tasks:
1. Expand render regression tests and fixtures.
2. Add benchmark baselines for oversampling and voice CPU cost.
3. Run mandatory QA scenarios from developer and DSP docs.

Expected outputs:
1. `tests/render/*`
2. `tests/dsp/*`
3. `bench/*`
4. QA summary note in `docs/qa/`

Acceptance checks:
1. Required scenario matrix complete.
2. Performance and aliasing constraints reported.

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

## 8. Open Risks and Blockers
| ID | Type | Description | Impact | Mitigation | Owner | Status |
|---|---|---|---|---|---|---|
| R-001 | Technical | Domain schema drift between backend and UI | High | Freeze contract at end of P1 before P5 full UI integration | Orchestrator | Mitigated |
| R-002 | Performance | Oversampling CPU spikes in nonlinear stacks | High | Per-module OS policy + bench gates in P7 | Backend/DSP | Open |
| R-003 | Quality | State migration regressions across versions | Medium | Version-tagged migration tests in P6 | Backend/DSP | Open |
| R-004 | Spec Alignment | P1 style/FM domain set diverges from documented MVP curated constraints | Medium | Resolve in P1 rework before marking phase Done | Backend/DSP + Orchestrator | Closed |
| R-005 | Contract | Frontend-backend mismatch in parameter IDs, macro set size, and style-set expectation | High | Create and sign off shared schema freeze artifact before P5 | Backend/DSP + Frontend/UI + Orchestrator | Closed |

## 9. Next Delegation Queue
1. Start backend `P2 - DSP Core Primitives` implementation.
2. Keep frontend on scaffold/support tasks for P2-P4 until P5 integration gate.
3. Before P5, reconfirm schema contract with a short checkpoint review.
