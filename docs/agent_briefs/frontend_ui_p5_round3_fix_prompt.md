# Frontend/UI P5 Round-3 Fix Prompt (Copy/Paste)

```text
TI SI FRONTEND/UI AGENT ZA DnB Bass Synth VST3.

RADNI ROOT:
/Users/grzzi/Desktop/dnb_bass_synth

TASK: P5 Round-3 frontend remediation sync nakon backend P5 Round-3 patcha.

OBAVEZNO PROCI TAJ REDOSLIJED DOKUMENATA:
1) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/p5_round3_review.md
2) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/p5_round2_review.md
3) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/p5_review.md
4) /Users/grzzi/Desktop/dnb_bass_synth/docs/master_implementation_plan.md
5) /Users/grzzi/Desktop/dnb_bass_synth/docs/project_rules.md
6) /Users/grzzi/Desktop/dnb_bass_synth/docs/spec/p1_schema_freeze.md
7) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/frontend_ui_agent_brief.md
8) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/frontend_ui_phase_tasklist.md
9) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/frontend_ui_p5_round3_fix_tasklist.md
10) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/frontend_phase_handoffs/P5_handoff_fix_round2.md
11) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P5_handoff_fix_round3.md (ako postoji)
12) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB Bass Synth VST Plugin Research.pdf
13) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB bass synth document for developer.pdf
14) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx
15) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx

OBAVEZNE AKCIJE U P5 ROUND-3:
1) Uskladi UI contract sa backend Round-3 APVTS inventory odlukama:
   - koristi samo canonical i aktivne param ID-jeve.
   - ako backend defera neki param, ukloni stale binding/reference iz UI layera.
2) Odrzi canonical MVP UX:
   - style naming: `Tech`, `Neuro`, `Dark`
   - macro panel: 4 canonical MVP makro kontrole
     - `macro.neuro_formant`
     - `macro.fm_metal`
     - `macro.roller_dynamics`
     - `macro.liquid_depth`
   - `macro.style_morph` ostaje zaseban morph control.
3) Odrzi architecture boundaries:
   - nema runtime UI->DSP bypassa
   - sve ide kroz APVTS + domain contract
4) Ako backend Round-3 ne mijenja frontend-facing contract:
   - predaj no-change ili doc-only handoff (bez nepotrebnog refaktora).

OGRANICENJA:
- Ne radi izvan root foldera.
- Ne bypassaj domain/ConstraintEngine.
- Ne uvodi neodobrene dependencyje.
- Ne ulazi u P6/P7 scope.

OBAVEZNA VERIFIKACIJA:
1) tools/scripts/init_submodules.sh
2) cmake --build build --parallel
3) cd build && ctest --output-on-failure
4) U handoffu navedi binding mapu (`ui_control -> param_id -> exists_in_apvts`).

OBAVEZNI OUTPUT:
1) Handoff packet u:
   /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/frontend_phase_handoffs/P5_handoff_fix_round3.md
2) U handoffu navedi:
   - je li bilo code/doc changeova
   - changed files (ako postoje)
   - closure map za frontend dio `F-P5R3-001` i `F-P5R3-003`
   - potvrdu da nema runtime bypassa i nestabilnog bindinga
3) Predlozi status samo do `Review`.
```
