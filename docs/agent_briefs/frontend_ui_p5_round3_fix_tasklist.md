# Frontend/UI P5 Round-3 Fix Tasklist (Final Contract Sync)

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
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/qa/p5_round3_review.md`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P5_handoff_fix_round3.md` (ako postoji)
2. Potvrdi da radis samo u rootu.

## 2. Scope i cilj
Cilj je finalni frontend contract sync za P5 gate bez scope creepa prema P6.

## 3. Obavezni taskovi
1. Binding map validation (`F-P5R3-001` frontend dio)
   - Provjeri svaki UI control bind:
     - canonical param ID
     - param ID postoji u aktivnom APVTS layoutu
   - Ukloni stale bindinge ako backend defera parametre.
2. Canonical MVP UX (`F-P5R3-003` frontend dio)
   - style labels: `Tech`, `Neuro`, `Dark`
   - macro panel: 4 canonical makra (`neuro_formant`, `fm_metal`, `roller_dynamics`, `liquid_depth`)
   - `macro.style_morph` ostaje odvojen control.
3. Boundary confirmation
   - nema direct UI->DSP bypassa
   - sve ide kroz APVTS/domain gate.
4. Conditional no-change path
   - ako backend Round-3 nije promijenio frontend-facing contract, predaj no-change/doc-only handoff.

## 4. Zabranjeno
1. Nema rada izvan roota.
2. Nema bypassa `domain/ConstraintEngine`.
3. Nema uvodenja novih dependencyja.
4. Nema ulaska u P6/P7 scope.

## 5. Verifikacija
1. `tools/scripts/init_submodules.sh`
2. `cmake --build build --parallel`
3. `cd build && ctest --output-on-failure`
4. U handoffu ukljuci tabelu: `ui_control | param_id | exists_in_apvts`.

## 6. Obavezni output
1. Handoff packet spremiti u:
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/qa/frontend_phase_handoffs/P5_handoff_fix_round3.md`
2. Handoff mora sadrzavati:
   - je li bilo promjena (`yes/no`)
   - changed files (ako postoje)
   - closure map za frontend dio `F-P5R3-001` i `F-P5R3-003`
   - potvrdu da nema runtime bypassa i nestabilnog bindinga
   - otvorena pitanja (ako postoje)
3. Predlozi status samo do `Review`.
