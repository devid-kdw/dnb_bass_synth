# Backend/DSP P5 Round-3 Fix Prompt (Copy/Paste)

```text
TI SI BACKEND/DSP AGENT ZA DnB Bass Synth VST3.

RADNI ROOT:
/Users/grzzi/Desktop/dnb_bass_synth

TASK: P5 Round-3 remediation patch-set za zatvaranje finalnih nalaza (`F-P5R3-001`, `F-P5R3-002`, `F-P5R3-003`).

OBAVEZNO PROCI TAJ REDOSLIJED DOKUMENATA:
1) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/p5_round3_review.md
2) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/p5_round2_review.md
3) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/p5_review.md
4) /Users/grzzi/Desktop/dnb_bass_synth/docs/master_implementation_plan.md
5) /Users/grzzi/Desktop/dnb_bass_synth/docs/project_rules.md
6) /Users/grzzi/Desktop/dnb_bass_synth/docs/spec/p1_schema_freeze.md
7) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/backend_dsp_agent_brief.md
8) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/backend_dsp_phase_tasklist.md
9) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/backend_dsp_p5_round3_fix_tasklist.md
10) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P5_handoff_fix_round2.md
11) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/frontend_phase_handoffs/P5_handoff_fix_round2.md
12) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB Bass Synth VST Plugin Research.pdf
13) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB bass synth document for developer.pdf
14) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx
15) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx

OBAVEZNE IZMJENE U P5 ROUND-3:
1) Zatvori `F-P5R3-001` (APVTS no-op exposure):
   - Napravi inventory svih aktivnih APVTS parametara iz `createParameterLayout()`.
   - Za svaki parametar odaberi:
     a) `wired` -> implementiran stvaran runtime efekt kroz domain/DSP path, ili
     b) `deferred` -> uklonjen iz aktivnog P5 layouta uz dokumentiran razlog.
   - Nema host-facing dead/no-op parametara.
2) Zatvori `F-P5R3-002` (`macro.roller_dynamics` audio evidence):
   - Osiguraj da `macro.roller_dynamics` utjece na renderani audio output (ne samo na domain struct vrijednosti).
   - Dodaj dokazni test sa kontroliranim uvjetima (isti note/block, razlika samo macro vrijednost).
3) Zatvori `F-P5R3-003` (handoff integrity):
   - U handoffu navodi samo dokazive `wired` tvrdnje.
   - Svaki `wired` unos mora imati:
     - code path referencu (file + linija),
     - test dokaz (naziv testa / ctest rezultat).

OGRANICENJA:
- Ne radi izvan root foldera.
- Ne uvodi nove dependencyje.
- Ne bypassaj domain/ConstraintEngine granicu.
- Ne ulazi u P6/P7 scope.

OBAVEZNA VERIFIKACIJA:
1) tools/scripts/init_submodules.sh
2) cmake --build build --parallel
3) cd build && ctest --output-on-failure
4) Potvrdi da APVTS inventory nema `dead/no-op` stavke.

OBAVEZNI OUTPUT:
1) Handoff packet u:
   /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P5_handoff_fix_round3.md
2) U handoffu navedi:
   - changed files
   - test komande + rezultat
   - closure map za `F-P5R3-001`, `F-P5R3-002`, `F-P5R3-003`
   - APVTS inventory: `param_id | status(wired/deferred) | code_path | test_evidence`
   - otvorena pitanja (ako postoje)
3) Predlozi status samo do `Review` (ne `Done`).
```
