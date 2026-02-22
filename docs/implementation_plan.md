# DnB Bass Synth Implementation Plan

Detailed phase tracking and mandatory per-phase updates are maintained in:
`docs/master_implementation_plan.md`

## 1. MVP Goal
Deliver a production-viable **VST3 MVP** that enforces DnB-safe behavior via restriction-first design:
- dual-engine signal architecture (Sub + Character)
- 3 style modes in MVP (Tech/Neuro/Dark)
- macro-first UI with constrained parameter space
- stable mono-compatible low end, RT-safe DSP execution

MVP target is based on:
- `knowledge/DNB bass synth document for developer.pdf` (Feature tiers + parameter sheet)
- `knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx` (DSP implementation details)
- `knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx` (stack/repo/CI architecture)
- `knowledge/DNB Bass Synth VST Plugin Research.pdf` (genre logic + restriction philosophy)

## 2. Phase Plan and Dependency Order

### Phase 0 - Foundation Setup
Scope:
- initialize skeleton folders/modules
- configure baseline CMake/JUCE layout
- set dependency placeholders (extern policy)
- add docs scaffolding and ADR folder

Depends on: none
Blocks: all coding phases
DoD:
- repository structure exists and is documented
- rules and implementation plan approved

### Phase 1 - Core Domain Constraints (First Functional Layer)
Scope:
- implement `domain/` contracts: `ConstraintEngine`, style mode limits, macro maps, parameter specs
- define normalized parameter schema and DnB-safe mapping paths
- enforce all hard constraints from developer spec (phase lock policy boundaries, release caps, FM ratio curation, etc.)

Depends on: Phase 0
Blocks: DSP and UI bindings
DoD:
- all runtime parameter paths are validated through domain layer
- tests for range clamps/style mappings pass

### Phase 2 - DSP Core Primitives
Scope:
- implement DSP base building blocks in `src/dsp/core` and `src/dsp/safety`
- anti-click ramp, smoother, denormal/NaN guards, DC blocker, safety utilities
- set oversampling interfaces and per-module strategy hooks

Depends on: Phase 1 (for valid parameter contracts)
Blocks: oscillator/filter/fx modules
DoD:
- RT-safe primitives compile and unit tests pass
- no forbidden RT operations in hot paths

### Phase 3 - Oscillators + Filters + Nonlinear Character Modules
Scope:
- sub oscillator path (phase reset behavior and protected low-end policy)
- character oscillator path (wavetable/FM operators)
- filter modules (SVF/notch/formant/crossover foundations)
- nonlinear modules (wavefold/distortion chain) with module-specific oversampling

Depends on: Phase 2
Blocks: voice engine and audio integration
DoD:
- rendered audio path for sub and character components works in isolation
- aliasing/CPU profile within expected limits for baseline settings

### Phase 4 - Engine Layer (Voice + Note Behavior)
Scope:
- `SynthEngine`, `VoiceManager`, `Voice`, note stack, legato/retrigger behavior
- deterministic voice policy and portamento handling
- style-mode morph path integration (where phase-compatible)

Depends on: Phase 3
Blocks: integrated plugin audio behavior
DoD:
- monophonic/paraphonic behavior deterministic and test-covered
- no click regressions across note-on/off and glide scenarios

### Phase 5 - App Layer Wiring + UI Macro Layer
Scope:
- APVTS layout wiring in `app/`
- macro-first UI bindings in `ui/` through domain-sanitized values only
- enforce style-mode dependent control behavior in UI presentation

Depends on: Phase 1 and Phase 4
Blocks: preset/state and usability validation
DoD:
- UI cannot bypass domain constraints
- macro controls drive expected multi-parameter behavior

### Phase 6 - Preset/State Serialization + Migration
Scope:
- implement preset manager/schema/migration in `preset/`
- stable parameter IDs and version-tagged state loading
- robust unknown-field handling (forward compatibility behavior)

Depends on: Phase 5
Blocks: release-readiness
DoD:
- save/load deterministic across restart
- migration tests pass for versioned states

### Phase 6.1 - Macro-10 Contract Expansion + Gate Closure
Scope:
- implement full 10-macro contract using:
  - locked 4 macros from `docs/spec/p1_schema_freeze.md`
  - 6 additional macros from `docs/spec/macro_10_contract_proposal.md`
- close P6->P7 deviations in:
  - `docs/qa/p6_to_p7_gate_deviations.md`
- resolve documentation/process drift (handoff integrity + plan status alignment)

Depends on: Phase 6
Blocks: Phase 7
DoD:
- no host-visible dead/no-op macro parameters
- each new macro has domain mapping + runtime effect + test evidence
- P6->P7 deviation backlog closed
- final gate review note accepted

### Phase 7 - Tests, Render QA, Benchmarks
Scope:
- unit + dsp + render test suites (`tests/unit`, `tests/dsp`, `tests/render`)
- benchmark baselines (`bench/`) for oversampling and voice CPU cost
- include mono-correlation, aliasing, anti-click, long-note stability scenarios

Depends on: Phase 6.1
Blocks: CI gate completion
DoD:
- required tests pass in local debug/release profiles
- key DSP regressions are covered by deterministic checks

### Phase 8 - CI/CD and Delivery Hardening
Scope:
- workflow scaffolding (`.github/workflows`)
- build + test pipelines for macOS and Windows targets
- formatting/lint gates and artifact output path conventions

Depends on: Phase 7
Blocks: release packaging
DoD:
- CI green for required jobs
- release workflow produces expected artifacts

## 3. Module Task Breakdown
- `domain/`: constraints, style limits, macro maps, parameter schema
- `dsp/core`: math/smoothing/safety primitives
- `dsp/osc`: sub + character oscillators, FM operators
- `dsp/filters`: SVF/notch/formant/crossover/comb/frequency-shift path by phase
- `dsp/dist`: saturation/wavefold/clip/autogain chain
- `engine/`: voice lifecycle, note stack, render orchestration
- `app/`: processor/editor/state/layout wiring
- `ui/`: macro views, style-mode controls, safe attachments
- `preset/`: serialization/migration/default patch policy
- `tests/` + `bench/`: correctness and performance verification

## 4. Major Risks and Mitigations

### RT Safety Violations
Risk:
- hidden allocation/lock/log in audio thread causing dropouts
Mitigation:
- strict RT bans from project rules
- static review + tests + lint checks for hot-path code

### Aliasing in Nonlinear Modules
Risk:
- audible fold/FM/clip artifacts in upper spectrum
Mitigation:
- per-module oversampling policy
- aliasing sweep tests and benchmarked OS factors

### Oversampling CPU Overhead
Risk:
- high CPU in dense patches
Mitigation:
- avoid global OS by default
- benchmark each nonlinear stage and tune factors module-by-module

### Parameter Zipper Noise / Instability
Risk:
- stepping artifacts during automation/LFO modulation
Mitigation:
- parameter smoothing policy per parameter class
- explicit tests for modulation transitions

### State/Preset Migration Breakage
Risk:
- old projects fail load or automation mappings break
Mitigation:
- stable parameter IDs
- version-tagged state and migration layer
- compatibility tests in CI

### Macro Contract Drift
Risk:
- knowledge target (10 macros) diverges from active runtime contract
Mitigation:
- adopt `docs/spec/macro_10_contract_proposal.md`
- execute closure backlog from `docs/qa/p6_to_p7_gate_deviations.md`

## 5. Definition of Done (Global)
A phase is done only when:
- implementation matches knowledge constraints
- no architecture boundary violation (`domain` bypass not allowed)
- required tests for phase pass
- decisions and deviations are documented (ADR when architecture-impacting)
- code is ready for downstream agent integration without hidden assumptions

## 6. Current Gate Backlog (Must Close Before P7)
Active backlog reference:
- `docs/qa/p6_to_p7_gate_deviations.md`

Implementation agents must treat this backlog as mandatory for P7 gate readiness.
