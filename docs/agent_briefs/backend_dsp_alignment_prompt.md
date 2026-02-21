# Backend/DSP Alignment Fix Prompt (F-ALIGN-001) (Copy/Paste)

```text
TI SI BACKEND/DSP AGENT ZA DnB Bass Synth VST3.

RADNI ROOT:
/Users/grzzi/Desktop/dnb_bass_synth

TASK: P4-gate alignment remediation za zatvaranje nalaza `F-ALIGN-001`.

OBAVEZNO PROCI TAJ REDOSLIJED DOKUMENATA:
1) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/alignment_remediation_review.md
2) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/ALIGN_D001_handoff.md
3) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/backend_dsp_alignment_tasklist.md
4) /Users/grzzi/Desktop/dnb_bass_synth/docs/master_implementation_plan.md
5) /Users/grzzi/Desktop/dnb_bass_synth/docs/project_rules.md
6) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/backend_dsp_agent_brief.md
7) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx
8) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx
9) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB bass synth document for developer.pdf
10) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB Bass Synth VST Plugin Research.pdf

OBAVEZNE IZMJENE:
1) Zatvori `F-ALIGN-001` u `src/dsp/core/Oversampler.h`:
   - ukloni runtime alokacije iz audio processing patha:
     - `getUpBuffer(...)`
     - `processUp(...)`
   - sve memorijske alokacije moraju biti odradene u `prepare(...)`.
2) Uvedi deterministic no-allocation guard:
   - ako je trazeni block veci od pripremljenog kapaciteta, obradi ga bez `resize` i bez iznimki.
   - ponasanje mora biti jasno definirano i dokumentirano u kodu/testu (npr. clamp/truncate sa sigurnim izlazom).
3) Potvrdi da P3 nonlinear/character paths ostaju kompatibilni sa novim no-allocation oversampler kontraktom.
4) Dodaj/azuriraj test coverage:
   - test koji validira da processing pozivi ne triggeraju reallocation path.
   - test za overflow guard ponasanje (veci block od pripreme).
   - zadrzi sve postojece P1-P3 testove zelenima.

OGRANICENJA:
- Ne radi izvan root foldera.
- Ne uvodi neodobrene dependencyje.
- Ne bypassaj domain/ConstraintEngine.
- Ne ulazi u P4/P5 scope.

OBAVEZNA VERIFIKACIJA:
1) cmake --build build --parallel
2) cd build && ctest --output-on-failure
3) `ctest --output-on-failure -R Oversampler`
4) Kratki compile smoke koji ukljucuje `src/dsp/core/Oversampler.h`

OBAVEZNI OUTPUT:
1) Handoff packet u:
   /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/ALIGN_D001_handoff_fix.md
2) U handoffu navedi:
   - changed files
   - test komande + rezultat
   - closure map za `F-ALIGN-001`
   - otvorena pitanja (ako postoje)
3) Predlozi status samo do `Review`.
```
