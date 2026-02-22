# P8 Backend CI/CD Handoff

**Phase**: P8  
**Scope**: Backend CI/CD hardening support  
**Status proposal**: `Review`

## 1. Changed Files
- `.github/workflows/ci.yml`
- `.github/workflows/release.yml`
- `docs/qa/backend_phase_handoffs/P8_handoff.md`

## 2. Closure Map (Backend P8 Scope)

| Scope ID | Requirement | Closure | Evidence |
|---|---|---|---|
| `P8-CI-001` | Reproducible backend quality gates (`configure -> build -> ctest`) with backend test binaries coverage (`domain_tests`, `engine_tests`, `dsp_tests`, `render_tests`, `preset_tests`). | Added blocking `backend_quality_gates` CI job (Debug) and blocking `backend_quality_gates_release` release job (Release). Both run `init_submodules`, CMake configure/build, backend binary presence/list checks, then `ctest --output-on-failure`. | `.github/workflows/ci.yml`, `.github/workflows/release.yml` |
| `P8-CI-002` | Bench policy must have clear status and avoid false-fail in Debug context. | Added `bench_evidence_debug` CI job as explicit non-blocking evidence (`continue-on-error: true`) with exact benchmark CLI commands and artifact log upload. | `.github/workflows/ci.yml` |
| `P8-CI-003` | Release artifact step must not bypass backend gates and must include checksum evidence. | Added release artifact job gated with `needs: backend_quality_gates_release`; re-runs `ctest` before packaging; generates and uploads SHA256 checksum (`.sha256`) and writes checksum summary evidence. | `.github/workflows/release.yml` |
| `P8-CI-004` | No DSP feature scope changes outside P8 hardening. | Only workflow and handoff documentation files changed; no DSP/domain/engine runtime code modified. | Changed-files list above |

## 3. Measurement Context
- Local verification build directory: `build`
- Local bench context: debug-instrumented benchmark library (`***WARNING*** Library was built as DEBUG. Timings may be affected.`)
- CI contexts introduced:
  - `ci.yml`: Debug blocking gate + Debug non-blocking bench evidence
  - `release.yml`: Release gate + Release artifact packaging/checksum

## 4. Mandatory Verification Commands and Results

### 4.1 Submodules
```bash
bash tools/scripts/init_submodules.sh
```
Result:
```text
[init_submodules] syncing submodule metadata
Synchronizing submodule url for 'extern/benchmark'
Synchronizing submodule url for 'extern/catch2'
Synchronizing submodule url for 'extern/clap-cleveraudio'
Synchronizing submodule url for 'extern/hiir'
Synchronizing submodule url for 'extern/json'
Synchronizing submodule url for 'extern/juce'
Synchronizing submodule url for 'extern/spdlog'
[init_submodules] initializing and updating extern submodules
[init_submodules] done
```

### 4.2 Build
```bash
cmake --build build --parallel
```
Result:
```text
Build completed successfully.
Targets include: DnBBassSynth, DnBBassSynth_VST3, domain_tests, engine_tests, dsp_tests, render_tests, preset_tests, bench_voice_cpu, bench_oversampling, bench_macro_updates.
```

### 4.3 Test Suite
```bash
cd build && ctest --output-on-failure
```
Result:
```text
100% tests passed, 0 tests failed out of 45
Total Test time (real) =   1.20 sec
```

### 4.4 Bench Smoke (required because bench CI policy was touched)
```bash
cd build && ./bench/bench_voice_cpu --benchmark_min_time=0.05s --benchmark_repetitions=1
```
Result:
```text
BM_VoiceManager_ProcessBlock        832 us          832 us           88
```

```bash
cd build && ./bench/bench_oversampling --benchmark_min_time=0.05s --benchmark_repetitions=1
```
Result:
```text
BM_Oversampler_Process        275 us          274 us          258
```

```bash
cd build && ./bench/bench_macro_updates --benchmark_min_time=0.05s --benchmark_repetitions=1
```
Result:
```text
BM_ConstraintEngine_Process       57.5 ns         57.5 ns      1293183
```

Note: all benchmark runs also printed host metadata warnings about CPU frequency/thread affinity; commands completed with exit code `0`.

## 5. CI/Release Command Paths Added

### 5.1 CI backend gate path (blocking)
```bash
cmake -S . -B build -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DDNB_ENABLE_PLUGIN_TARGET=OFF -DDNB_BUILD_TESTS=ON -DDNB_BUILD_BENCH=ON
cmake --build build --parallel
./build/tests/domain_tests --list-test-names-only
./build/tests/engine_tests --list-test-names-only
./build/tests/dsp_tests --list-test-names-only
./build/tests/render_tests --list-test-names-only
./build/tests/preset_tests --list-test-names-only
cd build && ctest --output-on-failure
```

### 5.2 CI bench evidence path (non-blocking)
```bash
cmake -S . -B build -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DDNB_ENABLE_PLUGIN_TARGET=OFF -DDNB_BUILD_TESTS=OFF -DDNB_BUILD_BENCH=ON
cmake --build build --parallel --target bench_voice_cpu bench_oversampling bench_macro_updates
./build/bench/bench_voice_cpu --benchmark_min_time=0.05s --benchmark_repetitions=1
./build/bench/bench_oversampling --benchmark_min_time=0.05s --benchmark_repetitions=1
./build/bench/bench_macro_updates --benchmark_min_time=0.05s --benchmark_repetitions=1
```

### 5.3 Release gate + artifact/checksum path
```bash
cmake -S . -B build -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DDNB_ENABLE_PLUGIN_TARGET=ON -DDNB_BUILD_TESTS=ON -DDNB_BUILD_BENCH=OFF
cmake --build build --parallel
cd build && ctest --output-on-failure
artifact_dir="build/DnBBassSynth_artefacts/Release/VST3"
if [[ ! -d "${artifact_dir}" ]]; then artifact_dir="build/DnBBassSynth_artefacts/VST3"; fi
zip -r build/release_bundle/DnBBassSynth_vst3_${GITHUB_REF_NAME}.zip "${artifact_dir}"
shasum -a 256 build/release_bundle/DnBBassSynth_vst3_${GITHUB_REF_NAME}.zip > build/release_bundle/DnBBassSynth_vst3_${GITHUB_REF_NAME}.zip.sha256
```

## 6. Open Questions
- None blocking for backend P8 CI/CD hardening scope.
