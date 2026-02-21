# Frontend/UI Tasklist po Fazama

Last updated: 2026-02-21  
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
2. Potvrdi da radiš isključivo unutar root foldera.
3. Provjeri u `docs/master_implementation_plan.md` koja je aktivna ili prva `Planned` faza relevantna za frontend.

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

## 8. P7 - QA + Render + Bench (Frontend QA)
Status: `Planned`  
Depends on: `P6 Done`

Taskovi:
1. Provesti UI QA scenarije:
   - macro automation handling
   - style mode switch UX
   - control range guard behavior
2. Dodati/održati UI binding testove gdje su dostupni.
3. Dokumentirati UX edge-caseve i known limits.

Output:
1. Frontend QA note s ključnim nalazima.

DoD:
1. UI quality gate prolazi za MVP scope.
2. Predan handoff packet.

## 9. P8 - CI/CD (Frontend support)
Status: `Planned`  
Primary owner: Orchestrator  
Frontend role: support

Taskovi:
1. Pomoć pri integraciji UI build/test checkova u CI.
2. Verificirati da CI pokriva frontend binding regressije.

DoD:
1. Frontend checkovi reproducibilni kroz CI.

## 10. Handoff packet format (obavezno po fazi)
Za svaku završenu fazu frontend agent mora predati:
1. Phase ID i status prijedlog (`In Progress -> Review`).
2. Točan popis promijenjenih datoteka.
3. Test command listu + rezultate.
4. Poznate limite / otvorena pitanja.
5. Potencijalni ADR prijedlog (ako je arhitektura mijenjana).

Preporučena lokacija:
- `docs/qa/frontend_phase_handoffs/<PHASE_ID>_handoff.md`
