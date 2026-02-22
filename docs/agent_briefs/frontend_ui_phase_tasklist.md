# Frontend/UI Tasklist po Fazama

Last updated: 2026-02-22  
Root: `/Users/grzzi/Desktop/dnb_bass_synth`

## 1. Obavezno prije početka
1. Pročitaj:
   - `/Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB Bass Synth VST Plugin Research.pdf`
   - `/Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB bass synth document for developer.pdf`
   - `/Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx`
   - `/Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/project_rules.md`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/master_implementation_plan.md`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/frontend_ui_agent_brief.md`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/spec/ui_graphic_asset_contract.md`
2. Potvrdi da radiš isključivo unutar root foldera.
3. Provjeri u `docs/master_implementation_plan.md` koja je aktivna ili prva `Planned` faza relevantna za frontend.
4. Ako postoji dizajn handoff, učitaj:
   - `docs/qa/design_phase_handoffs/P7_design_handoff.md`
   - `assets/ui/designer/p7/manifests/p7_ui_png_manifest.csv`
   - `assets/ui/designer/p7/manifests/p7_ui_control_asset_map.md`

## 2. P1 - Domain Constraint Core (Frontend support/review)
Status: `Planned`  
Primary owner: Backend/DSP  
Frontend role: support + contract alignment

Taskovi:
1. Pripremiti UI contract checklist za domain schema:
   - expected macro IDs
   - style-mode control behavior
   - parameter display map (normalized -> display units)
2. Definirati popis UI binding točaka koje ovise o P1 freeze-u.
3. Ne implementirati runtime binding koji zaobilazi domain.

Output:
1. Kratki contract note za backend handoff review.

DoD:
1. Jasno definiran frontend input contract za P5.

## 3. P2 - DSP Core Primitives (Frontend scaffold only)
Status: `Planned`  
Primary owner: Backend/DSP  
Frontend role: scaffold

Taskovi:
1. Pripremiti UI skeleton bez hard wiringa na nestabilne parametre:
   - layout kostur
   - macro panel placeholder
   - style selector placeholder
2. Zadržati binding layer kao interface-only dok domain contract nije stabilan.

Output:
1. UI scaffold koji ne uvodi arhitekturalni bypass.

DoD:
1. Nema direktnog oslanjanja na ne-frozen backend parametre.

## 4. P3 - Osc/Filter/Nonlinear DSP (Frontend scaffold + feedback)
Status: `Planned`  
Primary owner: Backend/DSP  
Frontend role: scaffold + UX feedback

Taskovi:
1. Nastaviti makro-first layout iteracije.
2. Pripremiti mapu vizualnog feedbacka za:
   - macro modulation response
   - style mode state indicators
3. Predati backendu feedback na naming/range ergonomiju (bez mijenjanja constraints logike).

Output:
1. UX feedback note i update scaffold komponenata.

DoD:
1. UI ostaje unutar restriction-first filozofije.

## 5. P4 - Voice/Engine Orchestration (Frontend prep for integration)
Status: `Planned`  
Primary owner: Backend/DSP  
Frontend role: prep

Taskovi:
1. Pripremiti UI scenarije za testiranje:
   - legato/retrigger indikacije
   - style mode transition UX signalizacija
2. Dogovoriti s backendom što je finalni event/state surface za UI prikaz.

Output:
1. Integration checklist za P5.

DoD:
1. P5 integration zahtjevi spremni prije full implementacije.

## 6. P5 - App Wiring + Macro UI (Frontend primary phase)
Status: `Planned`  
Depends on: `P1 Done`, `P4 Done`

Taskovi:
1. Implementirati macro-first UI:
   - `src/ui/components/*`
   - `src/ui/layout/*`
   - `src/ui/bindings/*`
2. Integrirati app editor layer:
   - `src/app/PluginEditor.*`
   - `src/app/ParameterLayout.*` (UI mapping aspekt)
3. Osigurati da sve kontrole prolaze kroz domain-approved ranges i style behavior.
4. Implementirati smooth style-mode UX tranzicije (bez bypassa DSP/domain).

Output:
1. Funkcionalan frontend macro layer vezan na domain-sanctioned parametre.

DoD:
1. UI ne može postaviti out-of-domain vrijednosti.
2. Macro behavior je konzistentan s knowledge/rules dokumentima.
3. Predan handoff packet.

## 7. P6 - Preset/State/Migration (Frontend support)
Status: `Planned`  
Primary owner: Backend/DSP  
Frontend role: support

Taskovi:
1. Dodati UI sloj za preset/state workflow (bez mijenjanja serialization logike).
2. Validirati da UI ne remeti stable parameter IDs i automation mapping.
3. Pružiti UX fallback za unknown/legacy state slučajeve.

Output:
1. Stabilan preset UX sloj kompatibilan s backend migration logikom.

DoD:
1. Nema UI regressija kod load/save tokova.

## 8. P6.1 - Macro-10 Expansion + P7 Gate Closure (Frontend primary)
Status: `Planned`  
Depends on: `P6 Done`

Taskovi:
1. Uskladiti UI binding i surface za svih 10 makroa prema:
   - `docs/spec/p1_schema_freeze.md` (zaključana 4)
   - `docs/spec/macro_10_contract_proposal.md` (dodatnih 6)
2. Očuvati macro-first UX:
   - performance surface ostaje fokusirana na 4 primarna makroa
   - dodatnih 6 makroa izložiti kroz advanced sloj bez scope creepa
3. Zatvoriti frontend P6->P7 gate odstupanja:
   - `G-P6P7-004` (frontend scope)
4. Ako backend promijeni contract kroz P6.1:
   - uskladiti bindinge isključivo na canonical ID-jeve
   - bez runtime UI->DSP bypassa

Output:
1. Stabilan UI contract za svih 10 makroa.
2. Frontend dio gate backloga zatvoren.

DoD:
1. Svaki UI control mapiran na postojeći APVTS param ID.
2. Nema dead kontrola i nema domain bypassa.
3. Predan P6.1 handoff s binding mapom i dokazima.

## 9. P7 - QA + Render + Bench (Frontend QA)
Status: `Planned`  
Depends on: `P6.1 Done`

Taskovi:
1. Provesti UI QA scenarije:
   - macro automation handling
   - style mode switch UX
   - control range guard behavior
2. Implementirati stylized PNG komponente iz dizajn paketa:
   - source: `assets/ui/designer/p7/exports/png/`
   - runtime target: `assets/ui/runtime/p7/`
3. Verificirati da svaki implementirani asset postoji u dizajn manifestu.
4. Dodati/održati UI binding testove gdje su dostupni.
5. Dokumentirati UX edge-caseve i known limits.

Output:
1. Frontend QA note s ključnim nalazima.
2. `ui_control -> param_id -> asset_file` integration mapa.

DoD:
1. UI quality gate prolazi za MVP scope.
2. Nema missing/dead visual states za kontrole u scopeu.
3. Predan handoff packet.

## 10. P8 - CI/CD (Frontend support)
Status: `Planned`  
Primary owner: Orchestrator  
Frontend role: support
Detailed kickoff checklist: `docs/agent_briefs/frontend_ui_p8_kickoff_tasklist.md`

Taskovi:
1. Uskladiti frontend contract checks za CI:
   - canonical `param_id` provjera za UI binding layer
   - zabrana legacy ID referenci (`style.morph`)
2. Uskladiti asset integrity checks za CI:
   - runtime UI asseti moraju biti uskladeni s manifestom
   - bez missing/dead control stateova
3. Osigurati da CI capturea UI regressije koje su bile vidljive u DAW testu:
   - knob endpoint/value-arc korelacija
   - center visual panel layering (bez static/runtime overlapa)
4. Azurirati frontend QA evidence dokumente za MVP release candidate.
5. Predati P8 frontend handoff sa exact commandima i rezultatima.

DoD:
1. Frontend checkovi reproducibilni kroz CI.
2. Contract i asset checks prolaze bez manualnog overridea.
3. Predan handoff packet:
   - `docs/qa/frontend_phase_handoffs/P8_handoff.md`

## 11. Handoff packet format (obavezno po fazi)
Za svaku završenu fazu frontend agent mora predati:
1. Phase ID i status prijedlog (`In Progress -> Review`).
2. Točan popis promijenjenih datoteka.
3. Test command listu + rezultate.
4. Poznate limite / otvorena pitanja.
5. Potencijalni ADR prijedlog (ako je arhitektura mijenjana).

Preporučena lokacija:
- `docs/qa/frontend_phase_handoffs/<PHASE_ID>_handoff.md`
