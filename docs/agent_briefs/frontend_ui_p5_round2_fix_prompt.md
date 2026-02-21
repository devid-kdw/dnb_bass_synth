# Frontend/UI P5 Round-2 Fix Prompt (Copy/Paste)

```text
TI SI FRONTEND/UI AGENT ZA DnB Bass Synth VST3.

RADNI ROOT:
/Users/grzzi/Desktop/dnb_bass_synth

TASK: P5 Round-2 frontend remediation sync nakon backend P5 Round-2 patcha.

OBAVEZNO PROCI TAJ REDOSLIJED DOKUMENATA:
1) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/p5_round2_review.md
2) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/p5_review.md
3) /Users/grzzi/Desktop/dnb_bass_synth/docs/master_implementation_plan.md
4) /Users/grzzi/Desktop/dnb_bass_synth/docs/project_rules.md
5) /Users/grzzi/Desktop/dnb_bass_synth/docs/spec/p1_schema_freeze.md
6) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/frontend_ui_agent_brief.md
7) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/frontend_ui_phase_tasklist.md
8) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/frontend_ui_p5_round2_fix_tasklist.md
9) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/frontend_phase_handoffs/P5_handoff_fix.md
10) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P5_handoff_fix_round2.md (ako postoji)
11) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB Bass Synth VST Plugin Research.pdf
12) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB bass synth document for developer.pdf
13) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx
14) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx

OBAVEZNE AKCIJE U P5 ROUND-2:
1) Uskladi UI contract sa backend Round-2 APVTS contractom:
   - koristi samo stabilne canonical param ID-jeve iz backend handoffa.
   - svi binding ID-jevi moraju postojati u aktivnom APVTS layoutu.
2) Zatvori `F-P5R2-003` frontend dio:
   - style naming mora biti canonical MVP: `Tech`, `Neuro`, `Dark`.
   - makro panel mora imati canonical MVP macro set:
     - `macro.neuro_formant`
     - `macro.fm_metal`
     - `macro.roller_dynamics`
     - `macro.liquid_depth`
   - `macro.style_morph` ostaje odvojen morph control.
3) Odrzi UX i boundary ogranicenja:
   - macro-first
   - restriction-first
   - bez runtime UI->DSP bypassa
4) Ako backend Round-2 NIJE promijenio frontend-facing contract:
   - predaj no-change/doc-only handoff bez nepotrebnog refactora.

OGRANICENJA:
- Ne radi izvan root foldera.
- Ne bypassaj domain/ConstraintEngine.
- Ne uvodi neodobrene dependencyje.
- Ne ulazi u P6/P7 scope.

OBAVEZNA VERIFIKACIJA:
1) tools/scripts/init_submodules.sh
2) cmake --build build --parallel
3) cd build && ctest --output-on-failure
4) U handoffu navedi binding mapu (`ui_control -> param_id`) i potvrdu da svaki `param_id` postoji.

OBAVEZNI OUTPUT:
1) Handoff packet u:
   /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/frontend_phase_handoffs/P5_handoff_fix_round2.md
2) U handoffu navedi:
   - je li bilo code/doc changeova
   - changed files (ako postoje)
   - closure map za `F-P5R2-003` frontend dio
   - potvrdu da nema runtime bypassa i nestabilnog bindinga
3) Predlozi status samo do `Review`.
```
