# Frontend/UI P5 Round-2 Fix Tasklist (Contract Alignment)

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
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/qa/p5_round2_review.md`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P5_handoff_fix_round2.md` (ako postoji)
2. Potvrdi da radis samo u rootu.

## 2. Scope i cilj
Cilj je zatvoriti frontend dio P5 Round-2 nalaza bez scope creepa prema P6.

## 3. Obavezni taskovi
1. Binding contract provjera
   - Validiraj da svaki UI control binda samo canonical i aktivne APVTS param ID-jeve.
   - Ukloni stale bindings ako backend defera odredene parametre.
2. Canonical style naming
   - Uskladi style UI naming na:
     - `Tech`
     - `Neuro`
     - `Dark`
3. Canonical macro MVP set
   - UI macro panel mora imati 4 makro kontrole:
     - `macro.neuro_formant`
     - `macro.fm_metal`
     - `macro.roller_dynamics`
     - `macro.liquid_depth`
   - `macro.style_morph` ostaje zaseban control i ne zamjenjuje ove 4.
4. Boundary discipline
   - Potvrdi da nema direct UI->DSP bypassa.
   - Sve ide kroz APVTS/domain contract.

## 4. Zabranjeno
1. Nema rada izvan roota.
2. Nema bypassa `domain/ConstraintEngine`.
3. Nema uvodenja novih dependencyja.
4. Nema ulaska u P6/P7 scope.

## 5. Verifikacija
1. `tools/scripts/init_submodules.sh`
2. `cmake --build build --parallel`
3. `cd build && ctest --output-on-failure`
4. U handoffu navedi mapu: `ui_control -> param_id -> exists_in_apvts(yes/no)`.

## 6. Obavezni output
1. Handoff packet spremiti u:
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/qa/frontend_phase_handoffs/P5_handoff_fix_round2.md`
2. Handoff mora sadrzavati:
   - je li bilo promjena (`yes/no`)
   - changed files (ako postoje)
   - sto je uskladjeno sa backend P5 Round-2 contractom
   - closure map za `F-P5R2-003` frontend dio
   - potvrdu da nema runtime bypassa i nestabilnog bindinga
   - otvorena pitanja (ako postoje)
3. Predlozi status samo do `Review`.
