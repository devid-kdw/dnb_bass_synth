# ALIGN D002/D003 Handoff

Date: 2026-02-21  
Owner: Techstack/Repo Agent  
Scope: Alignment remediation for `D-002` and `D-003` (pre-P4 audit)

## 1. Changed Files
- `.gitmodules`
- `CMakeLists.txt`
- `tests/CMakeLists.txt`
- `bench/CMakeLists.txt`
- `bench/bench_smoke.cpp`
- `tools/scripts/init_submodules.sh`
- `src/app/PluginProcessor.h`
- `src/app/PluginProcessor.cpp`
- `src/app/PluginEditor.h`
- `src/app/PluginEditor.cpp`
- `docs/adr/README.md`
- `docs/adr/ADR-001-juce-vs-alternatives.md`
- `docs/adr/ADR-002-per-module-oversampling.md`
- `docs/adr/ADR-003-domain-gate-only.md`
- `docs/adr/ADR-004-passive-clap-header.md`

## 2. Verification Commands + Result
1. `cmake --build build --parallel`  
   Result: **PASS**
   - CMake regeneration succeeded.
   - `domain_tests` and `dsp_tests` built successfully.
   - Informational warning shown: JUCE/benchmark submodules not initialized in current workspace.
   - Catch2 was resolved without `FetchContent` via non-FetchContent fallback path (`build/_deps/catch2-src`) because `extern/catch2` is not yet initialized.

2. `cd build && ctest --output-on-failure`  
   Result: **PASS** (`17/17` tests passed, `0` failed)

3. `FetchContent` removal check (active test path)
   - Ran repo grep for `FetchContent` in build/test wiring.
   - `tests/CMakeLists.txt` no longer contains `FetchContent` API usage.
   - `FetchContent` appears only in historical ADR text (`docs/adr/ADR-005-P1-Test-Dependency.md`), not in active CMake execution path.

4. Extern/bootstrap artifacts check
   - `.gitmodules`: **present**
   - `tools/scripts/init_submodules.sh`: **present** and executable

## 3. Closure Map

### D-002 (Dependency model + CMake/plugin wiring divergence)
Status: **Closed -> Review**

Delivered:
- Submodule-first dependency baseline introduced via `.gitmodules` for extern modules:
  - `extern/juce`, `extern/catch2`, `extern/json`, `extern/hiir`, `extern/spdlog`, `extern/clap-cleveraudio`, `extern/benchmark`
- Reproducible bootstrap script added:
  - `tools/scripts/init_submodules.sh` (`git submodule sync --recursive` + `git submodule update --init --recursive`)
- Top-level CMake aligned with tech stack intent:
  - C++20 baseline retained
  - JUCE plugin target intent wired (`juce_add_plugin`) and gated on submodule availability
  - tests wiring and bench wiring explicitly present
- Test layer dependency path migrated off `FetchContent`:
  - `tests/CMakeLists.txt` now resolves Catch2 through extern/submodule path, with explicit fatal guidance when dependency is absent

### D-003 (ADR baseline incomplete)
Status: **Closed -> Review**

Delivered ADR baseline in `docs/adr/`:
- `ADR-001-juce-vs-alternatives.md`
- `ADR-002-per-module-oversampling.md`
- `ADR-003-domain-gate-only.md`
- `ADR-004-passive-clap-header.md`

Each ADR contains required structure:
- context
- decision
- alternatives
- consequences

## 4. Open Questions / Constraints
- Current workspace does not yet have initialized extern submodule working trees under `extern/*`; therefore local build used fallback Catch2 source already present in `build/_deps`.
- For strict clean-clone reproducibility, repository review should confirm pinned submodule commits (gitlink entries) for all extern paths before merge.

## 5. Proposed Status
- `D-002`: **Review**
- `D-003`: **Review**
