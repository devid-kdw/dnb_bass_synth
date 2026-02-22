TI SI FRONTEND/UI AGENT ZA DnB Bass Synth VST3.

RADNI ROOT:
/Users/grzzi/Desktop/dnb_bass_synth

TASK: P7 remediation patch-set za zatvaranje nalaza `F-P7R-001` i `F-P7R-002` prije P8 gate-a.

OBAVEZNO PROCI OVAJ REDOSLIJED DOKUMENATA:
1) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/p7_fix_review.md
2) /Users/grzzi/Desktop/dnb_bass_synth/docs/master_implementation_plan.md
3) /Users/grzzi/Desktop/dnb_bass_synth/docs/implementation_plan.md
4) /Users/grzzi/Desktop/dnb_bass_synth/docs/project_rules.md
5) /Users/grzzi/Desktop/dnb_bass_synth/docs/spec/ui_graphic_asset_contract.md
6) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/frontend_ui_agent_brief.md
7) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/frontend_ui_phase_tasklist.md
8) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/frontend_ui_p7_fix_tasklist.md
9) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/frontend_phase_handoffs/P7_design_integration_handoff.md
10) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/design_phase_handoffs/P7_design_handoff.md
11) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/design_phase_handoffs/P7_design_handoff_fix.md
12) /Users/grzzi/Desktop/dnb_bass_synth/assets/ui/designer/p7/manifests/p7_ui_png_manifest.csv
13) /Users/grzzi/Desktop/dnb_bass_synth/assets/ui/designer/p7/manifests/p7_ui_control_asset_map.md
14) /Users/grzzi/Desktop/dnb_bass_synth/src/domain/ParameterSpec.h
15) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB Bass Synth VST Plugin Research.pdf
16) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB bass synth document for developer.pdf
17) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx
18) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx

OBAVEZNE IZMJENE:
1) Zatvori `F-P7R-001`:
   - Ispravi `style.mode` UI binding da bude ispravan 3-state mapping (`Tech/Neuro/Dark`) na APVTS choice parametar.
   - Ne koristiti bool-semantiku koja ne mapira deterministicno na enum state.
   - Zadrzi canonical morph ID: `macro.style_morph`.
2) Zatvori `F-P7R-002`:
   - Ispravi `docs/qa/frontend_phase_handoffs/P7_design_integration_handoff.md` da bude evidence-backed.
   - Zamijeni placeholder asset nazive stvarnim manifest nazivima.
   - Navedi tocne test rezultate (bez zastarjelih countova).
3) Odrzi architecture granice:
   - nema runtime UI->DSP bypassa
   - sve ide kroz APVTS + domain contract

OGRANICENJA:
- Ne radi izvan root foldera.
- Ne uvodi neodobrene dependencyje.
- Ne ulazi u P8 scope.

OBAVEZNA VERIFIKACIJA:
1) tools/scripts/init_submodules.sh
2) cmake --build build --parallel
3) cd build && ctest --output-on-failure
4) Contract checks:
   - nema `style.morph` legacy reference
   - svi asset fileovi iz handoff mape postoje u manifestu

OBAVEZNI OUTPUT:
1) Handoff packet u:
   /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/frontend_phase_handoffs/P7_design_integration_handoff_fix.md
2) U handoffu navedi:
   - changed files
   - closure map za `F-P7R-001`, `F-P7R-002`
   - mapu: `ui_control -> param_id -> asset_file`
   - test komande + rezultati
   - potvrdu da nema bypassa i dead kontrola
3) Predlozi status samo do `Review`.
