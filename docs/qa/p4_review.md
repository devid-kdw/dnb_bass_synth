# P4 Review (Voice/Engine Orchestration)

Date: 2026-02-21  
Reviewer: Orchestrator

## Scope Reviewed
1. `docs/qa/backend_phase_handoffs/P4_handoff.md`
2. `docs/qa/frontend_phase_handoffs/P4_handoff.md`
3. `docs/qa/frontend_p4_integration_checklist.md`
4. `src/engine/NoteStack.h`
5. `src/engine/Voice.h`
6. `src/engine/VoiceManager.h`
7. `src/engine/SynthEngine.h`
8. `tests/engine/test_note_stack.cpp`
9. `tests/engine/test_voice_allocator.cpp`
10. `tests/CMakeLists.txt`

## Validation Executed
1. `cmake --build build --parallel` -> PASS
2. `cd build && ctest --output-on-failure` -> PASS (`19/19`)
3. Large-block smoke:
   - `Voice::prepare(..., 2048)` + `Voice::processBlock(..., 2048)`  
   - observed `tail_abs=0` for samples `1024..2047` (indicates hard truncation)

## Findings (ordered by severity)

### F-P4-001 (High): RT-safety risk in `NoteStack` push path due possible reallocation
Files:
1. `src/engine/NoteStack.h:35`
2. `src/engine/NoteStack.h:38`

Issue:
1. `pushNote()` does `insert(begin, ...)` before applying the size cap (`pop_back()`).
2. When stack is already at capacity (`16`), temporary growth to `17` can trigger `std::vector` reallocation in audio-thread MIDI path.

Impact:
1. Violates strict RT-safe no-allocation policy.
2. Can introduce unpredictable latency spikes under dense/held-note scenarios.

Required fix:
1. Use fixed-capacity structure or enforce capacity before insertion so no growth/allocation can occur in real-time path.
2. Add explicit test/guard for max-capacity note bursts.

### F-P4-002 (High): Voice processing hard-truncates blocks >1024 samples
Files:
1. `src/engine/Voice.h:75`
2. `src/engine/Voice.h:76`
3. `src/engine/Voice.h:110`

Issue:
1. `Voice::processBlock()` uses fixed local buffer `float charBuffer[1024]`.
2. Any host block larger than `1024` is clamped, and the remainder is forced to zero.

Impact:
1. Audio dropouts/silence in tail of large host blocks.
2. Breaks correctness for hosts/buffer settings above `1024`.

Required fix:
1. Replace fixed local buffer with preallocated voice-owned buffer sized in `prepare(maxBlockSize)`.
2. Process full `numSamples` up to prepared max, without forced silence tail.
3. Add regression test for block size `>1024`.

### F-P4-003 (Medium): P4 requirement gap - style morph integration not implemented in engine path
References:
1. `docs/master_implementation_plan.md:118`
2. `src/engine/SynthEngine.h:25`
3. `src/engine/SynthEngine.h:35`

Issue:
1. P4 plan requires style-mode morph handling at engine-level flow.
2. Current `SynthEngine` only routes note on/off and audio mixing; no style-morph state/input/progress handling is present.

Impact:
1. Backend contract expected by frontend P4 checklist (`style morph progress`) is not yet realizable.
2. Risk of unstable API/contracts in P5 wiring.

Required fix:
1. Add explicit engine-level style morph state surface/contract (or document deferred scope with approved ADR/note).
2. Provide deterministic update path and test coverage for morph progression behavior.

### F-P4-004 (Low): Handoff test command does not actually select discovered engine tests
File:
1. `docs/qa/backend_phase_handoffs/P4_handoff.md:17`

Issue:
1. Command `ctest -R engine_tests` returns no tests because Catch2 discovered test names are case-level names, not executable target name.

Impact:
1. Reported verification command is misleading.

Required fix:
1. Update handoff verification command to either full `ctest --output-on-failure` or a valid regex that matches discovered test names.

## Decision
Overall status: **Review (changes accepted as partial)**.

P5 gate decision: **NO-GO** until `F-P4-001` and `F-P4-002` are fixed, and `F-P4-003` is resolved or explicitly approved as deferred.
