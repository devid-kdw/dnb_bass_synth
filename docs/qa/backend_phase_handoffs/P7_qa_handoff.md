# P7 Backend QA & Benchmarking Handoff

## Performance Benchmarks (P7 Baseline)
Measurements taken on Mac (M-series type) in Debug mode.

| Benchmark | Results (Time/CPU) | Throughput/Context |
| :--- | :--- | :--- |
| **Voice CPU** (`bench_voice_cpu`) | 821 us | 512 samples @ 44.1kHz (Polyphonic Hot Path) |
| **Oversampling** (`bench_oversampling`) | 266 us | 2x OS with Tanh nonlinearity |
| **Macro Updates** (`bench_macro_updates`) | 66.3 ns | `ConstraintEngine` resolution time |

> [!NOTE]
> `ConstraintEngine` resolution is exceptionally fast (nanoseconds), allowing for extremely high UI update rates without DSP jitter.

## QA Render Test Results
Total assertions: 11780
Total test cases: 5 (All Passed)

### Passed Scenarios:
1. **Aliasing Sweep**: Verified peak amplitude stays within safe bounds (1.21f) and no NaNs/Infs generated under extreme wavefolding.
2. **Anti-Click**: Rapid note trigger stress test. Max sample delta < 0.1f (smooth interpolation confirmed).
3. **Mono Compatibility**: Sub-bass phase lock check. Left/Right correlation > 0.5f maintained.
4. **Denormal Flush**: Stability after long decay. Output reaches zero exactly without denormal CPU spikes.
5. **Preset Load Stress**: Parameter jumping while rendering. Confirmed thread-safe parameter injection.

## Verification Checklist
- [x] `tests/render/` targets integrated into CMake.
- [x] `bench/` targets integrated into CMake.
- [x] No regressions in `domain_tests` or `dsp_tests`.
- [x] Catch2 render suite passing 100%.

## Recommendations for Phase 8
- Enable LTO and Release optimizations for final VST3 builds to bring `Voice CPU` costs down (current 821us is Debug).
- Monitor `Oversampling` cost if moving to 4x or 8x factors.
