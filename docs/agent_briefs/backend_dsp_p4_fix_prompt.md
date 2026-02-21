# Backend/DSP P4 Fix Prompt (Copy/Paste)

```text
TI SI BACKEND/DSP AGENT ZA DnB Bass Synth VST3.

RADNI ROOT:
/Users/grzzi/Desktop/dnb_bass_synth

TASK: P4 remediation patch-set za zatvaranje review findings (`F-P4-001`, `F-P4-002`, `F-P4-003`, `F-P4-004`).

OBAVEZNO PROCI TAJ REDOSLIJED DOKUMENATA:
1) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/p4_review.md
2) /Users/grzzi/Desktop/dnb_bass_synth/docs/master_implementation_plan.md
3) /Users/grzzi/Desktop/dnb_bass_synth/docs/project_rules.md
4) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/backend_dsp_agent_brief.md
5) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/backend_dsp_phase_tasklist.md
6) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/backend_dsp_p4_fix_tasklist.md
7) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P4_handoff.md
8) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/frontend_p4_integration_checklist.md
9) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB Bass Synth VST Plugin Research.pdf
10) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB bass synth document for developer.pdf
11) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx
12) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx

OBAVEZNE IZMJENE U P4:
1) Zatvori `F-P4-001` (RT-safe NoteStack):
   - U `src/engine/NoteStack.h` ukloni mogucnost runtime alokacije u push/pop pathu.
   - Nema privremenog rasta preko kapaciteta prije cap enforcementa.
   - Zadrzi LIFO/latest-note priority ponasanje.
2) Zatvori `F-P4-002` (voice block truncation):
   - U `src/engine/Voice.h` ukloni fiksni lokalni `charBuffer[1024]`.
   - Uvedi prealokiran voice-owned buffer u `prepare(maxBlockSize)` i obradi puni block do pripremljenog limita.
   - Nema hard silence tail bug-a za block >1024 (ako je `maxBlockSize` veci).
3) Zatvori `F-P4-003` (style morph engine path):
   - Uvedi minimalan, deterministic engine-level style morph state surface u `src/engine/SynthEngine.h`:
     - start/update/progress/read-only getter path
   - Nema UI/APVTS wiringa u ovom fixu, samo backend contract surface.
4) Zatvori `F-P4-004` (handoff verifikacija):
   - U novom handoffu koristi validne test komande (ne `ctest -R engine_tests` ako regex ne pogada discovered testove).

OGRANICENJA:
- Ne radi izvan root foldera.
- Ne uvodi nove dependencyje.
- Ne bypassaj domain/ConstraintEngine granicu.
- Ne ulazi u P5 implementaciju.

OBAVEZNA VERIFIKACIJA:
1) cmake --build build --parallel
2) cd build && ctest --output-on-failure
3) cd build && ctest --output-on-failure -R "NoteStack|VoiceManager"
4) Dodaj i pokreni regression test za block >1024 koji dokazuje da nema truncation/silence tail buga.
5) Kratki compile smoke:
   - source koji ukljucuje `src/engine/SynthEngine.h` + `src/engine/Voice.h`
   - kompilacija sa `c++ -std=c++20 -I. ...`

OBAVEZNI OUTPUT:
1) Handoff packet u:
   /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P4_handoff_fix.md
2) U handoffu navedi:
   - changed files
   - test komande + rezultat
   - closure map za `F-P4-001`, `F-P4-002`, `F-P4-003`, `F-P4-004`
   - otvorena pitanja (ako postoje)
3) Predlozi status samo do `Review` (ne `Done`).
```
