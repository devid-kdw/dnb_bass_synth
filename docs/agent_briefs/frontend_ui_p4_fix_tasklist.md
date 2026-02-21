# Frontend/UI P4 Fix Tasklist (Conditional Sync)

Last updated: 2026-02-21  
Root: `/Users/grzzi/Desktop/dnb_bass_synth`

## 1. Obavezno prije pocetka
1. Procitaj:
   - `/Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB Bass Synth VST Plugin Research.pdf`
   - `/Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB bass synth document for developer.pdf`
   - `/Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx`
   - `/Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/project_rules.md`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/master_implementation_plan.md`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/qa/p4_review.md`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/frontend_ui_agent_brief.md`
2. Potvrdi da radis samo u rootu.

## 2. Scope i cilj
P4 frontend fix je conditional sync faza.  
Cilj je uskladiti frontend integration checklist s backend P4 remediation contractom bez ulaska u P5 runtime implementation.

## 3. Obavezni taskovi (conditional)
1. Re-validiraj P4 frontend ogranicenja:
   - nema runtime UI->DSP bypassa
   - nema direct binda na nestabilan backend contract
   - macro-first/restriction-first ostaje netaknut
2. Ako backend P4 fix ne mijenja frontend-facing state surface:
   - predaj "no-change" handoff sa dokazom provjere
3. Ako backend P4 fix mijenja state surface (npr. style morph progress API naming):
   - napravi minimalne dokumentacijske korekcije u:
     - `docs/qa/frontend_p4_integration_checklist.md`
   - bez kodnog runtime wiringa

## 4. Zabranjeno
1. Nema rada izvan roota.
2. Nema bypassa `domain/ConstraintEngine`.
3. Nema uvodenja novih dependencyja.
4. Nema scope creepa prema P5 implementaciji.

## 5. Verifikacija
1. Dokumentiraj tocan backend contract koji je provjeren (iz `P4_handoff_fix`).
2. Potvrdi da frontend output ne uvodi runtime binding prije P5.
3. Ako je bilo izmjena, provedi minimalan build sanity check:
   - `cmake --build build --parallel` (samo ako izmjene diraju build-relevantne fajlove)

## 6. Obavezni output
1. Handoff packet spremiti u:
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/qa/frontend_phase_handoffs/P4_handoff_fix.md`
2. Handoff mora sadrzavati:
   - je li bilo promjena (`yes/no`)
   - changed files (ako postoje)
   - sto je provjereno i uskladeno
   - potvrdu da nema runtime UI bindinga na nestabilan contract
   - otvorena pitanja (ako postoje)
3. Predlozi status samo do `Review`.
