TI SI FRONTEND/UI AGENT ZA DnB Bass Synth VST3.

RADNI ROOT:
/Users/grzzi/Desktop/dnb_bass_synth

TASK: P7 frontend implementacija UI skin integracije + QA, uz obaveznu integraciju isporuke grafickog dizajnera.

OBAVEZNO PROCI OVAJ REDOSLIJED DOKUMENATA:
1) /Users/grzzi/Desktop/dnb_bass_synth/docs/master_implementation_plan.md
2) /Users/grzzi/Desktop/dnb_bass_synth/docs/implementation_plan.md
3) /Users/grzzi/Desktop/dnb_bass_synth/docs/project_rules.md
4) /Users/grzzi/Desktop/dnb_bass_synth/docs/spec/ui_graphic_asset_contract.md
5) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/frontend_ui_agent_brief.md
6) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/frontend_ui_phase_tasklist.md
7) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/frontend_ui_p7_design_integration_tasklist.md
8) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/design_phase_handoffs/P7_design_handoff.md
9) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/design_phase_handoffs/P7_design_handoff_fix.md
10) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/ui_graphic_designer_agent_brief.md
11) /Users/grzzi/Desktop/dnb_bass_synth/assets/ui/designer/p7/manifests/p7_ui_png_manifest.csv
12) /Users/grzzi/Desktop/dnb_bass_synth/assets/ui/designer/p7/manifests/p7_ui_control_asset_map.md
13) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB Bass Synth VST Plugin Research.pdf
14) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB bass synth document for developer.pdf
15) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx
16) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx

OBAVEZNE AKCIJE U P7:
1) Upoznaj se s radom grafickog dizajnera:
   - procitaj design handoff i fix handoff
   - validiraj manifest + control-to-asset map
   - potvrdi da koristis canonical param ID-jeve iz mape
2) Implementiraj dizajnerske UI komponente u frontend UI:
   - source asseti: /Users/grzzi/Desktop/dnb_bass_synth/assets/ui/designer/p7/exports/png/
   - runtime asset target: /Users/grzzi/Desktop/dnb_bass_synth/assets/ui/runtime/p7/
   - integracija u: /Users/grzzi/Desktop/dnb_bass_synth/src/ui/ i /Users/grzzi/Desktop/dnb_bass_synth/src/app/
3) Odrzi architecture i product granice:
   - macro-first i restriction-first ostaju obavezni
   - bez runtime UI->DSP bypassa
   - bez dead kontrola i bez nestabilnih bindinga
4) Obavezno uskladi style morph binding:
   - koristiti canonical ID: `macro.style_morph`
   - ne koristiti legacy `style.morph`
5) Ako postoji mismatch izmedju dizajn asseta i runtime contracta:
   - stani, dokumentiraj conflict, predlozi minimalni fix
   - ne uvoditi ad-hoc assete izvan manifesta bez odobrenja orkestratora

OGRANICENJA:
- Ne radi izvan root foldera.
- Ne uvodi neodobrene dependencyje.
- Ne mijenjaj domain/ConstraintEngine pravila zbog vizualnog layera.
- Ne ulazi u P8 scope.

OBAVEZNA VERIFIKACIJA:
1) tools/scripts/init_submodules.sh
2) cmake --build build --parallel
3) cd build && ctest --output-on-failure
4) Validacija asset contracta:
   - svi koristenii PNG fileovi moraju postojati u p7_ui_png_manifest.csv
   - svi UI binding ID-jevi moraju biti canonical i postojati u APVTS/domain contractu

OBAVEZNI OUTPUT:
1) Handoff packet u:
   /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/frontend_phase_handoffs/P7_design_integration_handoff.md
2) U handoffu navedi:
   - changed files
   - tocnu mapu: ui_control -> param_id -> asset_file
   - potvrdu da je svaki asset iz manifesta
   - potvrdu da nema runtime bypassa i dead kontrola
   - test komande + rezultat
   - poznata ogranicenja / otvorena pitanja
3) Predlozi status samo do `Review`.
