# P5 Round-3 Remediation Fix Handoff (Backend/DSP)

Date: 2026-02-21  
Phase ID: P5 Round-3 Backend Remediation  
Owner: Backend/DSP Agent  
Status Transition Proposal: `Review -> Review`

## 1. Scope
Round-3 remediation packet to close final findings:
- `F-P5R3-001` APVTS no-op exposure
- `F-P5R3-002` `macro.roller_dynamics` audio-path evidence
- `F-P5R3-003` handoff integrity (evidence-backed wired claims only)

## 2. Changed Files
- `src/app/PluginProcessor.cpp`
- `src/app/PluginProcessor.h`
- `src/engine/Voice.h`
- `tests/CMakeLists.txt`
- `tests/engine/test_p5_round3.cpp` (new)

## 3. Verification Commands + Results
1. `tools/scripts/init_submodules.sh` -> passed
2. `cmake --build build --parallel` -> passed
3. `cd build && ctest --output-on-failure` -> passed (`29/29`)

## 4. Closure Map

### `F-P5R3-001` - APVTS no-op exposure (Closed)
Resolution:
- Active APVTS layout reduced to evidence-backed wired parameters only in `createParameterLayout()`.
- Deferred/no-op candidates were removed from active P5 host contract (`sub.shape`, `sub.phase`, `sys.xover`, `osc.fm.ratio`, `fx.ott.mix`).
- Active APVTS now has no dead/no-op host-facing parameters.

Primary code evidence:
- Active layout: `src/app/PluginProcessor.cpp:166`
- Parameter ingestion path: `src/app/PluginProcessor.cpp:53`
- Domain mapping: `src/domain/ConstraintEngine.cpp:5`
- Runtime DSP consumption: `src/engine/Voice.h:69`

### `F-P5R3-002` - `macro.roller_dynamics` audio evidence (Closed)
Resolution:
- `macro.roller_dynamics` drives `ResolvedParams.filterCutoff` in domain.
- `filterCutoff` is now applied in `Voice` SVF processing on rendered character path.
- Added deterministic audio-delta test under controlled conditions.

Primary code evidence:
- Domain mapping: `src/domain/ConstraintEngine.cpp:23`
- Audio-path application: `src/engine/Voice.h:78`, `src/engine/Voice.h:130`
- New test: `tests/engine/test_p5_round3.cpp:140`

### `F-P5R3-003` - Handoff integrity mismatch (Closed)
Resolution:
- This handoff lists only evidence-backed `wired` entries.
- Every `wired` claim below includes file+line code path and test evidence.

## 5. APVTS Inventory (`param_id | status | code_path | test_evidence`)

| param_id | status | code_path | test_evidence |
|---|---|---|---|
| `style.mode` | wired | `src/app/PluginProcessor.cpp:54`, `src/domain/ConstraintEngine.cpp:9`, `src/engine/Voice.h:72` | `tests/engine/test_p5_round3.cpp:69`, `tests/unit/test_style_modes.cpp:6` |
| `env.amp.att` | wired | `src/app/PluginProcessor.cpp:61`, `src/domain/ConstraintEngine.cpp:12`, `src/engine/Voice.h:96` | `tests/engine/test_p5_round3.cpp:84` |
| `env.amp.rel` | wired | `src/app/PluginProcessor.cpp:64`, `src/domain/ConstraintEngine.cpp:13`, `src/engine/Voice.h:97` | `tests/engine/test_p5_round3.cpp:84` |
| `macro.neuro_formant` | wired | `src/app/PluginProcessor.cpp:67`, `src/domain/ConstraintEngine.cpp:19`, `src/engine/Voice.h:75` | `tests/engine/test_p5_round3.cpp:111`, `tests/unit/test_macro_constraints.cpp:11` |
| `macro.fm_metal` | wired | `src/app/PluginProcessor.cpp:70`, `src/domain/ConstraintEngine.cpp:20`, `src/engine/Voice.h:72` | `tests/engine/test_p5_round3.cpp:125`, `tests/unit/test_style_modes.cpp:11` |
| `macro.roller_dynamics` | wired | `src/app/PluginProcessor.cpp:73`, `src/domain/ConstraintEngine.cpp:23`, `src/engine/Voice.h:78` | `tests/engine/test_p5_round3.cpp:140`, `tests/unit/test_p5_round2.cpp:26` |
| `macro.liquid_depth` | wired | `src/app/PluginProcessor.cpp:76`, `src/domain/ConstraintEngine.cpp:21`, `src/engine/Voice.h:75` | `tests/engine/test_p5_round3.cpp:155`, `tests/unit/test_macro_constraints.cpp:19` |
| `macro.style_morph` | wired | `src/app/PluginProcessor.cpp:79`, `src/engine/SynthEngine.h:93`, `src/engine/SynthEngine.h:74` | `tests/engine/test_regression.cpp:54` |
| `sub.shape` | deferred (removed) | removed from active layout in `src/app/PluginProcessor.cpp:166` | n/a (removed from host-facing P5 contract) |
| `sub.phase` | deferred (removed) | removed from active layout in `src/app/PluginProcessor.cpp:166` | n/a (removed from host-facing P5 contract) |
| `sys.xover` | deferred (removed) | removed from active layout in `src/app/PluginProcessor.cpp:166` | n/a (removed from host-facing P5 contract) |
| `osc.fm.ratio` | deferred (removed) | removed from active layout in `src/app/PluginProcessor.cpp:166` | n/a (removed from host-facing P5 contract) |
| `fx.ott.mix` | deferred (removed) | removed from active layout in `src/app/PluginProcessor.cpp:166` | n/a (removed from host-facing P5 contract) |

APVTS no-op confirmation:
- Active `createParameterLayout()` contract contains only `wired` parameters (8 entries).
- No active `dead/no-op` APVTS parameter remains host-facing.

## 6. Open Questions / Limitations
- None blocking for P5 Round-3 gate closure.
