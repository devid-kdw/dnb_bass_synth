# TechStack/Repo Agent Brief

## 1. Agent Scope
You own repository architecture alignment with the tech stack specification.
Primary responsibility:
- enforce dependency model and build layout from tech stack docs
- align CMake and repo structure with defined architecture boundaries
- document architectural decisions in ADR format

## 2. Mandatory Knowledge Base (Read Before Work)
You must reference all of the following:
1. `knowledge/DNB Bass Synth VST Plugin Research.pdf`
2. `knowledge/DNB bass synth document for developer.pdf`
3. `knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx`
4. `knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx`
5. `docs/project_rules.md`
6. `docs/qa/pre_p4_knowledge_alignment_audit.md`
7. `docs/qa/alignment_remediation_review.md`

## 3. Allowed File Scope
Primary editable areas:
- root build files (`CMakeLists.txt`, `.gitmodules`)
- `cmake/`
- `extern/`
- `docs/adr/`
- workflow/config scripts under `tools/scripts/`
- non-audio wiring stubs in `src/app/` only as needed for CMake target consistency

## 4. Forbidden Changes
- No DSP behavior changes in `src/dsp/` (handled by backend DSP agent).
- No UI feature scope creep.
- No domain boundary bypass.
- No hidden dependency additions without explicit rationale.

## 5. Non-Negotiable Rules
- Keep `domain -> dsp` architecture boundary intact.
- Follow submodule-first dependency policy from tech stack docs.
- Keep build reproducibility and cross-platform intent visible in repo config.
- Use ADR docs for architecture-affecting decisions.

## 6. Expected Output
Deliver:
1. Repo dependency model aligned with tech stack spec.
2. CMake baseline aligned with plugin-target architecture intent.
3. ADR baseline (`ADR-001..ADR-004`) documented.
4. Validation notes that prove `F-ALIGN-002` and `F-ALIGN-003` closure.

## 7. Scope Creep Guard
Do not implement P4/P5 DSP/UI features while doing repo alignment.

## 8. Execution Package (Use These Files)
- `docs/agent_briefs/techstack_repo_alignment_tasklist.md` (alignment fix tasklist)
- `docs/agent_briefs/techstack_repo_alignment_prompt.md` (copy/paste startup prompt)
- `docs/master_implementation_plan.md` (current phase status and gate conditions)
