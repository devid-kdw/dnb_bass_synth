TI SI FRONTEND/UI AGENT ZA DnB Bass Synth VST3.

RADNI ROOT:
/Users/grzzi/Desktop/dnb_bass_synth

TASK: P8 frontend CI/CD hardening support (zadnja faza prije final MVP release candidate-a).

OBAVEZNO PROCI OVAJ REDOSLIJED DOKUMENATA:
1) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/p7_post_gate_daw_hotfix_review.md
2) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/p7_final_gate_review.md
3) /Users/grzzi/Desktop/dnb_bass_synth/docs/master_implementation_plan.md
4) /Users/grzzi/Desktop/dnb_bass_synth/docs/implementation_plan.md
5) /Users/grzzi/Desktop/dnb_bass_synth/docs/project_rules.md
6) /Users/grzzi/Desktop/dnb_bass_synth/docs/spec/ui_graphic_asset_contract.md
7) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/current_version_daw_test_checklist.md
8) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/frontend_ui_agent_brief.md
9) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/frontend_ui_phase_tasklist.md
10) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/frontend_ui_p8_kickoff_tasklist.md
11) /Users/grzzi/Desktop/dnb_bass_synth/assets/ui/designer/p7/manifests/p7_ui_png_manifest.csv
12) /Users/grzzi/Desktop/dnb_bass_synth/assets/ui/designer/p7/manifests/p7_ui_control_asset_map.md
13) /Users/grzzi/Desktop/dnb_bass_synth/src/ui/bindings/BindingLayer.h
14) /Users/grzzi/Desktop/dnb_bass_synth/src/ui/components/ImageSlider.h
15) /Users/grzzi/Desktop/dnb_bass_synth/src/ui/components/VisualFeedbackView.h
16) /Users/grzzi/Desktop/dnb_bass_synth/.github/workflows/ci.yml
17) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB Bass Synth VST Plugin Research.pdf
18) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB bass synth document for developer.pdf
19) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx
20) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx

OBAVEZNE AKCIJE U P8:
1) Uskladi frontend CI contract checks:
   - canonical param ID validacija za UI binding layer.
   - blokiraj legacy naming regresije (`style.morph` ne smije se pojaviti u runtime/doc contractu).
2) Uskladi asset integrity checks:
   - runtime koristenii asseti moraju biti uskladeni s manifestom.
   - nema missing/dead UI stateova za kontrole u scopeu.
3) Uskladi DAW-regresijske guardove:
   - osiguraj da knob endpoint na `0%`/`100%` ostane ispravan.
   - osiguraj da center visual panel nema static/runtime overlap regresiju.
4) Odrzi architecture granice:
   - nema runtime UI->DSP bypassa
   - sve kroz APVTS + domain contract

OGRANICENJA:
- Ne radi izvan root foldera.
- Ne uvodi neodobrene dependencyje.
- Ne mijenjaj domain/ConstraintEngine pravila zbog UI layera.
- Ne ulazi u scope izvan P8.

OBAVEZNA VERIFIKACIJA:
1) tools/scripts/init_submodules.sh
2) cmake --build build --parallel
3) cd build && ctest --output-on-failure
4) Contract checks:
   - `style.morph` legacy reference mora biti 0 u runtime binding pathu
5) Asset checks:
   - svi runtime asseti moraju postojati u manifestu

OBAVEZNI OUTPUT:
1) Handoff packet u:
   /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/frontend_phase_handoffs/P8_handoff.md
2) U handoffu navedi:
   - changed files
   - closure map za frontend P8 scope
   - tocne CI/contract/asset komande + rezultati
   - potvrdu da nema runtime bypassa i dead kontrola
   - otvorena pitanja (ako postoje)
3) Predlozi status samo do `Review`.
