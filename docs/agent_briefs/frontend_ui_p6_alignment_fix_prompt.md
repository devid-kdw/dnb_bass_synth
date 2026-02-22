# Frontend/UI P6 Alignment Fix Prompt (Copy/Paste)

```text
TI SI FRONTEND/UI AGENT ZA DnB Bass Synth VST3.

RADNI ROOT:
/Users/grzzi/Desktop/dnb_bass_synth

TASK: P6 frontend alignment remediation sync za zatvaranje nalaza `F-P6A-004` i `F-P6A-005` (frontend scope).

OBAVEZNO PROCI TAJ REDOSLIJED DOKUMENATA:
1) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/p6_alignment_audit.md
2) /Users/grzzi/Desktop/dnb_bass_synth/docs/master_implementation_plan.md
3) /Users/grzzi/Desktop/dnb_bass_synth/docs/implementation_plan.md
4) /Users/grzzi/Desktop/dnb_bass_synth/docs/project_rules.md
5) /Users/grzzi/Desktop/dnb_bass_synth/docs/spec/p1_schema_freeze.md
6) /Users/grzzi/Desktop/dnb_bass_synth/docs/spec/mvp_macro_contract.md (ako postoji)
7) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/frontend_ui_agent_brief.md
8) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/frontend_ui_phase_tasklist.md
9) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/frontend_ui_p6_alignment_fix_tasklist.md
10) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/frontend_phase_handoffs/P6_handoff.md
11) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P6_handoff_fix.md (ako postoji)
12) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB Bass Synth VST Plugin Research.pdf
13) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB bass synth document for developer.pdf
14) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx
15) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx

OBAVEZNE AKCIJE:
1) Zatvori `F-P6A-005` (frontend handoff integrity):
   - ispravi naming i tvrdnje u P6 frontend handoffu tako da bude canonical (`Tech`, `Neuro`, `Dark`) i evidence-backed.
2) Zatvori `F-P6A-004` (frontend dio):
   - Ako backend ide `Path A` (full MVP macro contract): uskladi UI bindinge/surface bez dead kontrola i bez bypassa.
   - Ako backend ide `Path B` (ADR defer): ne uvodi lazni UI affordance, dokumentiraj defer alignment bez scope creepa.
3) Potvrdi architecture granice:
   - nema runtime UI->DSP bypassa
   - sve ide kroz APVTS + domain contract.

OGRANICENJA:
- Ne radi izvan root foldera.
- Ne bypassaj `domain/ConstraintEngine`.
- Ne uvodi neodobrene dependencyje.
- Ne ulazi u P7/P8 scope.

OBAVEZNA VERIFIKACIJA:
1) tools/scripts/init_submodules.sh
2) cmake --build build --parallel
3) cd build && ctest --output-on-failure
4) U handoffu navedi binding mapu (`ui_control -> param_id -> exists_in_apvts`).

OBAVEZNI OUTPUT:
1) Handoff packet u:
   /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/frontend_phase_handoffs/P6_handoff_fix.md
2) U handoffu navedi:
   - je li bilo code/doc changeova
   - changed files (ako postoje)
   - closure map za frontend dio `F-P6A-004`, `F-P6A-005`
   - potvrdu da nema runtime bypassa i nestabilnog bindinga
3) Predlozi status samo do `Review`.
```

