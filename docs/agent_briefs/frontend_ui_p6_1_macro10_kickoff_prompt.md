# Frontend/UI P6.1 Macro-10 Kickoff Prompt (Copy/Paste)

```text
TI SI FRONTEND/UI AGENT ZA DnB Bass Synth VST3.

RADNI ROOT:
/Users/grzzi/Desktop/dnb_bass_synth

TASK: P6.1 frontend implementacija Macro-10 UI contracta + zatvaranje frontend dijela P6->P7 gate odstupanja.

OBAVEZNO PROCI TAJ REDOSLIJED DOKUMENATA:
1) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/p6_to_p7_gate_deviations.md
2) /Users/grzzi/Desktop/dnb_bass_synth/docs/spec/macro_10_contract_proposal.md
3) /Users/grzzi/Desktop/dnb_bass_synth/docs/spec/p1_schema_freeze.md
4) /Users/grzzi/Desktop/dnb_bass_synth/docs/spec/mvp_macro_contract.md
5) /Users/grzzi/Desktop/dnb_bass_synth/docs/master_implementation_plan.md
6) /Users/grzzi/Desktop/dnb_bass_synth/docs/implementation_plan.md
7) /Users/grzzi/Desktop/dnb_bass_synth/docs/project_rules.md
8) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/frontend_ui_agent_brief.md
9) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/frontend_ui_phase_tasklist.md
10) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/frontend_ui_p6_1_macro10_tasklist.md
11) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/frontend_phase_handoffs/P6_handoff_fix.md (ako postoji)
12) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P6_1_handoff.md (ako postoji)
13) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB Bass Synth VST Plugin Research.pdf
14) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB bass synth document for developer.pdf
15) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx
16) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx

OBAVEZNE AKCIJE U P6.1:
1) Odrzi macro-first UX i canonical contract:
   - 4 zaključana makroa ostaju performance-first surface
   - 6 novih makroa iz `macro_10_contract_proposal` dodaj kroz advanced surface
2) Uskladi sve UI bindinge isključivo na canonical param ID-jeve.
3) Zatvori odstupanje `G-P6P7-004` (frontend scope):
   - nema dead kontrola
   - nema runtime UI->DSP bypassa
4) Ako backend P6.1 handoff uvede contract detalje:
   - uskladi naming/layout/binding mapu minimalno i precizno
   - bez scope creepa prema P7/P8

OGRANICENJA:
- Ne radi izvan root foldera.
- Ne bypassaj domain/ConstraintEngine.
- Ne uvodi neodobrene dependencyje.
- Restriction-first i macro-first ostaju obavezni.

OBAVEZNA VERIFIKACIJA:
1) tools/scripts/init_submodules.sh
2) cmake --build build --parallel
3) cd build && ctest --output-on-failure
4) U handoffu navedi binding mapu (`ui_control -> param_id -> exists_in_apvts`).

OBAVEZNI OUTPUT:
1) Handoff packet u:
   /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/frontend_phase_handoffs/P6_1_handoff.md
2) U handoffu navedi:
   - je li bilo code/doc changeova
   - changed files (ako postoje)
   - closure map za `G-P6P7-004` (frontend scope)
   - binding map evidence i potvrdu da nema bypassa
3) Predlozi status samo do `Review`.
```
