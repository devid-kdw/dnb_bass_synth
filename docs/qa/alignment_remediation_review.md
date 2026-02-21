# Alignment Remediation Review (D-001, D-002, D-003)

Date: 2026-02-21  
Reviewer: Orchestrator

## 1. Scope Reviewed
Backend alignment handoff:
- `docs/qa/backend_phase_handoffs/ALIGN_D001_handoff.md`
- `src/dsp/core/Oversampler.h`
- `src/dsp/osc/CharacterOscillator.h`
- `tests/dsp/test_oversampler.cpp`
- `tests/dsp/test_character_osc.cpp`
- `tests/dsp/test_saturator.cpp`

Techstack/repo alignment handoff:
- `docs/qa/alignment_handoffs/ALIGN_D002_D003_handoff.md`
- `.gitmodules`
- `CMakeLists.txt`
- `tests/CMakeLists.txt`
- `tools/scripts/init_submodules.sh`
- `docs/adr/ADR-001-juce-vs-alternatives.md`
- `docs/adr/ADR-002-per-module-oversampling.md`
- `docs/adr/ADR-003-domain-gate-only.md`
- `docs/adr/ADR-004-passive-clap-header.md`
- `src/app/PluginProcessor.cpp`
- `src/app/PluginEditor.cpp`

Reference baseline:
- `docs/qa/pre_p4_knowledge_alignment_audit.md`

## 2. Validation Executed
### 2.1 Existing build/test
```bash
cmake --build build --parallel
cd build && ctest --output-on-failure
```
Result:
- `100% tests passed, 0 tests failed out of 17`

### 2.2 Clean configure reproducibility check
```bash
cmake -S . -B build_clean_alignment -DDNB_ENABLE_PLUGIN_TARGET=ON -DDNB_BUILD_TESTS=ON -DDNB_BUILD_BENCH=ON
```
Result:
- configure fails on fresh build because `extern/catch2` is missing and no fallback source exists in fresh binary dir.

## 3. Findings (ordered by severity)

### F-ALIGN-001 (High): D-001 still violates RT-safe no-allocation rule in processing path
Files:
- `src/dsp/core/Oversampler.h:72`
- `src/dsp/core/Oversampler.h:80`

Issue:
- `getUpBuffer()` and `processUp()` can call `upSampledBuffer.resize(...)`, which can allocate memory at runtime.
- knowledge/project RT-safe rule forbids runtime allocations in audio path.

Impact:
- unresolved RT-safety drift remains in oversampling core path.

Required fix:
1. Remove runtime resize in processing methods.
2. Enforce max block assumptions set in `prepare()` (assert/guard + fail-safe without allocation).

### F-ALIGN-002 (High): D-002 is only partially closed; submodule model is declared but not pinned in repo index
Evidence:
- `.gitmodules` exists, but tracked git entries still show only:
  - `extern/.gitkeep` (no gitlinks for `extern/juce`, `extern/catch2`, etc.)

Issue:
- dependency model is declared, but reproducible pinned submodule state is not committed.

Impact:
- repository is not yet in a fully reproducible submodule-first state required by tech stack alignment.

Required fix:
1. Add/track actual submodule gitlinks for required extern modules.
2. Re-run validation from a clean build directory after submodule init.

### F-ALIGN-003 (Medium): tests layer still allows local binary-dir fallback path
File:
- `tests/CMakeLists.txt:14`

Issue:
- `tests/CMakeLists.txt` allows fallback to `${CMAKE_BINARY_DIR}/_deps/catch2-src` if present.
- this can hide missing extern setup on developer machines with stale build dirs.

Impact:
- weakens strict submodule-first enforcement.

Required fix:
1. Remove binary-dir fallback for strict mode, or gate it behind an explicit opt-in compatibility flag.
2. Keep failure path as default when `extern/catch2` is not initialized.

### F-ALIGN-004 (Info): D-003 ADR baseline is implemented
Files:
- `docs/adr/ADR-001-juce-vs-alternatives.md`
- `docs/adr/ADR-002-per-module-oversampling.md`
- `docs/adr/ADR-003-domain-gate-only.md`
- `docs/adr/ADR-004-passive-clap-header.md`

Status:
- closed.

## 4. Decision
Overall alignment status: **Review (not accepted as fully closed)**.

`D-003` is closed, but `D-001` and `D-002` remain partially unresolved under strict no-drift criteria.

## 5. P4 Gate
**P4 readiness: NO-GO (strict mode).**

P4 should not start until:
1. `F-ALIGN-001` is fixed (no runtime resize/allocation in oversampling process path).
2. `F-ALIGN-002` is fixed (extern submodule gitlinks pinned in repo).
3. `F-ALIGN-003` is resolved or explicitly accepted as a policy exception.

## 6. Agent Briefing Updates Logged
Repo-techstack alignment updates are now reflected in:
1. `docs/agent_briefs/backend_dsp_agent_brief.md` (`Repo Alignment Updates (Mandatory)`)
2. `docs/agent_briefs/frontend_ui_agent_brief.md` (`Repo Alignment Updates (Mandatory)`)
