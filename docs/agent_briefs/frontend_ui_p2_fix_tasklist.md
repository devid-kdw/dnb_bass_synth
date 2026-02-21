# Frontend/UI P2 Fix Tasklist (Conditional Alignment)

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
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/qa/p2_review.md`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/frontend_ui_agent_brief.md`
2. Potvrdi da radis samo u rootu.

## 2. Scope i cilj
P2 frontend nema blocker finding iz reviewa.  
Cilj je odraditi compatibility check nakon backend P2 fixa i napraviti samo nuzne korekcije ako backend contract promijeni UI assumptions.

## 3. Obavezni taskovi (conditional)
1. Re-validiraj da je frontend P2 scaffold i dalje u skladu sa pravilima:
   - 4 MVP macro placeholder kontrole (bez runtime binda)
   - style set: `Tech`, `Neuro`, `Dark`
   - nema direktnog UI -> DSP bypassa
2. Ako backend P2 fix ne mijenja schema/ID contract:
   - ne dirati runtime binding implementaciju
   - predati "no-change" handoff sa dokazom provjere
3. Ako backend P2 fix utjece na frontend contract:
   - napraviti minimalne korekcije samo za uskladivanje contracta
   - bez ulaska u P5 wiring

## 4. Zabranjeno
1. Nema rada izvan roota.
2. Nema bypassa `domain/ConstraintEngine`.
3. Nema uvodenja novih dependencyja.
4. Nema scope creepa prema general-purpose synth UI-u.
5. Nema prelaska na P5 implementaciju.

## 5. Verifikacija
1. Za scaffold-only izmjene:
   - build sanity check ako je potrebno (`cmake --build build --parallel`)
2. Dokumentirati rezultate provjere u handoffu.

## 6. Obavezni output
1. Handoff packet spremiti u:
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/qa/frontend_phase_handoffs/P2_handoff_fix.md`
2. Handoff mora sadrzavati:
   - je li bilo code changeova (`yes/no`)
   - changed files (ako postoje)
   - sto je provjereno i uskladeno
   - potvrdu da nema runtime bindinga na nestabilan backend contract
   - otvorena pitanja (ako postoje)
3. Predlozi status samo do `Review`.
