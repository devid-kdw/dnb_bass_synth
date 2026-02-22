# Backend/DSP P6 Kickoff Prompt (Copy/Paste)

```text
TI SI BACKEND/DSP AGENT ZA DnB Bass Synth VST3.

RADNI ROOT:
/Users/grzzi/Desktop/dnb_bass_synth

TASK: P6 implementacija Preset/State/Migration sloja (prva P6 isporuka).

OBAVEZNO PROCI TAJ REDOSLIJED DOKUMENATA:
1) /Users/grzzi/Desktop/dnb_bass_synth/docs/master_implementation_plan.md
2) /Users/grzzi/Desktop/dnb_bass_synth/docs/implementation_plan.md
3) /Users/grzzi/Desktop/dnb_bass_synth/docs/project_rules.md
4) /Users/grzzi/Desktop/dnb_bass_synth/docs/spec/p1_schema_freeze.md
5) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/backend_dsp_agent_brief.md
6) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/backend_dsp_phase_tasklist.md
7) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/p5_round3_review.md
8) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P5_handoff_fix_round3.md
9) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/frontend_phase_handoffs/P5_handoff_fix_round3.md
10) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB Bass Synth VST Plugin Research.pdf
11) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB bass synth document for developer.pdf
12) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx
13) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx

OBAVEZNE AKCIJE U P6:
1) Implementiraj preset/state jezgru:
   - `src/preset/PresetSchema.*`
   - `src/preset/PresetMigration.*`
   - `src/preset/PresetManager.*`
2) Definiraj verzionirani state contract:
   - schema version u state payloadu
   - stabilni canonical `param_id` kljucevi (bez rename/remove drift-a)
   - graceful unknown-field handling (bez crasha i bez nekontroliranog fallbacka)
3) Uvezi preset/state sloj u app:
   - wire `getStateInformation()` i `setStateInformation()` kroz `PresetManager`
   - osiguraj deterministic roundtrip save/load ponasanje
4) Odrzi architecture i safety pravila:
   - nema bypassa `domain/ConstraintEngine`
   - nema RT-unsafe operacija u audio threadu
5) Dodaj test pokrivenost za P6:
   - save/load roundtrip
   - migration iz legacy schema fixture-a
   - unknown field tolerance
   - invalid/corrupt state fallback ponašanje

OGRANICENJA:
- Ne radi izvan root foldera.
- Ne uvodi nove dependencyje.
- Ne mijenjaj P7 scope (bench/render QA gate).
- Ne mijenjaj aktivne P5 APVTS ID-jeve bez ADR prijedloga.

OBAVEZNA VERIFIKACIJA:
1) tools/scripts/init_submodules.sh
2) cmake --build build --parallel
3) cd build && ctest --output-on-failure
4) Dodatno u handoffu navedi migration matricu:
   - `from_version -> to_version -> rezultat`

OBAVEZNI OUTPUT:
1) Handoff packet u:
   /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P6_handoff.md
2) U handoffu navedi:
   - changed files
   - test komande + rezultat
   - state contract tabelu (`param_id | persisted | notes`)
   - migration matricu i closure map za P6 zahtjeve
   - otvorena pitanja / rizike (ako postoje)
3) Predlozi status samo do `Review` (ne `Done`).
```
