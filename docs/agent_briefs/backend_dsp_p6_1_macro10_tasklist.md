# Backend/DSP P6.1 Macro-10 Tasklist

Last updated: 2026-02-22  
Root: `/Users/grzzi/Desktop/dnb_bass_synth`

## 1. Obavezno prije pocetka
1. Procitaj dokumente redom iz:
   - `docs/agent_briefs/backend_dsp_p6_1_macro10_kickoff_prompt.md`
2. Potvrdi da radis iskljucivo unutar root foldera.
3. Potvrdi da zatvaras ovaj backend deviation scope:
   - `G-P6P7-002`
   - `G-P6P7-003`
   - `G-P6P7-004` (backend)
   - `G-P6P7-005` (backend)

## 2. Scope i cilj
Cilj P6.1 backend paketa je aktivirati svih 10 makroa bez dead parametara i pripremiti backend evidence za P7 gate.

## 3. Obavezni taskovi
1. Macro-10 backend contract
   - Odrzi zaključanih 4 makroa iz `docs/spec/p1_schema_freeze.md`.
   - Dodaj 6 novih makroa iz `docs/spec/macro_10_contract_proposal.md`.
2. Domain + APVTS + runtime wiring
   - Svaki novi macro mora imati canonical param ID.
   - Svaki macro mora imati domain map + style clamp + runtime effect.
3. Test pokrivenost
   - Dodaj testove za domain mapping.
   - Dodaj testove za style-limited behavior (`Tech`, `Neuro`, `Dark`).
   - Dodaj runtime effect evidence testove (bez fake/no-op prolaza).
4. Deviation fix: `G-P6P7-002`
   - Ispravi backend P6 handoff wording i verification command evidence.
5. Deviation fix: `G-P6P7-003`
   - Uskladi plugin version tag sa jednim source-of-truth mehanizmom.
   - Dodaj test za version consistency payloada.
6. Deviation fix: `G-P6P7-005` (backend dio)
   - Ako je Macro-10 aktiviran, pripremi ADR izmjenu/supersede za defer odluku.

## 4. Zabranjeno
1. Nema rada izvan roota.
2. Nema bypassa `domain/ConstraintEngine`.
3. Nema novih dependencyja bez odobrenja.
4. Nema ulaska u P7/P8 feature scope.

## 5. Verifikacija (obavezno)
1. `tools/scripts/init_submodules.sh`
2. `cmake --build build --parallel`
3. `cd build && ctest --output-on-failure`
4. `cd build && ctest --output-on-failure -R Preset`
5. U handoffu obavezno prilozi `macro evidence map`.

## 6. Obavezni output
1. Handoff packet spremiti u:
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P6_1_handoff.md`
2. Handoff mora sadrzavati:
   - status prijedlog (`In Progress -> Review`)
   - changed files
   - test komande + rezultat
   - closure map za `G-P6P7-002`, `G-P6P7-003`, `G-P6P7-004` (backend), `G-P6P7-005` (backend)
   - macro evidence mapu
   - open issues/risks (ako postoje)
3. Ne prelaziti na P7 bez potvrde orkestratora.
