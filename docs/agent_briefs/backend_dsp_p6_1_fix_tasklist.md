# Backend/DSP P6.1 Fix Tasklist

Last updated: 2026-02-22  
Root: `/Users/grzzi/Desktop/dnb_bass_synth`

## 1. Obavezno prije pocetka
1. Procitaj redom dokumente iz:
   - `docs/agent_briefs/backend_dsp_p6_1_fix_prompt.md`
2. Potvrdi da radis iskljucivo unutar root foldera.
3. Ovaj paket zatvara backend scope nalaza:
   - `F-P6.1-001`
   - `F-P6.1-002`
   - `F-P6.1-004`
   - `G-P6P7-002`
   - `G-P6P7-003`

## 2. Scope i cilj
Cilj je uskladiti backend P6.1 implementaciju sa Macro-10 contractom i zatvoriti evidence/gate nedostatke prije P7.

## 3. Obavezni taskovi
1. FM Pressure style alignment (`F-P6.1-001`)
   - Uskladi style cap logiku za `macro.fm_pressure` prema `Tech < Neuro < Dark`.
   - Ne smije biti Dark-only aktivacija.
   - Nadogradi unit testove za style progression evidence.
2. Domain clamp closure (`F-P6.1-002`)
   - Dodaj finalni `filterCutoff` clamp nakon svih macro utjecaja u `ConstraintEngine`.
3. Handoff evidence correction (`F-P6.1-004`, `G-P6P7-002`)
   - Ispravi `docs/qa/backend_phase_handoffs/P6_handoff.md`:
     - command mora biti `ctest -R Preset`
     - schema/wrapper wording mora biti factual.
4. Plugin version source-of-truth (`G-P6P7-003`)
   - Ukloni hardcoded drift rizik za `plugin_version`.
   - Dodaj test koji dokazivo provjerava sinkronizaciju source-of-truth -> payload.
5. Handoff cleanup
   - Ispravi `docs/qa/backend_phase_handoffs/P6_1_handoff.md` gdje postoje netocne tvrdnje.

## 4. Zabranjeno
1. Nema rada izvan roota.
2. Nema bypassa `domain/ConstraintEngine`.
3. Nema novih dependencyja.
4. Nema scope creepa prema P7/P8.

## 5. Verifikacija (obavezno)
1. `tools/scripts/init_submodules.sh`
2. `cmake --build build --parallel`
3. `cd build && ctest --output-on-failure`
4. `cd build && ctest --output-on-failure -R Preset`
5. U handoffu navedi `finding_id -> changed_file -> test_evidence`.

## 6. Obavezni output
1. Handoff packet spremiti u:
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P6_1_handoff_fix.md`
2. Handoff mora sadrzavati:
   - status prijedlog (`Review -> Review`)
   - changed files
   - test komande + rezultat
   - closure map za trazene findinge
   - open issues (ako postoje)
3. Ne prelaziti na P7 bez potvrde orkestratora.
