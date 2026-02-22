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

## 9. Repo Alignment Updates (Mandatory)
Effective from 2026-02-21 alignment review:
1. Before any fresh configure/build, run `tools/scripts/init_submodules.sh`.
2. Do not reintroduce `FetchContent` dependency flow in UI-related CMake wiring.
3. Do not rely on stale `build/_deps` fallback artifacts as primary dependency path.
4. Keep UI contract discipline: no runtime assumptions on unstable plugin wiring until backend/domain contract is explicitly marked stable.
5. Read and follow:
   - `docs/qa/alignment_handoffs/ALIGN_D002_D003_handoff.md`
   - `docs/qa/alignment_remediation_review.md`
   - `docs/qa/backend_phase_handoffs/ALIGN_D001_handoff.md`

## 10. Execution Package (Use These Files)
- `docs/agent_briefs/frontend_ui_phase_tasklist.md` (phase-by-phase execution tasks)
- `docs/agent_briefs/frontend_ui_agent_prompt.md` (copy/paste startup prompt)
- `docs/agent_briefs/frontend_ui_p1_fix_prompt.md` (P1 remediation prompt)
- `docs/agent_briefs/frontend_ui_p2_fix_tasklist.md` (P2 conditional alignment tasklist)
- `docs/agent_briefs/frontend_ui_p2_fix_prompt.md` (P2 conditional alignment prompt)
- `docs/agent_briefs/frontend_ui_p7_design_integration_tasklist.md` (designer asset integration tasklist)
- `docs/agent_briefs/frontend_ui_p7_design_integration_prompt.md` (designer asset integration prompt)
- `docs/master_implementation_plan.md` (current phase status and global gates)

## 11. Graphic Designer Integration Workflow (Mandatory)
When graphic designer track is active, frontend must follow this exact sequence:
1. Read `docs/spec/ui_graphic_asset_contract.md`.
2. Read latest designer handoff in `docs/qa/design_phase_handoffs/`.
3. Read designer mapping file:
   - `assets/ui/designer/p7/manifests/p7_ui_control_asset_map.md`
4. Integrate only assets listed in:
   - `assets/ui/designer/p7/manifests/p7_ui_png_manifest.csv`
5. Move/copy approved runtime assets to:
   - `assets/ui/runtime/p7/`

Frontend must not:
1. invent missing asset states silently
2. bind controls to assets outside manifest
3. modify control semantics to fit visuals

Frontend must report:
1. exact `ui_control -> param_id -> asset_file` map in phase handoff
2. any asset gaps/blockers back to orchestrator and designer
