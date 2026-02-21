# Backend/DSP P2 Fix Tasklist (Blocking Remediation)

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
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/qa/p2_review.md`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/backend_dsp_agent_brief.md`
2. Potvrdi da radis samo u rootu.
3. Ovaj fix paket zatvara findings: `F-P2-001`, `F-P2-002`, `F-P2-003`.

## 2. Scope i cilj
Cilj je prebaciti P2 iz `Review` u `Done` zatvaranjem portability i coverage blokera bez scope creepa.

## 3. Obavezni taskovi
1. `F-P2-001` portability fix (`src/dsp/core/DenormalFlush.h`)
   - Uvesti arhitekturalni guard za x86/x64 intrinsics include.
   - Na nepodrzanim arhitekturama ostaviti siguran no-op fallback (RAII klasa mora ostati validna za instanciranje).
   - Ne uvoditi novi dependency.
2. `F-P2-002` coverage fix (test include + behavior)
   - Dodati novi DSP test koji ukljucuje:
     - `src/dsp/core/DenormalFlush.h`
     - `src/dsp/core/SanityCheck.h`
   - Testirati minimalno:
     - `ScopedDenormalFlush` instanciranje.
     - `ScopedDenormalFlush::flush` (subnormal -> 0, normalna vrijednost ostaje).
     - `SanityCheck::ensureSafe` za finite i NaN/Inf slucajeve.
   - Uvezati test u `tests/CMakeLists.txt`.
3. `F-P2-003` handoff disciplina
   - Novi handoff mora predlagati status samo do `Review` (ne `Done`).
   - Jasno mapirati closure po finding ID-u (`F-P2-001..003`).

## 4. Zabranjeno
1. Nema rada izvan roota.
2. Nema bypassa `domain/ConstraintEngine`.
3. Nema uvodenja neodobrenih dependencyja.
4. Nema prelaska na P3.

## 5. Verifikacija (obavezno pokrenuti)
1. `cmake --build build --parallel`
2. `cd build && ctest --output-on-failure`
3. Portability smoke compile:
   - generirati mali source koji ukljucuje `DenormalFlush.h` i `SanityCheck.h`
   - kompilirati ga sa `c++ -std=c++20 -I. ...`
   - rezultat mora biti uspjesan na trenutnoj arhitekturi

## 6. Obavezni output
1. Handoff packet spremiti u:
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P2_handoff_fix.md`
2. Handoff mora sadrzavati:
   - Phase ID + predlozeni status transition (`Review -> Review` ili `In Progress -> Review`)
   - changed files (tocne putanje)
   - test komande + rezultat
   - closure tablicu za `F-P2-001`, `F-P2-002`, `F-P2-003`
   - otvorena pitanja / ogranicenja
3. Stop nakon predaje handoffa, bez prelaska na P3.
