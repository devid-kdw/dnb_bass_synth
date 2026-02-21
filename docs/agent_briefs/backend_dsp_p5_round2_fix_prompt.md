# Backend/DSP P5 Round-2 Fix Prompt (Copy/Paste)

```text
TI SI BACKEND/DSP AGENT ZA DnB Bass Synth VST3.

RADNI ROOT:
/Users/grzzi/Desktop/dnb_bass_synth

TASK: P5 Round-2 remediation patch-set za zatvaranje review findings (`F-P5R2-001`, `F-P5R2-002`, `F-P5R2-003`).

OBAVEZNO PROCI TAJ REDOSLIJED DOKUMENATA:
1) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/p5_round2_review.md
2) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/p5_review.md
3) /Users/grzzi/Desktop/dnb_bass_synth/docs/master_implementation_plan.md
4) /Users/grzzi/Desktop/dnb_bass_synth/docs/project_rules.md
5) /Users/grzzi/Desktop/dnb_bass_synth/docs/spec/p1_schema_freeze.md
6) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/backend_dsp_agent_brief.md
7) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/backend_dsp_phase_tasklist.md
8) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/backend_dsp_p5_round2_fix_tasklist.md
9) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P5_handoff_fix.md
10) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/frontend_phase_handoffs/P5_handoff_fix.md
11) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB Bass Synth VST Plugin Research.pdf
12) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB bass synth document for developer.pdf
13) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx
14) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx

OBAVEZNE IZMJENE U P5 ROUND-2:
1) Zatvori `F-P5R2-001` (APVTS contract completeness):
   - Napravi cisti inventar svih aktivnih APVTS parametara.
   - Za svaki parametar postavi status:
     - `wired` (ima dokaziv runtime efekt), ili
     - `deferred` (uklonjen iz aktivnog P5 APVTS layouta uz doc razlog).
   - Nema host-facing dead/no-op parametara.
2) Odrzi canonical MVP macro set aktivnim i funkcionalnim:
   - `macro.neuro_formant`
   - `macro.fm_metal`
   - `macro.roller_dynamics`
   - `macro.liquid_depth`
   - `macro.style_morph`
   - `macro.roller_dynamics` ne smije biti dead no-op u runtime pathu.
3) Zatvori `F-P5R2-002` (test evidence):
   - Dodaj testove koji dokazuju:
     - style mode mapiranje (`style.mode`) je deterministic i bounded,
     - style morph proizvodi output razliku pod kontroliranim inputom,
     - `macro.roller_dynamics` nije no-op.
   - Uvezi sve nove testove u `tests/CMakeLists.txt` kroz `ctest`.
4) Zatvori backend dio `F-P5R2-003` (canonical naming):
   - U backend contract/UI-facing choice stringovima koristi MVP naming:
     - `Tech`, `Neuro`, `Dark`
   - Ne koristiti `Neurofunk` kao canonical label.

OGRANICENJA:
- Ne radi izvan root foldera.
- Ne uvodi nove dependencyje.
- Ne bypassaj domain/ConstraintEngine granicu.
- Ne ulazi u P6/P7 implementaciju.

OBAVEZNA VERIFIKACIJA:
1) tools/scripts/init_submodules.sh
2) cmake --build build --parallel
3) cd build && ctest --output-on-failure
4) Potvrdi da APVTS inventory nema `dead/no-op` stavke.

OBAVEZNI OUTPUT:
1) Handoff packet u:
   /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P5_handoff_fix_round2.md
2) U handoffu navedi:
   - changed files
   - test komande + rezultat
   - closure map za `F-P5R2-001`, `F-P5R2-002`, `F-P5R2-003`
   - APVTS inventory tabelu: `param_id | status(wired/deferred) | runtime_path`
   - otvorena pitanja (ako postoje)
3) Predlozi status samo do `Review` (ne `Done`).
```
