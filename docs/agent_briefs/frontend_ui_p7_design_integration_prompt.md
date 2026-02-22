TI SI FRONTEND/UI AGENT ZA DnB Bass Synth VST3.

RADNI ROOT:
/Users/grzzi/Desktop/dnb_bass_synth

TASK: P7 implementacija grafickog designer asset paketa u runtime UI.

OBAVEZNO PROCI OVAJ REDOSLIJED DOKUMENATA:
1) /Users/grzzi/Desktop/dnb_bass_synth/docs/master_implementation_plan.md
2) /Users/grzzi/Desktop/dnb_bass_synth/docs/project_rules.md
3) /Users/grzzi/Desktop/dnb_bass_synth/docs/spec/ui_graphic_asset_contract.md
4) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/frontend_ui_agent_brief.md
5) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/frontend_ui_phase_tasklist.md
6) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/frontend_ui_p7_design_integration_tasklist.md
7) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/design_phase_handoffs/P7_design_handoff.md
8) /Users/grzzi/Desktop/dnb_bass_synth/assets/ui/designer/p7/manifests/p7_ui_png_manifest.csv
9) /Users/grzzi/Desktop/dnb_bass_synth/assets/ui/designer/p7/manifests/p7_ui_control_asset_map.md
10) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB Bass Synth VST Plugin Research.pdf
11) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB bass synth document for developer.pdf
12) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx
13) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx

OBAVEZNE AKCIJE:
1) Implementiraj samo assete koji postoje u designer manifestu.
2) Odrzi macro-first i restriction-first UX logiku.
3) Ne uvodi runtime UI->DSP bypass.
4) Evidentiraj punu mapping tablicu: `ui_control -> param_id -> asset_file`.

OGRANICENJA:
- Ne radi izvan root foldera.
- Ne uvodi neodobrene dependencyje.
- Ne mijenjaj domain pravila radi vizualnog layera.

OBAVEZNA VERIFIKACIJA:
1) tools/scripts/init_submodules.sh
2) cmake --build build --parallel
3) cd build && ctest --output-on-failure

OBAVEZNI OUTPUT:
1) Handoff packet:
   /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/frontend_phase_handoffs/P7_design_integration_handoff.md
2) U handoffu navedi:
   - changed files
   - tocnu binding+asset mapu
   - potvrdu da su svi asseti iz manifesta i da nema dead kontrola
3) Predlozi status samo do `Review`.
