# Frontend/UI P6.1 Fix Tasklist

Last updated: 2026-02-22  
Root: `/Users/grzzi/Desktop/dnb_bass_synth`

## 1. Obavezno prije pocetka
1. Procitaj redom dokumente iz:
   - `docs/agent_briefs/frontend_ui_p6_1_fix_prompt.md`
2. Potvrdi da radis iskljucivo unutar root foldera.
3. Ovaj paket zatvara frontend scope nalaza:
   - `F-P6.1-003`
   - `G-P6P7-004` (frontend)

## 2. Scope i cilj
Cilj je uskladiti frontend P6.1 sa macro-first UX hijerarhijom i canonical Macro-10 binding contractom.

## 3. Obavezni taskovi
1. UX split (`F-P6.1-003`)
   - Uvedi primary/performance blok sa 4 zakljucana makroa.
   - Uvedi advanced blok sa preostalih 6 makroa.
   - Ne mijenjaj canonical ID-jeve.
2. Binding integrity (`G-P6P7-004` frontend)
   - Provjeri da svaki UI control ima APVTS param.
   - Ukloni dead kontrole ili dead binding reference.
   - Potvrdi da nema UI->DSP bypassa.
3. Handoff correction
   - Ispravi `docs/qa/frontend_phase_handoffs/P6_1_handoff.md` da bude factual.

## 4. Zabranjeno
1. Nema rada izvan roota.
2. Nema bypassa `domain/ConstraintEngine`.
3. Nema novih dependencyja.
4. Nema ulaska u P7/P8 scope.

## 5. Verifikacija (obavezno)
1. `tools/scripts/init_submodules.sh`
2. `cmake --build build --parallel`
3. `cd build && ctest --output-on-failure`
4. U handoffu navedi mapu: `ui_control | param_id | exists_in_apvts`.

## 6. Obavezni output
1. Handoff packet spremiti u:
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/qa/frontend_phase_handoffs/P6_1_handoff_fix.md`
2. Handoff mora sadrzavati:
   - status prijedlog (`Review -> Review`)
   - changed files
   - test komande + rezultat
   - closure map za trazene findinge
   - open issues (ako postoje)
3. Ne prelaziti na P7 bez potvrde orkestratora.
