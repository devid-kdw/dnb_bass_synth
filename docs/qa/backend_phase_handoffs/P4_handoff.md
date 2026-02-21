# Handoff Packet: Phase 4 (P4)

**Phase ID**: P4 - Voice/Engine Orchestration
**Owner**: Backend/DSP
**Status Transition**: In Progress -> Review

## 1. Changed/Added Files
**Engine State:**
- `src/engine/NoteStack.h` (MIDI LIFO Stack & Legato Tracking)
- `src/engine/Voice.h` (DSP Bundle encapsulation & Amplitude Env)
- `src/engine/VoiceManager.h` (Strict Mono & Paraphonic Glide control)
- `src/engine/SynthEngine.h` (Top-level DSP loop and MIDI router)
  
**Tests:**
- `tests/engine/test_note_stack.cpp`
- `tests/engine/test_voice_allocator.cpp`
- `tests/CMakeLists.txt`

## 2. Test Commands & Results
**Command**:
```bash
cmake --build build --parallel
cd build && ctest -R engine_tests --output-on-failure -V
```

**Result**:
`All tests passed (19 assertions in 2 test cases)`

Smoke checks (`c++ -std=c++20 -I. /tmp/synth_engine_smoke.cpp`) verify that the top-level `SynthEngine.h` instantiates properly without internal compile violations in its tree.

## 3. Known Limitations / Open Risks
- Amplitude Envelope is currently a static 5ms attack / 15ms release linear ramp. This is strictly to satisfy Phase 4 rules for click-free testing, but a fully functional interactive ADSR will be mapped via domain constraints once Phase 5 connects macro styles.
- Routing through Crossover limits Sub to a dedicated, unmodulated path, while the Character path runs the Saturator. True parallel or serial modularity is fixed per the DnB constraints spec.

## 4. RT Compliance Evidence
`subBuffer` and `charBuffer` in `SynthEngine` are aggressively pre-allocated in `prepare()` up to `maxBlockSize`. Clamping prevents boundary violation. NoteStack `std::vector` capacity strictly reserved early, avoiding runtime `resize()`.

Ready for Orchestrator Review.
