# Backend/DSP P5 Fix Tasklist (Blocking Remediation)

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
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/backend_dsp_agent_brief.md`
2. Potvrdi da radis samo u rootu.
3. Ovaj fix paket zatvara findings: `F-P5-001`, `F-P5-002`, `F-P5-003`, `F-P5-004`.

## 2. Scope i cilj
Cilj je prebaciti P5 iz `Review` u `Done` zatvaranjem contract/wiring gapova bez scope creepa prema P6.

## 3. Obavezni taskovi
1. `F-P5-001` style.mode contract wiring
   - Uvedi canonical `style.mode` param (Tech/Neuro/Dark) u aktivni APVTS layout.
   - Dodaj RT-safe cache pointer i mapiranje u `RawInputParams.activeStyle`.
   - Mapiranje mora biti deterministic i clampano na validan enum range.
2. `F-P5-002` style morph audio-path effect
   - Odrzi postojeci deterministic style morph state u engine-u.
   - Osiguraj da `macro.style_morph` ima mjerljiv runtime efekt na output path (ne samo state storage).
   - Ne smije doci do bypassa domain gate-a i ne smije se narusiti sub protection policy.
3. `F-P5-003` APVTS contract completeness
   - Napravi inventar svih exposed APVTS parametara u P5.
   - Za svaki parametar postavi status:
     - `wired`: stvarno utjece na runtime kroz domain-approved mapping, ili
     - `deferred`: nije aktivan u P5, uklonjen/oznacen uz dokumentiran razlog.
   - Nije dozvoljen tihi dead/no-op parametar bez dokumentiranog statusa.
4. `F-P5-004` handoff discipline
   - Predaj novi handoff u `docs/qa/backend_phase_handoffs/P5_handoff_fix.md`.
   - Ne koristiti `docs/agent_briefs/` kao izlaznu QA handoff putanju.

## 4. Zabranjeno
1. Nema rada izvan roota.
2. Nema bypassa `domain/ConstraintEngine`.
3. Nema uvodenja novih dependencyja.
4. Nema ulaska u P6/P7 feature scope.

## 5. Verifikacija (obavezno pokrenuti)
1. `tools/scripts/init_submodules.sh`
2. `cmake --build build --parallel`
3. `cd build && ctest --output-on-failure`
4. Dodaj i pokreni testove koji pokrivaju:
   - style mode mapiranje (`style.mode`) i utjecaj na constraint behavior
   - style morph runtime utjecaj na audio output uz isti MIDI ulaz
5. Ako uvedes nove test fajlove, ukljuci ih u `tests/CMakeLists.txt`.

## 6. Obavezni output
1. Handoff packet spremiti u:
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P5_handoff_fix.md`
2. Handoff mora sadrzavati:
   - Phase ID + predlozeni status transition (`Review -> Review`)
   - changed files (tocne putanje)
   - test komande + rezultat
   - closure map za `F-P5-001`, `F-P5-002`, `F-P5-003`, `F-P5-004`
   - APVTS param inventory tabelu (`param_id`, `wired/deferred`, `path`)
   - otvorena pitanja / ogranicenja
3. Stop nakon predaje handoffa, bez prelaska na P6.
