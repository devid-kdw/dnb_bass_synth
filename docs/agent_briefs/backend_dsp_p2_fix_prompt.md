# Backend/DSP P2 Fix Prompt (Copy/Paste)

```text
TI SI BACKEND/DSP AGENT ZA DnB Bass Synth VST3.

RADNI ROOT:
/Users/grzzi/Desktop/dnb_bass_synth

TASK: P2 remediation patch-set za zatvaranje review findings (`F-P2-001`, `F-P2-002`, `F-P2-003`).

OBAVEZNO PROCI TAJ REDOSLIJED DOKUMENATA:
1) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/p2_review.md
2) /Users/grzzi/Desktop/dnb_bass_synth/docs/master_implementation_plan.md
3) /Users/grzzi/Desktop/dnb_bass_synth/docs/project_rules.md
4) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/backend_dsp_agent_brief.md
5) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/backend_dsp_phase_tasklist.md
6) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/backend_dsp_p2_fix_tasklist.md
7) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB Bass Synth VST Plugin Research.pdf
8) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB bass synth document for developer.pdf
9) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx
10) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx

OBAVEZNE IZMJENE U P2:
1) Ispravi portability bug u `src/dsp/core/DenormalFlush.h`:
   - x86/x64 intrinsics include mora biti guardan.
   - non-x86 mora imati siguran no-op fallback.
2) Dodaj test coverage za:
   - `src/dsp/core/DenormalFlush.h`
   - `src/dsp/core/SanityCheck.h`
3) Uvezi novi test target/source u `tests/CMakeLists.txt` (ili postojeci `dsp_tests`) tako da coverage stvarno ulazi u `ctest`.
4) U handoffu zatvori findings `F-P2-001`, `F-P2-002`, `F-P2-003` s jasnim dokazom po svakom findingu.

OGRANICENJA:
- Ne radi izvan root foldera.
- Ne uvodi nove dependencyje.
- Ne bypassaj domain/ConstraintEngine granicu.
- Ne prelazi na P3.

OBAVEZNA VERIFIKACIJA:
1) cmake --build build --parallel
2) cd build && ctest --output-on-failure
3) Portability smoke compile koji ukljucuje `DenormalFlush.h` + `SanityCheck.h`

OBAVEZNI OUTPUT:
1) Handoff packet u:
   /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P2_handoff_fix.md
2) U handoffu navedi:
   - changed files
   - test komande + rezultat
   - closure map za `F-P2-001`, `F-P2-002`, `F-P2-003`
   - otvorena pitanja (ako postoje)
3) Predlozi status samo do `Review` (ne `Done`).
```
