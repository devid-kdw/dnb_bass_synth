# P3 Review Report (Backend + Frontend)

Date: 2026-02-21  
Reviewer: Orchestrator

## 1. Scope Reviewed
Backend P3 handoff:
- `docs/qa/backend_phase_handoffs/P3_handoff.md`
- `src/dsp/osc/SubOscillator.h`
- `src/dsp/osc/CharacterOscillator.h`
- `src/dsp/filters/StateVariableFilter.h`
- `src/dsp/filters/CrossoverLR4.h`
- `src/dsp/dist/Saturator.h`
- `src/dsp/dist/Wavefolder.h`
- `tests/dsp/test_sub_phase_lock.cpp`
- `tests/dsp/test_character_osc.cpp`
- `tests/dsp/test_crossover_lr4.cpp`
- `tests/CMakeLists.txt`

Frontend P3 handoff:
- `docs/qa/frontend_phase_handoffs/P3_handoff.md`
- `docs/qa/frontend_p3_ux_feedback.md`
- `src/ui/components/VisualFeedbackPlaceholder.h`
- `src/ui/layout/MainLayoutScaffold.h`

## 2. Validation Executed
### 2.1 Existing test suite
```bash
cmake --build build --parallel
cd build && ctest --output-on-failure
```
Result:
- `100% tests passed, 0 tests failed out of 14`

### 2.2 Additional P3 module compile smoke check
```bash
c++ -std=c++20 -I. /tmp/p3_header_smoke.cpp -o /tmp/p3_header_smoke
```
`/tmp/p3_header_smoke.cpp` includes:
- `src/dsp/osc/SubOscillator.h`
- `src/dsp/osc/CharacterOscillator.h`
- `src/dsp/filters/StateVariableFilter.h`
- `src/dsp/filters/CrossoverLR4.h`
- `src/dsp/dist/Saturator.h`
- `src/dsp/dist/Wavefolder.h`

Result:
- compile fails due unresolved include paths in newly added P3 headers.

## 3. Findings (ordered by severity)

### F-P3-001 (High): P3 DSP modules fail standalone compile due invalid include paths
Files:
- `src/dsp/filters/StateVariableFilter.h:3`
- `src/dsp/dist/Saturator.h:3`
- `src/dsp/dist/Saturator.h:4`
- `src/dsp/dist/Saturator.h:5`
- `src/dsp/dist/Wavefolder.h:3`
- `src/dsp/dist/Wavefolder.h:4`

Issue:
- headers use paths like `../../src/dsp/core/...` which do not resolve correctly from those directories.
- current test bundle does not include these modules, so failure is masked.

Impact:
- P3 integration into engine/app layers will break as soon as these modules are included.

Required fix:
1. Replace broken includes with valid project-relative includes from current directories (for example `../core/...` from `src/dsp/dist` and `src/dsp/filters`).
2. Add compile coverage for `StateVariableFilter`, `Saturator`, and `Wavefolder` (tests or dedicated compile smoke target under CMake).

### F-P3-002 (High): `CrossoverLR4` high-pass denominator coefficients are never assigned
File:
- `src/dsp/filters/CrossoverLR4.h:79`
- `src/dsp/filters/CrossoverLR4.h:87`
- `src/dsp/filters/CrossoverLR4.h:103`
- `src/dsp/filters/CrossoverLR4.h:104`

Issue:
- processing uses `c_a1_hp` and `c_a2_hp`, but `setFrequency` does not assign them.
- they remain zero-initialized, so high-pass path is not the intended IIR biquad topology.

Impact:
- crossover slope/phase behavior can deviate from LR4 target and violate sub/character split intent.

Required fix:
1. Assign HP denominator coefficients consistently with the designed biquad formulation.
2. Add frequency-response style test assertions (not only impulse integral sum) for LP/HP behavior around crossover.

### F-P3-003 (Medium): P3 tests do not cover newly added nonlinear/filter modules
Files:
- `tests/CMakeLists.txt:25`

Issue:
- P3 added `StateVariableFilter`, `Saturator`, `Wavefolder`, but test target only adds:
  - `test_sub_phase_lock.cpp`
  - `test_character_osc.cpp`
  - `test_crossover_lr4.cpp`

Impact:
- compile/runtime regressions in three key P3 modules are currently invisible to CI/test run.

Required fix:
1. Add tests for those modules (at minimum include/construct/process sanity checks).
2. Keep module-level compile coverage mandatory for future phases.

## 4. Frontend P3 Assessment
Frontend P3 support track is acceptable:
- scaffold update and visual placeholder are in scope
- no UI-to-DSP/domain bypass introduced
- UX feedback doc is useful input for P4/P5 integration planning

No blocking frontend finding in P3.

## 5. Decision
Overall P3 status: **Review (not accepted as Done yet)**.

Reason:
- backend contains blocking compile/integration defects (`F-P3-001`, `F-P3-002`) and test-coverage gap (`F-P3-003`).

## 6. Required Follow-ups
1. Backend submits P3 fix patch for include path correctness and crossover denominator assignment.
2. Add test/compile coverage for all newly introduced P3 modules.
3. Re-run build + tests + P3 compile smoke check.
4. Orchestrator re-reviews and then decides on `P3 -> Done`.
