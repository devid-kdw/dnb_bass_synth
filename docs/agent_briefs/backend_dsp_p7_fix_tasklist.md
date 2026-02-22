# Backend DSP P7 Fix Tasklist

Last updated: 2026-02-22  
Root: `/Users/grzzi/Desktop/dnb_bass_synth`

## 1. Mandatory Inputs
1. `docs/qa/p7_fix_review.md`
2. `docs/master_implementation_plan.md`
3. `docs/project_rules.md`
4. `docs/agent_briefs/backend_dsp_agent_brief.md`
5. `docs/qa/backend_phase_handoffs/P7_qa_handoff.md`
6. `tests/render/test_aliasing.cpp`
7. `tests/render/test_qa_scenarios.cpp`
8. `bench/bench_voice_cpu.cpp`
9. `bench/bench_oversampling.cpp`
10. `bench/bench_macro_updates.cpp`
11. `docs/qa/knowledge_extract/supplement_fresh.txt`
12. `docs/qa/knowledge_extract/techstack_fresh.txt`

## 2. Fix Scope
### 2.1 Close `F-P7R-003`
1. Replace/add aliasing assertions with measurable spectral/foldback-oriented metric.
2. Ensure test comment/name/threshold align with actual measurement.
3. Keep test deterministic and CI-stable.

### 2.2 Close `F-P7R-004`
1. Re-run benches with explicit reproducible commands.
2. Re-run full `ctest` and report exact total test count.
3. Update backend P7 handoff with exact evidence, not rounded placeholders.

## 3. Verification
1. `tools/scripts/init_submodules.sh`
2. `cmake --build build --parallel`
3. `cd build && ctest --output-on-failure`
4. Bench commands (with explicit time suffix), e.g.:
   - `./bench/bench_voice_cpu --benchmark_min_time=0.05s --benchmark_repetitions=1`
   - `./bench/bench_oversampling --benchmark_min_time=0.05s --benchmark_repetitions=1`
   - `./bench/bench_macro_updates --benchmark_min_time=0.05s --benchmark_repetitions=1`

## 4. Required Output
Create fix handoff:
- `docs/qa/backend_phase_handoffs/P7_qa_handoff_fix.md`

Handoff must include:
1. changed files
2. closure map for `F-P7R-003`, `F-P7R-004`
3. exact commands + outputs summary
4. exact test count and pass status
5. benchmark context (Debug/Release)
6. proposed status: `Review`
