# UI Graphic Designer Tasklist po Fazama

Last updated: 2026-02-22  
Root: `/Users/grzzi/Desktop/dnb_bass_synth`

## 1. Obavezno prije pocetka
1. Procitaj:
   - `/Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB Bass Synth VST Plugin Research.pdf`
   - `/Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB bass synth document for developer.pdf`
   - `/Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx`
   - `/Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/project_rules.md`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/spec/ui_graphic_asset_contract.md`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/ui_graphic_designer_agent_brief.md`
2. Potvrdi da radis iskljucivo unutar root foldera.
3. Potvrdi da broj i naming formula ostaju tocno po contractu.

## 2. P7 - UI Design Pack v1 (Primary)
Status: `Planned`  
Primary owner: UI Graphic Designer  
Depends on: `P6.1 Done`

Taskovi:
1. Dizajnirati i eksportati tocno 60 PNG elemenata po kategorijama iz contracta.
2. Odrzati jasno razdvajanje:
   - primary/performance surface = 4 makroa
   - advanced surface = 6 makroa
3. Ispratiti canonical style naming (`Tech`, `Neuro`, `Dark`) kroz style kontrolni set.
4. Izraditi mapping datoteku `ui_control -> asset_file` za frontend implementaciju.
5. Izraditi manifest s checksumima i dimenzijama.

Output:
1. `assets/ui/designer/p7/exports/png/*`
2. `assets/ui/designer/p7/manifests/p7_ui_png_manifest.csv`
3. `assets/ui/designer/p7/manifests/p7_ui_control_asset_map.md`
4. `docs/qa/design_phase_handoffs/P7_design_handoff.md`

DoD:
1. Asset count je tocno 60.
2. Svi fileovi prate naming formulu.
3. Manifest i handoff su kompletni i evidence-backed.
4. Frontend moze implementirati bez dodatnih pretpostavki.

## 3. P8 - Design QA Support (Secondary)
Status: `Planned`  
Primary owner: UI Graphic Designer + Frontend/UI

Taskovi:
1. Ispraviti clipping/alignment/state feedback koji prijavi frontend QA.
2. Verzijski bumpati samo promijenjene assete (`v002`, `v003`, ...).
3. Azurirati manifest/handoff nakon svake izmjene.

DoD:
1. Nema asset drift-a bez dokumentirane promjene.
2. Integracija prolazi bez nedostajucih state varijanti.

## 4. Handoff packet format (obavezno)
Za svaku fazu dizajn agent predaje:
1. Phase ID i status prijedlog (`Planned -> Review`).
2. Točan popis promijenjenih fileova.
3. Count po kategorijama + ukupni count.
4. Manifest validation (naming regex + checksums).
5. Poznate limite / otvorena pitanja.

Preporucena lokacija:
- `docs/qa/design_phase_handoffs/<PHASE_ID>_design_handoff.md`
