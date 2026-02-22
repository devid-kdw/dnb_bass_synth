# Frontend/UI P6.1 Fix Prompt (Copy/Paste)

```text
TI SI FRONTEND/UI AGENT ZA DnB Bass Synth VST3.

RADNI ROOT:
/Users/grzzi/Desktop/dnb_bass_synth

TASK: P6.1 frontend remediation patch-set za zatvaranje nalaza iz `docs/qa/p6_1_review.md` i frontend dijela gate backloga prije P7.

OBAVEZNO PROCI TAJ REDOSLIJED DOKUMENATA:
1) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/p6_1_review.md
2) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/p6_to_p7_gate_deviations.md
3) /Users/grzzi/Desktop/dnb_bass_synth/docs/spec/macro_10_contract_proposal.md
4) /Users/grzzi/Desktop/dnb_bass_synth/docs/spec/p1_schema_freeze.md
5) /Users/grzzi/Desktop/dnb_bass_synth/docs/spec/mvp_macro_contract.md
6) /Users/grzzi/Desktop/dnb_bass_synth/docs/master_implementation_plan.md
7) /Users/grzzi/Desktop/dnb_bass_synth/docs/implementation_plan.md
8) /Users/grzzi/Desktop/dnb_bass_synth/docs/project_rules.md
9) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/frontend_ui_agent_brief.md
10) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/frontend_ui_phase_tasklist.md
11) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/frontend_ui_p6_1_fix_tasklist.md
12) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/frontend_phase_handoffs/P6_1_handoff.md
13) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P6_1_handoff_fix.md (ako postoji)
14) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB Bass Synth VST Plugin Research.pdf
15) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB bass synth document for developer.pdf
16) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx
17) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx

OBAVEZNE IZMJENE U P6.1 FIX:
1) Zatvori `F-P6.1-003` (UX hierarchy drift):
   - implementiraj jasnu podjelu:
     - primary/performance surface = 4 zakljucana makroa
     - advanced surface = dodatnih 6 makroa
2) Odrzi `G-P6P7-004` (frontend scope):
   - svi bindingi moraju biti canonical param ID-jevi
   - nema dead kontrola
   - nema runtime UI->DSP bypassa
3) Uskladi frontend handoff evidence:
   - ispravi `docs/qa/frontend_phase_handoffs/P6_1_handoff.md` tako da odrazava realan UI state i stvarne test rezultate.
4) Ako backend fix promijeni contract detalje:
   - napravi minimalni alignment bez scope creepa.

OGRANICENJA:
- Ne radi izvan root foldera.
- Ne bypassaj domain/ConstraintEngine.
- Ne uvodi neodobrene dependencyje.
- Ne ulazi u P7/P8 feature scope.

OBAVEZNA VERIFIKACIJA:
1) tools/scripts/init_submodules.sh
2) cmake --build build --parallel
3) cd build && ctest --output-on-failure
4) U handoffu navedi binding mapu: `ui_control -> param_id -> exists_in_apvts`.

OBAVEZNI OUTPUT:
1) Handoff packet u:
   /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/frontend_phase_handoffs/P6_1_handoff_fix.md
2) U handoffu navedi:
   - je li bilo code/doc promjena
   - changed files
   - closure map za `F-P6.1-003` i frontend dio `G-P6P7-004`
   - binding map evidence + potvrdu da nema bypassa
3) Predlozi status samo do `Review`.
```
