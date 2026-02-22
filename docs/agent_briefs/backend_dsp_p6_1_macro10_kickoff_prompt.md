# Backend/DSP P6.1 Macro-10 Kickoff Prompt (Copy/Paste)

```text
TI SI BACKEND/DSP AGENT ZA DnB Bass Synth VST3.

RADNI ROOT:
/Users/grzzi/Desktop/dnb_bass_synth

TASK: P6.1 implementacija Macro-10 contracta + zatvaranje backend dijela P6->P7 gate odstupanja.

OBAVEZNO PROCI TAJ REDOSLIJED DOKUMENATA:
1) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/p6_to_p7_gate_deviations.md
2) /Users/grzzi/Desktop/dnb_bass_synth/docs/spec/macro_10_contract_proposal.md
3) /Users/grzzi/Desktop/dnb_bass_synth/docs/spec/p1_schema_freeze.md
4) /Users/grzzi/Desktop/dnb_bass_synth/docs/spec/mvp_macro_contract.md
5) /Users/grzzi/Desktop/dnb_bass_synth/docs/master_implementation_plan.md
6) /Users/grzzi/Desktop/dnb_bass_synth/docs/implementation_plan.md
7) /Users/grzzi/Desktop/dnb_bass_synth/docs/project_rules.md
8) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/backend_dsp_agent_brief.md
9) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/backend_dsp_phase_tasklist.md
10) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/backend_dsp_p6_1_macro10_tasklist.md
11) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P6_handoff_fix.md (ako postoji)
12) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/frontend_phase_handoffs/P6_handoff_fix.md (ako postoji)
13) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB Bass Synth VST Plugin Research.pdf
14) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB bass synth document for developer.pdf
15) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx
16) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx

OBAVEZNE AKCIJE U P6.1:
1) Implementiraj 6 dodatnih canonical makroa (4 postojeća ostaju netaknuta):
   - macro.sub_punch
   - macro.fm_pressure
   - macro.cutoff_motion
   - macro.fold_bite
   - macro.table_drift
   - macro.smash_glue
2) Provedi puni backend chain za svaki novi macro:
   - param spec/APVTS surface
   - domain mapping i style clampovi (`Tech`, `Neuro`, `Dark`)
   - runtime effect u engine/dsp
   - test evidence (mapping + runtime + style)
3) Zatvori odstupanja:
   - G-P6P7-002
   - G-P6P7-003
   - G-P6P7-004 (backend scope)
   - G-P6P7-005 (backend scope: ADR update/supersede input)
4) Ne uvoditi host-visible dead/no-op parametre.
5) Ne uvoditi scope creep prema P7/P8 feature implementaciji.

OGRANICENJA:
- Ne radi izvan root foldera.
- Ne bypassaj domain/ConstraintEngine.
- Ne uvodi neodobrene dependencyje.
- RT-safe pravila su obavezna (bez alloc/lock/io/log u audio threadu).

OBAVEZNA VERIFIKACIJA:
1) tools/scripts/init_submodules.sh
2) cmake --build build --parallel
3) cd build && ctest --output-on-failure
4) cd build && ctest --output-on-failure -R Preset
5) U handoffu navedi: macro evidence mapu (`macro_id -> domain_test -> runtime_test -> style_test`).

OBAVEZNI OUTPUT:
1) Handoff packet u:
   /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P6_1_handoff.md
2) U handoffu navedi:
   - changed files
   - test komande + rezultat
   - closure map za `G-P6P7-002`, `G-P6P7-003`, `G-P6P7-004` (backend), `G-P6P7-005` (backend)
   - migration/version consistency dokaz
   - otvorena pitanja (ako postoje)
3) Predlozi status samo do `Review`.
```
