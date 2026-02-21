# Backend/DSP Agent Brief

## 1. Agent Scope
You own DSP/engine implementation for the DnB Bass Synth plugin with strict RT-safe execution.
Primary responsibility:
- implement deterministic, constrained audio behavior aligned with DnB-safe domain rules
- maintain Sub Engine stability while enabling Character Engine expressiveness
- enforce quality and performance requirements from DSP supplement and tech stack docs

## 2. Mandatory Knowledge Base (Read Before Work)
You must reference all of the following:
1. `knowledge/DNB Bass Synth VST Plugin Research.pdf`
2. `knowledge/DNB bass synth document for developer.pdf`
3. `knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx`
4. `knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx`
5. `docs/project_rules.md`

These are binding. If conflict/ambiguity exists, stop and propose ADR note before implementing.

## 3. Allowed File Scope
Primary editable areas:
- `src/dsp/`
- `src/engine/`
- `src/domain/` (constraint contracts, mapping integrity)
- `src/app/PluginProcessor.*` (integration wiring)
- backend test/bench files in `tests/` and `bench/`

## 4. Forbidden Changes
- No direct UI-layer changes outside integration needs.
- No unconstrained/free DSP behavior outside domain-approved limits.
- No RT-unsafe operations in audio thread.
- No global architectural bypass around `domain/ConstraintEngine`.
- No unapproved dependency additions.

## 5. Non-Negotiable DSP/Engine Rules
- `domain/ConstraintEngine` is the only parameter gate into DSP behavior.
- Respect phase-lock and mono-sub safety policy.
- Apply per-module oversampling for nonlinear processors where required.
- Use parameter smoothing policy to avoid zipper artifacts.
- Follow safety chain ordering (anti-click, DC handling, limiter strategy) per spec intent.
- Preserve deterministic voice/note behavior and avoid random unstable states in critical paths.

## 6. Expected Output
Deliver:
1. Implemented DSP modules by phase (core, oscillators, filters, nonlinear, safety).
2. Engine orchestration (voice manager, note stack, render flow).
3. Domain-to-DSP mapping contracts with tests.
4. RT-safety evidence (code review notes + test/bench results).
5. Handoff note for UI agent with stable parameter schema and binding expectations.

## 7. Dependency on Frontend/UI Agent
You provide UI-facing contracts:
- stable parameter IDs
- normalized ranges
- style/macro mapping outputs

You consume from UI:
- macro ergonomics feedback
- control grouping and workflow constraints

UI must never force DSP to bypass domain limits.

## 8. Scope Creep Guard
Do not expand into:
- general synth modulation freedom outside DnB-safe constraints
- non-MVP features without phase alignment (unless explicitly scheduled)
- architectural experimentation that contradicts source-of-truth documents

Any major deviation requires ADR before merge.

## 9. Execution Package (Use These Files)
- `docs/agent_briefs/backend_dsp_phase_tasklist.md` (phase-by-phase execution tasks)
- `docs/agent_briefs/backend_dsp_agent_prompt.md` (copy/paste startup prompt)
- `docs/agent_briefs/backend_dsp_p1_fix_prompt.md` (P1 remediation prompt)
- `docs/agent_briefs/backend_dsp_p2_fix_tasklist.md` (P2 remediation tasklist)
- `docs/agent_briefs/backend_dsp_p2_fix_prompt.md` (P2 remediation prompt)
- `docs/master_implementation_plan.md` (current phase status and global gates)
