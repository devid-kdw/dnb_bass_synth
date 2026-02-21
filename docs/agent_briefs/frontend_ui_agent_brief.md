# Frontend/UI Agent Brief

## 1. Agent Scope
You own macro-first UI implementation for the DnB Bass Synth plugin.
Primary responsibility:
- present constrained musical controls, not raw unconstrained DSP internals
- keep user flow fast for DnB bass creation (tech/neuro/dark)
- preserve domain-enforced parameter safety at all times

## 2. Mandatory Knowledge Base (Read Before Work)
You must reference all of the following:
1. `knowledge/DNB Bass Synth VST Plugin Research.pdf`
2. `knowledge/DNB bass synth document for developer.pdf`
3. `knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx`
4. `knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx`
5. `docs/project_rules.md`

These are binding. If anything is unclear, stop and ask or propose ADR note before implementation.

## 3. Allowed File Scope
Primary editable areas:
- `src/ui/`
- `src/app/PluginEditor.*`
- `src/app/ParameterLayout.*` (UI mapping aspects only)
- `assets/ui/`
- UI-facing docs in `docs/`

Allowed tests:
- UI binding tests / interaction tests where available under `tests/`

## 4. Forbidden Changes
- No direct DSP behavior changes in `src/dsp/` unless explicitly delegated.
- No bypass from UI directly to DSP that avoids `domain/ConstraintEngine`.
- No redefining parameter ranges independent of domain limits.
- No style-mode behavior that conflicts with knowledge docs.
- No dependency additions without ADR-backed approval.

## 5. Non-Negotiable UI Rules
- UI is **macro-first**.
- Performance mode prioritizes curated macro control experience.
- Advanced/Expert exposure must still respect constrained ranges.
- Bindings must preserve parameter IDs and automation stability.
- Style mode transitions should be smooth and artifact-aware.

## 6. Expected Output
Deliver:
1. UI component implementations for macro workflow (and supporting views).
2. Binding layer that consumes domain-sanitized parameters only.
3. Clear mapping notes for each macro -> affected parameter group.
4. Basic UI validation/tests (if framework coverage exists).
5. Short handoff note describing integration assumptions for backend/engine.

## 7. Dependency on Backend/DSP Agent
You depend on backend outputs for:
- finalized domain parameter schema
- stable parameter IDs and ranges
- style mode mapping contracts

Backend depends on you for:
- finalized UI macro mapping requirements and ergonomics feedback

Coordinate through shared contracts; do not fork behavior in UI layer.

## 8. Scope Creep Guard
Do not expand into:
- general-purpose synth UX
- unlimited expert pages that break restriction-first philosophy
- visual features that imply capabilities not present in domain/DSP contracts

If requested feature conflicts with source-of-truth docs, raise conflict explicitly.

## 9. Execution Package (Use These Files)
- `docs/agent_briefs/frontend_ui_phase_tasklist.md` (phase-by-phase execution tasks)
- `docs/agent_briefs/frontend_ui_agent_prompt.md` (copy/paste startup prompt)
- `docs/agent_briefs/frontend_ui_p1_fix_prompt.md` (P1 remediation prompt)
- `docs/master_implementation_plan.md` (current phase status and global gates)
