# Backend P1 Review Report (Domain Constraint Core)

Date: 2026-02-21  
Reviewer: Orchestrator

## 1. Scope Reviewed
Reviewed artifacts delivered by backend agent for P1:
- `docs/qa/backend_phase_handoffs/P1_handoff.md`
- `src/domain/ConstraintEngine.h`
- `src/domain/ConstraintEngine.cpp`
- `src/domain/DnBLimits.h`
- `src/domain/StyleMode.h`
- `src/domain/MacroMap.h`
- `src/domain/ParameterSpec.h`
- `tests/CMakeLists.txt`
- `tests/unit/test_parameter_ranges.cpp`
- `tests/unit/test_macro_constraints.cpp`
- `tests/unit/test_style_modes.cpp`
- `tools/extract_pdf.py`

## 2. Validation Executed
Command:
```bash
cmake --build build --parallel
cd build && ctest --output-on-failure
```

Result:
- 5/5 tests passed
- No immediate build/test breakage detected

## 3. Change Summary
P1 introduces first functional `domain/ConstraintEngine` path with:
1. core domain constraints (attack/release, crossover, fixed sub phase)
2. style modifiers and macro mappings
3. FM ratio snapping to curated set
4. initial unit tests for ranges, macro behavior, and style gating

## 4. Findings

### F-001 (Medium): MVP style set drift
`src/domain/StyleMode.h` includes `Liquid`, `JumpUp`, `Darkstep` in active enum set, while MVP definition in current project docs emphasizes 3 style modes (Tech/Neuro/Dark). This can create scope ambiguity in downstream UI and test mapping.

Recommendation:
- Either constrain active MVP set to Tech/Neuro/Dark, or explicitly mark extra modes as V2/V3-gated with feature flag.

### F-002 (Medium): FM ratio set misaligned with curated spec examples
`src/domain/DnBLimits.h` includes values like `2.718`, `3.141`, `4.23`, `5.0` while knowledge docs repeatedly emphasize curated DnB-focused inharmonic anchors (e.g. `1.41`, `0.7 (7:10)`, `8:23`, and references to `3.15`).

Recommendation:
- Align `allowedFMRatios` with documented curated set and version it in domain config/spec.

### F-003 (Low): `macroRollerDyn` is currently not wired in `ConstraintEngine`
`RawInputParams` exposes `macroRollerDyn`, `MacroMap` defines `applyRollerDyn`, but `ConstraintEngine::process` does not use it.

Recommendation:
- Either wire it now to a constrained target path, or remove from P1 and defer formally to later phase.

### F-004 (Low): mixed unit semantics in `RawInputParams` comment
`RawInputParams` comment says normalized 0..1 UI input, while `ampAttack`/`ampRelease` fields are represented in milliseconds by defaults.

Recommendation:
- Clarify whether this struct is normalized UI space or resolved UI units before domain clamp.

### F-005 (Low/Policy): test dependency strategy diverges from current stack direction
`tests/CMakeLists.txt` uses `FetchContent` for Catch2. Current architecture docs prefer controlled dependency strategy via `extern/` + submodules.

Recommendation:
- Keep one strategy consistently project-wide; if switching, log ADR note.

## 5. Review Decision
P1 status: **Review (not accepted as Done yet)**

Reason:
- foundation is solid and tests pass, but there are spec-alignment drifts that should be closed before promoting P1 to Done.

## 6. Required Follow-ups
1. Resolve F-001 and F-002 (spec alignment blockers)
2. Resolve or explicitly defer F-003
3. Clarify F-004 and dependency policy for F-005
4. Submit updated handoff for re-review
