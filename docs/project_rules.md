# DnB Bass Synth Project Rules

## 1. Purpose and Scope
This project builds a **specialized DnB bass VST3 synth** for tech/neuro/dark workflows.
It is **not** a general-purpose synth.
Design principle: **restriction-first** to keep all outcomes in a DnB-valid sound space.

## 2. Source of Truth (Mandatory)
All architecture and implementation decisions must align with these documents:
1. `knowledge/DNB Bass Synth VST Plugin Research.pdf`
2. `knowledge/DNB bass synth document for developer.pdf`
3. `knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx`
4. `knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx`
5. This rules file: `docs/project_rules.md`

If conflict appears, resolve by preferring explicit constraints from the knowledge docs and recording the resolution in ADR.

## 3. Workspace Boundary Rule
All work must stay inside:
`/Users/grzzi/Desktop/dnb_bass_synth`

No files, config, code generation, or asset operations are allowed outside project root.

## 4. Product Boundary Rule
Required product identity:
- dual-engine architecture: **Sub Engine + Character Engine**
- macro-first UX
- style mode behavior (Tech/Neuro/Dark in MVP)
- hard limits for phase, mono sub behavior, FM ratio space, and safety constraints

Forbidden:
- scope creep into broad EDM/general synth behavior
- unrestricted parameter spaces that break DnB-safe design intent

## 5. Architecture Boundary Rule (Critical)
Data path must be:
`app/ui -> domain/ConstraintEngine -> engine -> dsp`

Rules:
- `domain/ConstraintEngine` is the **only** authority for genre limits, mode mapping, macro mapping, and parameter sanitation.
- No direct UI-to-DSP bypass.
- No direct raw APVTS parameter consumption inside DSP that bypasses domain constraints.
- Sub Engine remains protected and stable; Character Engine holds aggressive processing.

## 6. Real-Time Safety Rules (Audio Thread)
Forbidden inside audio callback / hot RT path:
- dynamic allocation (`new`, `delete`, `malloc`, reallocation)
- blocking locks (`mutex`, `condition_variable`, blocking waits)
- file I/O or preset disk reads
- console/log I/O (`printf`, `std::cout`, synchronous logging)

Required:
- pre-allocation at init/prepare stage
- lock-free communication for non-RT diagnostics
- deterministic per-sample/per-block behavior
- denormal protection and NaN/Inf guards in DSP-critical paths

## 7. DSP Quality Rules
Mandatory quality constraints:
- phase reset policy for sub-critical behavior (as defined in knowledge docs)
- mono protection below crossover zone (100-120 Hz boundary policy)
- per-module oversampling for nonlinear blocks (FM/wavefold/distortion), not blanket global OS by default
- parameter smoothing to prevent zipper noise (typical 5-30 ms where applicable)
- DC blocker placement and safety chain order must follow DSP supplement intent

## 8. Dependency Policy
Approved baseline stack:
- C++20, JUCE 8.x, CMake 3.24+
- Catch2, nlohmann/json, spdlog, HIIR, optional passive CLAP header
- google/benchmark for bench module

Explicitly disallowed as separate project dependencies (per tech stack doc):
- Eigen
- standalone `fmt` dependency (spdlog bundled fmt is sufficient)

Any new dependency requires:
1. written justification
2. impact on binary/runtime/RT safety
3. ADR before merge

## 9. Coding and Repo Conventions (High-Level)
- Keep modules cohesive and boundaries strict (`domain` not mixed into `dsp` internals).
- Prefer deterministic, testable C++ classes over hidden side effects.
- Avoid hidden magic constants; expose constrained constants via domain/spec mapping.
- Add concise comments only where behavior is non-obvious.

## 10. Branch, Commit, and Task Discipline
- One focused task per branch/PR.
- PR must reference impacted knowledge docs sections.
- No architecture-changing merge without ADR update.
- No unfinished placeholder behavior in RT path without explicit TODO + guard.

## 11. ADR Discipline
Use `docs/adr/` for every major change in:
- architecture boundaries
- dependency policy
- oversampling strategy
- state/preset compatibility strategy

ADR entry must include: context, decision, alternatives, consequences.

## 12. Testing and Validation Gates
Minimum gates before completion of any major module:
- unit tests for constraints/mapping logic
- DSP correctness tests (phase lock, anti-click, crossover, safety)
- regression checks for mono compatibility below sub crossover
- CPU/aliasing checks for nonlinear modules
- state/preset load compatibility checks (including migration behavior)

## 13. Delegation Rules for All Agents
Every delegated agent must:
- use all 4 knowledge docs + this rules file as mandatory KB
- avoid conflicting decisions
- escalate any ambiguity before implementing architecture drift
- propose ADR for major deviation before coding

Frontend/UI-specific enforcement:
- UI remains macro-first
- UI bindings must honor domain-approved ranges and style behaviors
- UI cannot implement independent DSP rule logic that diverges from domain

Backend/DSP-specific enforcement:
- DSP modules must not introduce unconstrained/free behavior outside domain limits
- strict RT-safe implementation
- oversampling and safety chain follow DSP supplement + tech stack architecture
