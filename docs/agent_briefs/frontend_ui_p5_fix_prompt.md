# Frontend/UI P5 Fix Prompt (Copy/Paste)

```text
TI SI FRONTEND/UI AGENT ZA DnB Bass Synth VST3.

RADNI ROOT:
/Users/grzzi/Desktop/dnb_bass_synth

TASK: P5 remediation sync za zatvaranje frontend-side gapova nakon backend P5 fix patcha.

OBAVEZNO PROCI TAJ REDOSLIJED DOKUMENATA:
1) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/p5_review.md
2) /Users/grzzi/Desktop/dnb_bass_synth/docs/master_implementation_plan.md
3) /Users/grzzi/Desktop/dnb_bass_synth/docs/project_rules.md
4) /Users/grzzi/Desktop/dnb_bass_synth/docs/spec/p1_schema_freeze.md
5) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/frontend_ui_agent_brief.md
6) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/frontend_ui_phase_tasklist.md
7) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/frontend_ui_p5_fix_tasklist.md
8) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/frontend_phase_handoffs/P5_handoff.md
9) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P5_handoff_fix.md (ako postoji)
10) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB Bass Synth VST Plugin Research.pdf
11) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB bass synth document for developer.pdf
12) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx
13) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx

OBAVEZNE AKCIJE U P5 FIX-u:
1) Uskladi UI contract sa backend P5 fix contractom:
   - koristis samo stabilne canonical param ID-jeve iz backend handoffa
   - obavezno podrzi style contract (`style.mode`) ako je backend aktivirao taj parametar
2) Odrzi P5 UX ogranicenja:
   - macro-first ostaje primaran
   - restriction-first ostaje primaran
   - bez runtime UI->DSP bypassa
3) Ako backend P5 fix NIJE promijenio frontend-facing contract:
   - ne radi nepotrebne code promjene
   - predaj no-change ili doc-only handoff
4) Ako backend P5 fix JEST promijenio contract:
   - napravi minimalne UI binding/layout izmjene potrebne za uskladjenje
   - bez scope creepa prema P6 featureima

OGRANICENJA:
- Ne radi izvan root foldera.
- Ne bypassaj domain/ConstraintEngine.
- Ne uvodi neodobrene dependencyje.
- Ne ulazi u P6/P7 scope.

OBAVEZNA VERIFIKACIJA:
1) tools/scripts/init_submodules.sh
2) cmake --build build --parallel
3) cd build && ctest --output-on-failure
4) Potvrdi da su svi UI binding ID-jevi validni i postoje u aktivnom APVTS layoutu.

OBAVEZNI OUTPUT:
1) Handoff packet u:
   /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/frontend_phase_handoffs/P5_handoff_fix.md
2) U handoffu navedi:
   - je li bilo code/doc changeova
   - changed files (ako postoje)
   - tocno sto je uskladjeno s backend P5 contractom
   - potvrdu da nema runtime bypassa i nestabilnog bindinga
3) Predlozi status samo do `Review`.
```
