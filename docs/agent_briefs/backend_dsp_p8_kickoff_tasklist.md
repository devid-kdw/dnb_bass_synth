# Backend DSP P8 Kickoff Tasklist

Last updated: 2026-02-22  
Root: `/Users/grzzi/Desktop/dnb_bass_synth`

## 1. Mandatory Inputs
1. `docs/qa/p7_post_gate_daw_hotfix_review.md`
2. `docs/qa/p7_final_gate_review.md`
3. `docs/master_implementation_plan.md`
4. `docs/implementation_plan.md`
5. `docs/project_rules.md`
6. `docs/agent_briefs/backend_dsp_agent_brief.md`
7. `docs/agent_briefs/backend_dsp_phase_tasklist.md`
8. `.github/workflows/ci.yml`
9. `.github/workflows/release.yml`
10. `CMakeLists.txt`
11. `tests/CMakeLists.txt`
12. `bench/CMakeLists.txt`
13. `tools/scripts/init_submodules.sh`
14. `knowledge/DNB Bass Synth VST Plugin Research.pdf`
15. `knowledge/DNB bass synth document for developer.pdf`
16. `knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx`
17. `knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx`

## 2. P8 Backend Scope (Support)

### 2.1 CI backend matrix hardening
1. Ensure CI runs deterministic backend quality gates:
   - configure
   - build
   - `ctest --output-on-failure`
2. Ensure backend test binaries are covered:
   - `domain_tests`
   - `engine_tests`
   - `dsp_tests`
   - `render_tests`
   - `preset_tests`

### 2.2 Bench and performance evidence policy
1. Keep benchmark execution reproducible in CI context.
2. If benchmark runs are debug-instrumented, keep them non-blocking evidence jobs (no false gate failures).
3. Document exact CLI and context (Debug/Release).

### 2.3 Release hardening support
1. Ensure release workflow does not skip core backend tests.
2. Ensure release artifact step includes checksum evidence for produced binaries.
3. Do not change DSP behavior outside P8 CI/release scope.

## 3. Constraints
1. No work outside `/Users/grzzi/Desktop/dnb_bass_synth`.
2. No new dependencies.
3. No bypass of `domain/ConstraintEngine`.
4. No P9 scope creep.

## 4. Verification
1. `tools/scripts/init_submodules.sh`
2. `cmake --build build --parallel`
3. `cd build && ctest --output-on-failure`
4. If bench jobs are touched:
   - `cd build && ./bench/bench_voice_cpu --benchmark_min_time=0.05s --benchmark_repetitions=1`
   - `cd build && ./bench/bench_oversampling --benchmark_min_time=0.05s --benchmark_repetitions=1`
   - `cd build && ./bench/bench_macro_updates --benchmark_min_time=0.05s --benchmark_repetitions=1`

## 5. Required Output
Create handoff:
- `docs/qa/backend_phase_handoffs/P8_handoff.md`

Handoff must include:
1. changed files
2. closure map for backend P8 scope
3. exact CI/backend commands and results
4. measurement context (Debug/Release)
5. known limitations/open questions
6. proposed status: `Review`
