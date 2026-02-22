# Backend/DSP Tasklist po Fazama

Last updated: 2026-02-22  
Root: `/Users/grzzi/Desktop/dnb_bass_synth`

## 1. Obavezno prije početka
1. Pročitaj:
   - `/Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB Bass Synth VST Plugin Research.pdf`
   - `/Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB bass synth document for developer.pdf`
   - `/Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx`
   - `/Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/project_rules.md`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/master_implementation_plan.md`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/backend_dsp_agent_brief.md`
2. Potvrdi da radiš isključivo unutar root foldera.
3. Provjeri u `docs/master_implementation_plan.md` koja je prva `Planned` faza.

## 2. P1 - Domain Constraint Core
Status: `Planned`  
Depends on: `P0 Done`

Taskovi:
1. Implementirati `ConstraintEngine`, `DnBLimits`, `StyleMode`, `MacroMap`, `ParameterSpec` u `src/domain/`.
2. Kodificirati hard constraints:
   - phase reset/sub lock policy
   - mono low-end pravila (xover zona 100-120 Hz)
   - release limit i FM ratio kurirani raspon
3. Dodati unit testove:
   - `tests/unit/test_parameter_ranges.cpp`
   - `tests/unit/test_macro_constraints.cpp`
   - `tests/unit/test_style_modes.cpp`

Output:
1. Domain sloj koji je jedini ulaz u DSP constraints.
2. Testovi prolaze za mapping/clamp/style logiku.

DoD:
1. Nema direct bypassa domain sloja prema DSP-u.
2. Svi traženi testovi prolaze.
3. Predan handoff packet.

## 3. P2 - DSP Core Primitives
Status: `Planned`  
Depends on: `P1 Done`

Taskovi:
1. Implementirati core primitive:
   - `src/dsp/core/Smoother.*`
   - `src/dsp/core/DCBlocker.*`
   - `src/dsp/core/Oversampler.*`
   - `src/dsp/core/DenormalFlush.*`
   - `src/dsp/core/SanityCheck.*`
2. Implementirati `src/dsp/safety/AntiClickRamp.*`.
3. Provjeriti RT-safe pravila (bez alloc/lock/io/log u audio threadu).

Output:
1. Stabilni RT-safe primitive blokovi za daljnje DSP module.
2. Test pokrivenost za sigurnosne primitive.

DoD:
1. Nema RT-safe kršenja u hot pathu.
2. Core/safety testovi prolaze.
3. Predan handoff packet.

## 4. P3 - Osc/Filter/Nonlinear DSP
Status: `Planned`  
Depends on: `P2 Done`

Taskovi:
1. Implementirati `src/dsp/osc/*` za Sub + Character putanje.
2. Implementirati `src/dsp/filters/*` (SVF/notch/formant/crossover temelji).
3. Implementirati `src/dsp/dist/*` (wavefold/dist/clip/autogain).
4. Primijeniti per-module oversampling na nelinearne module gdje je potreban.
5. Dodati/održati DSP testove:
   - `tests/dsp/test_sub_phase_lock.cpp`
   - `tests/dsp/test_anti_click.cpp`
   - `tests/dsp/test_crossover_lr4.cpp`
   - `tests/dsp/test_oversampler.cpp`

Output:
1. Funkcionalan Sub i Character DSP path.
2. Zaštita sub spektra i kontroliran aliasing u nelinearnim blokovima.

DoD:
1. Sub ostaje mono-stabilan i phase-safe.
2. DSP testovi prolaze.
3. CPU/aliasing baseline zabilježen u handoffu.

## 5. P4 - Voice/Engine Orchestration
Status: `Planned`  
Depends on: `P3 Done`

Taskovi:
1. Implementirati:
   - `src/engine/SynthEngine.*`
   - `src/engine/VoiceManager.*`
   - `src/engine/Voice.*`
   - `src/engine/NoteStack.*`
2. Implementirati deterministic legato/retrigger/steal ponašanje.
3. Integrirati style-mode morph path u engine flow.

Output:
1. Deterministički voice lifecycle.
2. Stabilan note handling bez click regresija.

DoD:
1. Voice ponašanje konzistentno kroz test scenarije.
2. Predan handoff packet.

## 6. P5 - App Wiring + Macro UI (Backend dio)
Status: `Planned`  
Depends on: `P1 Done`, `P4 Done`

Taskovi:
1. Backend dio app wiringa:
   - `src/app/PluginProcessor.*`
   - `src/app/ParameterLayout.*`
2. Zaključati stabilne parameter ID-jeve i schema contract.
3. Predati UI agentu backend contract za binding.

Output:
1. Stabilan processor/domain/engine/DSP tok.
2. Dokumentiran schema + ID contract za UI.

DoD:
1. UI može bindati bez bypassa domain sloja.
2. Predan handoff packet + contract note.

## 7. P6 - Preset/State/Migration
Status: `Planned`  
Depends on: `P5 Done`

Taskovi:
1. Implementirati:
   - `src/preset/PresetManager.*`
   - `src/preset/PresetSchema.*`
   - `src/preset/PresetMigration.*`
2. Održati compatibility strategiju:
   - version-tagged state
   - stable IDs
   - graceful unknown param handling
3. Dodati testove za save/load/migration.

Output:
1. Deterministički preset/state sustav.
2. Verzionirana migracija bez rušenja.

DoD:
1. Save/load testovi prolaze.
2. Migration scenariji pokriveni testovima.
3. Predan handoff packet.

## 8. P6.1 - Macro-10 Expansion + P7 Gate Closure (Backend primary)
Status: `Planned`  
Depends on: `P6 Done`

Taskovi:
1. Implementirati 6 dodatnih makroa iz:
   - `docs/spec/macro_10_contract_proposal.md`
   - canonical ID-jevi:
     - `macro.sub_punch`
     - `macro.fm_pressure`
     - `macro.cutoff_motion`
     - `macro.fold_bite`
     - `macro.table_drift`
     - `macro.smash_glue`
2. Uskladiti domain + app + runtime putanju za svih 10 makroa bez host-visible dead/no-op parametara.
3. Dodati test pokrivenost za:
   - domain mapping
   - style clamp ponašanje (`Tech`, `Neuro`, `Dark`)
   - runtime effect evidence
4. Zatvoriti backend P6->P7 gate odstupanja:
   - `G-P6P7-002`
   - `G-P6P7-003`
   - `G-P6P7-004` (backend scope)
   - `G-P6P7-005` (backend scope: ADR update/supersede input)
5. Predati backend P6.1 handoff s closure mapom i test evidence.

Output:
1. Aktivan Macro-10 backend contract i runtime implementacija.
2. Backend dio gate backloga zatvoren dokazima.

DoD:
1. Svi novi macro parametri imaju stvarni runtime učinak.
2. Nema kršenja `domain/ConstraintEngine` granice.
3. Build/test verification prolazi i handoff je predan.

## 9. P7 - QA + Render + Bench
Status: `Planned`  
Depends on: `P6.1 Done`

Taskovi:
1. Proširiti testove u:
   - `tests/dsp/*`
   - `tests/render/*`
2. Dodati benchmarke:
   - `bench/bench_voice_cpu.cpp`
   - `bench/bench_oversampling.cpp`
   - `bench/bench_macro_updates.cpp`
3. Provesti scenario matrix iz knowledge docs:
   - anti-click
   - mono compatibility
   - aliasing sweep
   - long note stability
   - preset load stress

Output:
1. QA izvještaj i benchmark baseline.

DoD:
1. Obavezni scenariji pokriveni.
2. Rezultati dokumentirani za orchestration review.
3. Predan handoff packet.

## 10. P8 - CI/CD (Backend support)
Status: `Planned`  
Primary owner: Orchestrator  
Backend role: support
Detailed kickoff checklist: `docs/agent_briefs/backend_dsp_p8_kickoff_tasklist.md`

Taskovi:
1. Uskladiti backend test matrix za CI:
   - `domain_tests`
   - `engine_tests`
   - `dsp_tests`
   - `render_tests`
   - `preset_tests`
2. Dodati reproducibilne backend quality-gate komande u CI kontekst:
   - `cmake --build build --parallel`
   - `cd build && ctest --output-on-failure`
3. Uskladiti bench smoke policy za CI:
   - zadrzati bench komande kao non-blocking evidence job ako su debug buildovi
   - osigurati da bench job ne uvodi false-fail u MVP gate
4. Potvrditi da release-artefakt korak ne zaobilazi domain granice ni DSP safety testove.
5. Predati P8 backend handoff sa closure mapom i CI evidence summary.

DoD:
1. CI reproducira backend quality gates bez manualnog patchanja.
2. `ctest` matrix je deterministic i dokumentiran.
3. Predan handoff packet:
   - `docs/qa/backend_phase_handoffs/P8_handoff.md`

## 11. Handoff packet format (obavezno po fazi)
Za svaku završenu fazu backend agent mora predati:
1. Phase ID i status prijedlog (`In Progress -> Review`).
2. Točan popis promijenjenih datoteka.
3. Test command listu + rezultate.
4. Poznate limite / otvorena pitanja.
5. Potencijalni ADR prijedlog (ako je arhitektura mijenjana).

Preporučena lokacija:
- `docs/qa/backend_phase_handoffs/<PHASE_ID>_handoff.md`
