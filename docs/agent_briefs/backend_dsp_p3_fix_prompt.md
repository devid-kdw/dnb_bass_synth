# Backend/DSP P3 Fix Prompt (Copy/Paste)

```text
TI SI BACKEND/DSP AGENT ZA DnB Bass Synth VST3.

RADNI ROOT:
/Users/grzzi/Desktop/dnb_bass_synth

TASK: P3 remediation patch-set za zatvaranje review findings (`F-P3-001`, `F-P3-002`, `F-P3-003`).

OBAVEZNO PROCI TAJ REDOSLIJED DOKUMENATA:
1) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/p3_review.md
2) /Users/grzzi/Desktop/dnb_bass_synth/docs/master_implementation_plan.md
3) /Users/grzzi/Desktop/dnb_bass_synth/docs/project_rules.md
4) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/backend_dsp_agent_brief.md
5) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/backend_dsp_phase_tasklist.md
6) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P3_handoff.md
7) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/frontend_p3_ux_feedback.md
8) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB Bass Synth VST Plugin Research.pdf
9) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB bass synth document for developer.pdf
10) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx
11) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx

OBAVEZNE IZMJENE U P3:
1) Zatvori `F-P3-001` (compile blocker include path):
   - Ispravi include putanje u:
     - `src/dsp/filters/StateVariableFilter.h`
     - `src/dsp/dist/Saturator.h`
     - `src/dsp/dist/Wavefolder.h`
   - Includeovi moraju biti validni iz stvarne lokacije tih headera (bez `../../src/...` greske).
2) Zatvori `F-P3-002` (crossover correctness):
   - U `src/dsp/filters/CrossoverLR4.h` dodijeli HP denominator koeficijente koji se koriste u procesu (`c_a1_hp`, `c_a2_hp`).
   - Odrzi LR4 split intent i sub/character sigurnost.
3) Zatvori `F-P3-003` (coverage gap):
   - Dodaj test coverage za:
     - `src/dsp/filters/StateVariableFilter.h`
     - `src/dsp/dist/Saturator.h`
     - `src/dsp/dist/Wavefolder.h`
   - Uvezi testove kroz `tests/CMakeLists.txt` tako da ulaze u `ctest`.
4) Ne uvoditi scope creep prema P4/P5.

OGRANICENJA:
- Ne radi izvan root foldera.
- Ne uvodi nove dependencyje.
- Ne bypassaj domain/ConstraintEngine granicu.
- Ne prelazi na P4.

OBAVEZNA VERIFIKACIJA:
1) cmake --build build --parallel
2) cd build && ctest --output-on-failure
3) P3 compile smoke check:
   - napravi mali source koji ukljucuje:
     - `src/dsp/osc/SubOscillator.h`
     - `src/dsp/osc/CharacterOscillator.h`
     - `src/dsp/filters/StateVariableFilter.h`
     - `src/dsp/filters/CrossoverLR4.h`
     - `src/dsp/dist/Saturator.h`
     - `src/dsp/dist/Wavefolder.h`
   - kompiliraj sa `c++ -std=c++20 -I. ...`
   - compile mora proci bez greske.

OBAVEZNI OUTPUT:
1) Handoff packet u:
   /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P3_handoff_fix.md
2) U handoffu navedi:
   - changed files
   - test komande + rezultat
   - closure map za `F-P3-001`, `F-P3-002`, `F-P3-003`
   - otvorena pitanja (ako postoje)
3) Predlozi status samo do `Review` (ne `Done`).
```
