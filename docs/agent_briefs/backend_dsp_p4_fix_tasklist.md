# Backend/DSP P4 Fix Tasklist (Blocking Remediation)

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
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/qa/p4_review.md`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/backend_dsp_agent_brief.md`
2. Potvrdi da radis samo u rootu.
3. Ovaj fix paket zatvara findings: `F-P4-001`, `F-P4-002`, `F-P4-003`, `F-P4-004`.

## 2. Scope i cilj
Cilj je prebaciti P4 iz `Review` u `Done` zatvaranjem RT-safe i audio correctness blokera bez scope creepa prema P5.

## 3. Obavezni taskovi
1. `F-P4-001` RT-safe fix (`src/engine/NoteStack.h`)
   - Ukloni runtime allocation rizik u `pushNote`.
   - Nema privremenog prelaska preko kapaciteta koji moze okinuti reallocation.
   - Zadrzi behavior:
     - latest-note priority
     - retrigger istog note-a osvjezava velocity i prioritet
     - cap = 16
   - Dodaj test scenario burst note-on/off preko 16 noteova.
2. `F-P4-002` voice block correctness (`src/engine/Voice.h`)
   - Ukloni lokalni fiksni `charBuffer[1024]`.
   - Uvedi prealokiran buffer kao clan klase:
     - alociran samo u `prepare(maxBlockSize)`
     - bez alokacija u `processBlock`
   - Obradi puni block do pripremljenog limita.
   - Dodaj regression test za veliki block (npr. 2048) koji potvrduje da tail nije artefaktno silenced zbog internog limita 1024.
3. `F-P4-003` style morph requirement (`src/engine/SynthEngine.h`)
   - Dodaj minimalni style morph state machine/surface:
     - init/start morph
     - deterministic progress update po blocku
     - read-only getter(i) za progress/active stanje
   - Ne uvoditi UI binding/APVTS u ovom fixu.
   - Dodaj test koji validira progress monotonicnost i completion (0 -> 1).
4. `F-P4-004` handoff command correctness
   - U P4 fix handoffu navedi realne ctest komande koje stvarno pogadaju discovered testove.
   - Ako koristis regex, potvrdi da regex vraca stvarne test case-ove.

## 4. Zabranjeno
1. Nema rada izvan roota.
2. Nema bypassa `domain/ConstraintEngine`.
3. Nema uvodenja novih dependencyja.
4. Nema prelaska na P5 wiring/feature scope.

## 5. Verifikacija (obavezno pokrenuti)
1. `cmake --build build --parallel`
2. `cd build && ctest --output-on-failure`
3. `cd build && ctest --output-on-failure -R "NoteStack|VoiceManager"`
4. Pokreni test koji pokriva large block scenario (`>1024`) za voice path.
5. Compile smoke:
   - mali source sa include:
     - `src/engine/SynthEngine.h`
     - `src/engine/Voice.h`
   - kompilacija: `c++ -std=c++20 -I. ...`

## 6. Obavezni output
1. Handoff packet spremiti u:
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P4_handoff_fix.md`
2. Handoff mora sadrzavati:
   - Phase ID + predlozeni status transition (`Review -> Review` ili `In Progress -> Review`)
   - changed files (tocne putanje)
   - test komande + rezultat
   - closure map za `F-P4-001`, `F-P4-002`, `F-P4-003`, `F-P4-004`
   - otvorena pitanja / ogranicenja
3. Stop nakon predaje handoffa, bez prelaska na P5.
