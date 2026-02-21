# Backend/DSP P5 Round-2 Fix Tasklist (Blocking Remediation)

Last updated: 2026-02-21  
Root: `/Users/grzzi/Desktop/dnb_bass_synth`

## 1. Obavezno prije pocetka
1. Procitaj:
   - `/Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB Bass Synth VST Plugin Research.pdf`
   - `/Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB bass synth document for developer.pdf`
   - `/Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx`
   - `/Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/project_rules.md`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/master_implementation_plan.md`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/spec/p1_schema_freeze.md`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/qa/p5_review.md`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/qa/p5_round2_review.md`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P5_handoff_fix.md`
2. Potvrdi da radis samo u rootu.
3. Ovaj fix paket zatvara findings: `F-P5R2-001`, `F-P5R2-002`, `F-P5R2-003`.

## 2. Scope i cilj
Cilj je prebaciti P5 iz `Review` u `Done` bez false-affordance APVTS parametara i bez contract drifta.

## 3. Obavezni taskovi
1. APVTS inventory i cleanup (`F-P5R2-001`)
   - Enumeriraj sve aktivne APVTS parametre iz `createParameterLayout()`.
   - Za svaki postavi status:
     - `wired` -> dokaziv runtime efekt kroz domain/engine path.
     - `deferred` -> ukloni iz aktivnog layouta i dokumentiraj defer.
   - Nema dead/no-op parametara ostavljenih u aktivnom P5 host contractu.
2. Canonical macro set (`F-P5R2-001`)
   - Odrzi 5 macro kontrola aktivnim:
     - `macro.neuro_formant`
     - `macro.fm_metal`
     - `macro.roller_dynamics`
     - `macro.liquid_depth`
     - `macro.style_morph`
   - `macro.roller_dynamics` mora imati realan runtime efekt (ne TODO/no-op).
3. Test evidence (`F-P5R2-002`)
   - Dodaj test za style-mode mapiranje (bounded i deterministic: Tech/Neuro/Dark).
   - Dodaj test za style morph output delta pod kontroliranim uvjetima.
   - Dodaj test da `macro.roller_dynamics` mijenja runtime rezultat.
   - Uvezi testove u `tests/CMakeLists.txt`.
4. Canonical naming (`F-P5R2-003`)
   - Standardiziraj UI-facing style naziv na `Neuro` (ne `Neurofunk`) u backend contract surface-u.

## 4. Zabranjeno
1. Nema rada izvan roota.
2. Nema bypassa `domain/ConstraintEngine`.
3. Nema uvodenja novih dependencyja.
4. Nema ulaska u P6/P7 scope.

## 5. Verifikacija (obavezno pokrenuti)
1. `tools/scripts/init_submodules.sh`
2. `cmake --build build --parallel`
3. `cd build && ctest --output-on-failure`
4. Potvrdi da APVTS inventory tablica nema `dead/no-op` stavke.

## 6. Obavezni output
1. Handoff packet spremiti u:
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P5_handoff_fix_round2.md`
2. Handoff mora sadrzavati:
   - Phase ID + predlozeni status transition (`Review -> Review`)
   - changed files (tocne putanje)
   - test komande + rezultat
   - closure map za `F-P5R2-001`, `F-P5R2-002`, `F-P5R2-003`
   - APVTS inventory: `param_id | wired/deferred | runtime_path`
   - otvorena pitanja / ogranicenja
3. Stop nakon predaje handoffa, bez prelaska na P6.
