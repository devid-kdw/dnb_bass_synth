# Frontend/UI P6.1 Macro-10 Tasklist

Last updated: 2026-02-22  
Root: `/Users/grzzi/Desktop/dnb_bass_synth`

## 1. Obavezno prije pocetka
1. Procitaj dokumente redom iz:
   - `docs/agent_briefs/frontend_ui_p6_1_macro10_kickoff_prompt.md`
2. Potvrdi da radis iskljucivo unutar root foldera.
3. Potvrdi da zatvaras ovaj frontend deviation scope:
   - `G-P6P7-004` (frontend)

## 2. Scope i cilj
Cilj P6.1 frontend paketa je uskladiti UI na puni Macro-10 contract bez krsenja architecture boundary pravila.

## 3. Obavezni taskovi
1. Performance + advanced macro surface
   - Zadrzi 4 postojeća makroa kao primarni performance sloj.
   - Dodaj 6 novih macro kontrola kroz advanced sloj.
2. Canonical binding contract
   - Koristi samo canonical param ID-jeve.
   - Svaki UI control mora mapirati na postojeci APVTS param.
3. Deviation fix: `G-P6P7-004` (frontend dio)
   - Ukloni dead kontrolne putanje.
   - Potvrdi da nema runtime UI->DSP bypassa.
4. Dokumentacija/handoff integrity
   - Predaj tocan binding map i closure evidence u P6.1 handoffu.

## 4. Zabranjeno
1. Nema rada izvan roota.
2. Nema bypassa `domain/ConstraintEngine`.
3. Nema neodobrenih dependencyja.
4. Nema scope creepa prema P7/P8.

## 5. Verifikacija (obavezno)
1. `tools/scripts/init_submodules.sh`
2. `cmake --build build --parallel`
3. `cd build && ctest --output-on-failure`
4. U handoffu navedi mapu: `ui_control | param_id | exists_in_apvts`.

## 6. Obavezni output
1. Handoff packet spremiti u:
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/qa/frontend_phase_handoffs/P6_1_handoff.md`
2. Handoff mora sadrzavati:
   - status prijedlog (`In Progress -> Review`)
   - je li bilo code/doc promjena
   - changed files
   - closure map za `G-P6P7-004` (frontend)
   - binding map evidence
   - open issues/risks (ako postoje)
3. Ne prelaziti na P7 bez potvrde orkestratora.
