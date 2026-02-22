# Frontend/UI P6 Alignment Fix Tasklist

Last updated: 2026-02-22  
Root: `/Users/grzzi/Desktop/dnb_bass_synth`

## 1. Obavezno prije pocetka
1. Procitaj:
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/qa/p6_alignment_audit.md`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/master_implementation_plan.md`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/implementation_plan.md`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/project_rules.md`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/spec/p1_schema_freeze.md`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/spec/mvp_macro_contract.md` (ako postoji)
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/qa/frontend_phase_handoffs/P6_handoff.md`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P6_handoff_fix.md` (ako postoji)
   - sva 4 knowledge dokumenta iz `/knowledge`
2. Potvrdi da radis iskljucivo unutar root foldera.
3. Ovaj paket zatvara: `F-P6A-004` (frontend dio) i `F-P6A-005` (frontend dio).

## 2. Scope i cilj
Cilj je uskladiti UI contract i P6 dokumentaciju sa backend fixevima i canonical MVP pravilima.

## 3. Obavezni taskovi
1. Zatvori `F-P6A-005` (frontend handoff integrity)
   - Ispravi P6 handoff tvrdnje tako da koriste canonical naming (`Tech`, `Neuro`, `Dark`).
   - Ukloni neprecizne ili neprovjerljive tvrdnje.
2. Zatvori `F-P6A-004` (frontend macro contract alignment)
   - Ako backend isporuci puni MVP macro contract (`Path A`):
     - uskladi UI surfaces/bindinge s canonical macro contractom
     - nema dead UI controla i nema bypassa prema DSP-u
   - Ako backend isporuci ADR defer (`Path B`):
     - ne uvoditi lazne UI affordance
     - uskladiti frontend dokumentaciju s defer odlukom i granicama
3. Potvrdi da P5/P6 boundary pravila ostaju:
   - macro-first ostaje primaran
   - restriction-first ostaje primaran
   - nema runtime UI->DSP bypassa
4. Ako backend fix ne mijenja frontend-facing contract:
   - predaj no-change ili doc-only handoff.

## 4. Zabranjeno
1. Nema rada izvan roota.
2. Nema bypassa `domain/ConstraintEngine`.
3. Nema neodobrenih dependencyja.
4. Nema ulaska u P7/P8 scope.

## 5. Verifikacija (obavezno)
1. `tools/scripts/init_submodules.sh`
2. `cmake --build build --parallel`
3. `cd build && ctest --output-on-failure`
4. U handoffu navedi binding mapu: `ui_control | param_id | exists_in_apvts`.

## 6. Obavezni output
1. Handoff packet spremiti u:
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/qa/frontend_phase_handoffs/P6_handoff_fix.md`
2. Handoff mora sadrzavati:
   - status transition prijedlog (`Review -> Review`)
   - je li bilo code/doc changeova
   - changed files (ako postoje)
   - closure map za frontend dio `F-P6A-004`, `F-P6A-005`
   - potvrdu da nema runtime bypassa i nestabilnog bindinga
3. Ne prelaziti na P7 bez potvrde orkestratora.

