TI SI UI GRAPHIC DESIGNER AGENT ZA DnB Bass Synth VST3.

RADNI ROOT:
/Users/grzzi/Desktop/dnb_bass_synth

TASK: P7 remediation patch za zatvaranje design mapping blocker-a prije frontend P7 starta.

OBAVEZNO PROCI OVAJ REDOSLIJED DOKUMENATA:
1) /Users/grzzi/Desktop/dnb_bass_synth/docs/spec/ui_graphic_asset_contract.md
2) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/design_phase_handoffs/P7_design_handoff.md
3) /Users/grzzi/Desktop/dnb_bass_synth/assets/ui/designer/p7/manifests/p7_ui_control_asset_map.md
4) /Users/grzzi/Desktop/dnb_bass_synth/assets/ui/designer/p7/manifests/p7_ui_png_manifest.csv
5) /Users/grzzi/Desktop/dnb_bass_synth/src/domain/ParameterSpec.h
6) /Users/grzzi/Desktop/dnb_bass_synth/docs/project_rules.md
7) /Users/grzzi/Desktop/dnb_bass_synth/docs/master_implementation_plan.md
8) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB Bass Synth VST Plugin Research.pdf
9) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB bass synth document for developer.pdf
10) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx
11) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx

OBAVEZNE IZMJENE:
1) Zatvori canonical param mapping blocker:
   - U datoteci:
     /Users/grzzi/Desktop/dnb_bass_synth/assets/ui/designer/p7/manifests/p7_ui_control_asset_map.md
   - Zamijeni sve `style.morph` reference s canonical ID-em `macro.style_morph` za morph kontrole:
     - `ui.style.morph.track`
     - `ui.style.morph.thumb`
     - `ui.style.morph.glow`
2) Za dekorativni panel element:
   - `ui.panel.style_morph` postavi `Param ID` na `n/a` (ako panel nije runtime-bindan kontrolni parametar).
3) Ažuriraj handoff evidenciju:
   - datoteka:
     /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/design_phase_handoffs/P7_design_handoff.md
   - dodaj kratku remediation napomenu da je mapping usklađen na canonical `macro.style_morph`.

OGRANICENJA:
- Ne radi izvan root foldera.
- Ne mijenjaj broj PNG fajlova (mora ostati 60).
- Ne mijenjaj naming formulu i ne radi redesign scope creep.
- Ne diraj `src/` kod osim read-only provjere canonical ID-a.

OBAVEZNA VERIFIKACIJA:
1) Provjeri da više nema `style.morph` u control mapi:
   - rg -n "`style.morph`" /Users/grzzi/Desktop/dnb_bass_synth/assets/ui/designer/p7/manifests/p7_ui_control_asset_map.md
   - rezultat mora biti prazan
2) Provjeri da canonical ID postoji u mapi:
   - rg -n "`macro.style_morph`" /Users/grzzi/Desktop/dnb_bass_synth/assets/ui/designer/p7/manifests/p7_ui_control_asset_map.md
   - mora postojati za track/thumb/glow kontrole
3) Provjeri da se PNG package nije promijenio po countu:
   - find /Users/grzzi/Desktop/dnb_bass_synth/assets/ui/designer/p7/exports/png -type f -name '*.png' | wc -l
   - rezultat mora biti 60

OBAVEZNI OUTPUT:
1) Handoff packet u:
   /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/design_phase_handoffs/P7_design_handoff_fix.md
2) U handoffu navedi:
   - changed files
   - closure map za blocker (`style.morph` -> `macro.style_morph`)
   - rezultat verifikacijskih komandi
   - potvrdu da je PNG count ostao 60
3) Predlozi status samo do `Review`.
