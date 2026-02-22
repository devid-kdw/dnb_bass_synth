# P7 Backend QA Handoff Fix

**Phase**: P7  
**Scope**: Remediation for `F-P7R-003`, `F-P7R-004`  
**Status proposal**: `Review`

## 1. Changed Files
- `tests/render/test_aliasing.cpp`
- `docs/qa/backend_phase_handoffs/P7_qa_handoff_fix.md`

## 2. Closure Map

| Finding | Closure | Evidence |
|---|---|---|
| `F-P7R-003` (aliasing QA evidence gap) | Reworked aliasing test from peak-only checks to deterministic spectral foldback metric. Test now renders a fixed stress scenario (C9, nonlinear chain enabled), computes Hann-windowed DFT band energies, and asserts foldback ratio threshold: `10*log10(E_alias_30-5000Hz / E_ref_7000-18000Hz) <= -4 dB`. Name/comments/threshold now match real measurement logic. | `tests/render/test_aliasing.cpp`; `ctest` test #36 pass; targeted run: `./tests/render_tests "[aliasing]" --rng-seed 20260222 --reporter compact` -> `All tests passed (4098 assertions in 1 test case)` |
| `F-P7R-004` (handoff evidence drift) | Re-ran required submodule/build/test/bench commands with exact CLI and captured concrete outputs (no placeholders). Added measurement context and reproducible command list. | Sections 3 and 4 below with exact command/result data from this run |

## 3. Measurement Context
- Build directory: `build`
- Generator: `Unix Makefiles` (`build/CMakeCache.txt`)
- `CMAKE_BUILD_TYPE`: empty (`CMAKE_BUILD_TYPE:STRING=` in `build/CMakeCache.txt`)
- Bench binaries report: `***WARNING*** Library was built as DEBUG. Timings may be affected.`
- Conclusion: measurements below are from non-Release (debug-instrumented) context.

## 4. Verification Commands and Exact Results

### 4.1 Submodules
```bash
tools/scripts/init_submodules.sh
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
Result: build finished successfully, including `domain_tests`, `engine_tests`, `dsp_tests`, `render_tests`, `preset_tests`, and all three bench binaries.

### 4.3 Test Suite
```bash
cd build && ctest --output-on-failure
```
Result (exact totals):
```text
100% tests passed, 0 tests failed out of 45
Total Test time (real) =   1.09 sec
```

Aliasing-specific deterministic check:
```bash
cd build && ./tests/render_tests "[aliasing]" --rng-seed 20260222 --reporter compact
```
Result:
```text
Filters: [aliasing]
RNG seed: 20260222
All tests passed (4098 assertions in 1 test case)
```

### 4.4 Bench Verification (time suffix commands)
```bash
cd build && ./bench/bench_voice_cpu --benchmark_min_time=0.05s --benchmark_repetitions=1
```
Result:
```text
2026-02-22T14:16:43+01:00
BM_VoiceManager_ProcessBlock        787 us          786 us           88
```

```bash
cd build && ./bench/bench_oversampling --benchmark_min_time=0.05s --benchmark_repetitions=1
```
Result:
```text
2026-02-22T14:16:51+01:00
BM_Oversampler_Process        267 us          267 us          269
```

```bash
cd build && ./bench/bench_macro_updates --benchmark_min_time=0.05s --benchmark_repetitions=1
```
Result:
```text
2026-02-22T14:16:55+01:00
BM_ConstraintEngine_Process       63.8 ns         63.7 ns      1158940
```

Note: all three benchmark runs emitted host metadata warnings about CPU frequency/thread affinity; benchmark data still executed and reported successfully.

## 5. Open Questions
- None blocking for P7 remediation scope.
