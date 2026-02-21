# Backend/DSP Alignment Fix Tasklist (F-ALIGN-001)

Last updated: 2026-02-21  
Root: `/Users/grzzi/Desktop/dnb_bass_synth`

## 1. Obavezno prije pocetka
1. Procitaj:
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/qa/alignment_remediation_review.md`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/ALIGN_D001_handoff.md`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/master_implementation_plan.md`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/project_rules.md`
   - `/Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB Bass Synth VST Plugin Research.pdf`
   - `/Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB bass synth document for developer.pdf`
   - `/Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx`
   - `/Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx`
2. Potvrdi da radis samo unutar root foldera.
3. Ovaj paket zatvara samo nalaz `F-ALIGN-001`.

## 2. Scope i cilj
Cilj je zatvoriti RT-safety odstupanje u oversampleru:
- nema runtime alokacija u audio processing pathu
- zadrzan per-module oversampling intent i postojeca P3 funkcionalnost
- deterministic fallback kad block premasi `prepare(...)` kapacitet

## 3. Obavezni taskovi (F-ALIGN-001)
1. `src/dsp/core/Oversampler.h`
   - Ukloni sve `resize` pozive iz `getUpBuffer(...)` i `processUp(...)`.
   - Zadrzi FIR/polyphase kvalitetu koja je vec uvedena u `ALIGN_D001`.
   - Kapacitet buffera i stanja mora biti pripremljen u `prepare(...)` i resetiran u `reset(...)`.
2. Overflow/no-allocation guard
   - Definiraj sto se dogada kad `numSamples * factor` prelazi pripremljeni kapacitet.
   - Implementacija mora ostati RT-safe: bez `malloc/new/resize`, bez lockova, bez throw.
   - Guard ponasanje dokumentiraj kratkim komentarom i testom.
3. Primjena po modulima:
   - Provjeri da nonlinear moduli koriste oversampling smisleno:
     - `src/dsp/dist/Saturator.h`
     - `src/dsp/dist/Wavefolder.h`
     - relevantni FM/character path iz P3
4. Kvaliteta i stabilnost:
   - Dodaj ili prosiri testove u `tests/dsp/test_oversampler.cpp`:
     - no-reallocation behavior za normalan block
     - overflow-guard behavior za prevelik block
     - anti-alias/anti-imaging sanity ostaje validan
   - Zadrzi postojece P1-P3 testove zelenima.

## 4. Zabranjeno
1. Nema rada izvan root foldera.
2. Nema bypassa `domain/ConstraintEngine`.
3. Nema scope creepa prema P4/P5.
4. Nema uvodenja neodobrenih dependencyja u ovom tasku.

## 5. Verifikacija
1. `cmake --build build --parallel`
2. `cd build && ctest --output-on-failure`
3. `cd build && ctest --output-on-failure -R Oversampler`
4. Compile smoke:
   - napravi kratki source koji ukljucuje `src/dsp/core/Oversampler.h`
   - kompiliraj sa `c++ -std=c++20 -I. ...`

## 6. Obavezni output
1. Handoff packet spremiti u:
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/ALIGN_D001_handoff_fix.md`
2. Handoff mora sadrzavati:
   - changed files (tocne putanje)
   - test komande + rezultat
   - closure map za `F-ALIGN-001`
   - poznata ogranicenja / otvorena pitanja
3. Predlozi status samo do `Review`.
