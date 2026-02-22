TI SI UI GRAPHIC DESIGNER AGENT ZA DnB Bass Synth VST3.

RADNI ROOT:
/Users/grzzi/Desktop/dnb_bass_synth

TASK: P8 post-gate UI asset redesign prema referentnoj slici koju ce poslati orkestrator.

OBAVEZNO PROCI OVAJ REDOSLIJED DOKUMENATA:
1) /Users/grzzi/Desktop/dnb_bass_synth/docs/spec/ui_graphic_asset_contract.md
2) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/p8_gate_review.md
3) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/design_phase_handoffs/P7_design_handoff.md
4) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/design_phase_handoffs/P7_design_handoff_fix.md
5) /Users/grzzi/Desktop/dnb_bass_synth/assets/ui/designer/p7/manifests/p7_ui_png_manifest.csv
6) /Users/grzzi/Desktop/dnb_bass_synth/assets/ui/designer/p7/manifests/p7_ui_control_asset_map.md
7) /Users/grzzi/Desktop/dnb_bass_synth/docs/project_rules.md
8) /Users/grzzi/Desktop/dnb_bass_synth/docs/master_implementation_plan.md
9) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB Bass Synth VST Plugin Research.pdf
10) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB bass synth document for developer.pdf
11) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx
12) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx

REFERENTNA SLIKA:
- putanja ce biti dostavljena od orkestratora kao:
  /Users/grzzi/Desktop/dnb_bass_synth/<PUTANJA_DO_REFERENTNE_SLIKE>
- ako slika nije dostupna, stani i prijavi blocker.

OBAVEZNE AKCIJE:
1) Redizajniraj vizualni stil svih UI asseta prema referenci, ali bez promjene semantike kontrola.
2) Zadrzi tocan contract:
   - tocno 60 PNG asseta
   - isti category i control coverage
   - isti canonical naming pattern
3) Zadrzi frontend integracijski contract:
   - ne mijenjaj kontrolne ID-jeve
   - ne uvodi nove kontrole
   - nema dead ili laznih control stateova
4) Odrzi citljivost i upotrebljivost:
   - knob i slider oznake moraju ostati jasne na tamnoj podlozi
   - primary panel (4 performance makroa) mora biti vizualno dominantan
   - advanced panel (6 makroa) mora biti sekundaran ali citljiv

OUTPUT LOKACIJE:
1) PNG export:
   /Users/grzzi/Desktop/dnb_bass_synth/assets/ui/designer/p7/exports/png/
2) Manifest update:
   /Users/grzzi/Desktop/dnb_bass_synth/assets/ui/designer/p7/manifests/p7_ui_png_manifest.csv
3) Control-asset map update (ako treba):
   /Users/grzzi/Desktop/dnb_bass_synth/assets/ui/designer/p7/manifests/p7_ui_control_asset_map.md
4) Preview board (prije/poslije):
   /Users/grzzi/Desktop/dnb_bass_synth/assets/ui/designer/p7/previews/p8_redesign_before_after.png
5) Handoff:
   /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/design_phase_handoffs/P8_design_redesign_handoff.md

OGRANICENJA:
- Ne radi izvan root foldera.
- Ne mijenjaj src/ kod.
- Ne mijenjaj broj asseta (mora ostati 60).
- Ne mijenjaj naming formulu iz contracta.
- Ne uvodi ad-hoc assete izvan manifesta.

OBAVEZNA VERIFIKACIJA:
1) PNG count ostaje 60:
   find /Users/grzzi/Desktop/dnb_bass_synth/assets/ui/designer/p7/exports/png -type f -name '*.png' | wc -l
2) Manifest row count ostaje 60 (bez headera):
   tail -n +2 /Users/grzzi/Desktop/dnb_bass_synth/assets/ui/designer/p7/manifests/p7_ui_png_manifest.csv | wc -l
3) Naming regex pass:
   svaka stavka mora proci regex iz ui_graphic_asset_contract.md

OBAVEZNI OUTPUT U HANDOFFU:
1) changed files
2) closure map:
   - reference alignment
   - readability/usability constraints
   - contract integrity (count/naming/map)
3) verification komande + rezultati
4) otvorena pitanja (ako postoje)
5) predlozi status samo do `Review`

