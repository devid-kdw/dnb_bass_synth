# Frontend/UI P5 Fix Tasklist (Contract Alignment)

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
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/spec/p1_schema_freeze.md`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/qa/p5_review.md`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P5_handoff_fix.md` (ako postoji)
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/frontend_ui_agent_brief.md`
2. Potvrdi da radis samo u rootu.

## 2. Scope i cilj
Cilj je uskladiti frontend P5 output sa backend P5 contractom i zatvoriti UI-side gapove bez prelaska u P6.

## 3. Obavezni taskovi
1. Re-validate contract binding map
   - Validiraj da je svaki UI control bindan samo na canonical ID-jeve.
   - Ukloni/izbjegni binding na parametre koji nisu stabilni ili nisu u APVTS layoutu.
2. Style contract alignment
   - Ako backend P5 fix aktivira `style.mode`, uvedi/uskladi style mode kontrolu (Tech/Neuro/Dark) i binding.
   - `macro.style_morph` ostaje zaseban kontinuirani control, ne zamjenjuje canonical style mode contract.
3. Macro-first guard
   - Zadrzi 4 MVP macro kontrole kao primarni UX ulaz.
   - Ne otvaraj granularni general-purpose synth UI.
4. Runtime boundary guard
   - Potvrdi da nema UI->DSP bypassa.
   - Sve ide kroz APVTS/domain contract, bez ad-hoc runtime hookova.
5. Handoff quality
   - Ako backend contract nije promijenjen, predaj no-change ili doc-only handoff.
   - Ako je promijenjen, predaj minimalni code/doc patch bez scope creepa.

## 4. Zabranjeno
1. Nema rada izvan roota.
2. Nema bypassa `domain/ConstraintEngine`.
3. Nema uvodenja novih dependencyja.
4. Nema ulaska u P6/P7 feature scope.

## 5. Verifikacija
1. `tools/scripts/init_submodules.sh`
2. `cmake --build build --parallel`
3. `cd build && ctest --output-on-failure`
4. U handoffu explicitno potvrdi listu binding ID-jeva i njihovu prisutnost u APVTS layoutu.

## 6. Obavezni output
1. Handoff packet spremiti u:
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/qa/frontend_phase_handoffs/P5_handoff_fix.md`
2. Handoff mora sadrzavati:
   - je li bilo promjena (`yes/no`)
   - changed files (ako postoje)
   - tocno sto je uskladjeno sa backend P5 contractom
   - potvrdu da nema runtime bypassa i nestabilnog bindinga
   - otvorena pitanja (ako postoje)
3. Predlozi status samo do `Review`.
