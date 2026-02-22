# Backend/DSP P6 Alignment Fix Tasklist

Last updated: 2026-02-22  
Root: `/Users/grzzi/Desktop/dnb_bass_synth`

## 1. Obavezno prije pocetka
1. Procitaj:
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/qa/p6_alignment_audit.md`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/master_implementation_plan.md`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/implementation_plan.md`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/project_rules.md`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/spec/p1_schema_freeze.md`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P6_handoff.md`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/qa/frontend_phase_handoffs/P6_handoff.md`
   - sva 4 knowledge dokumenta iz `/knowledge`
2. Potvrdi da radis iskljucivo unutar root foldera.
3. Ovaj paket zatvara: `F-P6A-001`, `F-P6A-002`, `F-P6A-003`, `F-P6A-004` (backend dio), `F-P6A-005` (backend dio).

## 2. Scope i cilj
Cilj je zatvoriti P6 alignment odstupanja bez krsenja domain gate i RT-safe pravila.

## 3. Obavezni taskovi
1. Zatvori `F-P6A-001` (JSON migration layer)
   - U `src/preset/*` uvedi eksplicitan JSON-backed migration sloj uskladjen s tech stack zahtjevom (ValueTree + JSON migration).
   - Odrzi kompatibilnost s postojecim state payloadom.
2. Zatvori `F-P6A-002` (plugin version tag)
   - Dodaj plugin-version oznaku u state payload uz schema version.
   - Implementiraj deterministic load ponašanje kad version tag nedostaje.
3. Zatvori `F-P6A-003` (unknown-field test gap)
   - Dodaj dedicated test scenarije:
     - unknown param id
     - unknown extra node/field
     - potvrda da nema crasha i da se poznati parametri ispravno ucitavaju
4. Zatvori `F-P6A-004` (macro target drift)
   - Napravi canonical MVP macro contract dokument:
     - `docs/spec/mvp_macro_contract.md`
     - izvuci tocna imena/ID-jeve iz knowledge dokumenata (bez izmisljanja)
   - Zatim odaberi i implementiraj jednu closure strategiju:
     - `Path A (preporuceno)`: implementirati puni MVP macro contract i runtime wiring bez dead/no-op host parametara.
     - `Path B (dozvoljeno samo ako A nije izvediv u ovom patchu)`: ADR + explicit defer plan, azuriran master plan/risk, i jasna oznaka da MVP makro cilj jos nije zatvoren.
5. Zatvori `F-P6A-005` (backend handoff integrity)
   - Ispravi netocne ili neprovjerljive tvrdnje u backend P6 handoffu.
   - Predaj novi handoff s closure mapom i dokazima.

## 4. Zabranjeno
1. Nema rada izvan roota.
2. Nema bypassa `domain/ConstraintEngine`.
3. Nema novih neodobrenih dependencyja.
4. Nema scope creepa prema P7/P8 feature implementaciji.

## 5. Verifikacija (obavezno)
1. `tools/scripts/init_submodules.sh`
2. `cmake --build build --parallel`
3. `cd build && ctest --output-on-failure`
4. `cd build && ctest --output-on-failure -R preset`
5. U handoffu ukljuci mapu: `finding_id -> closure_evidence`.

## 6. Obavezni output
1. Handoff packet spremiti u:
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P6_handoff_fix.md`
2. Handoff mora sadrzavati:
   - predlozeni status transition (`Review -> Review`)
   - changed files
   - test komande + rezultat
   - closure map za `F-P6A-001`..`F-P6A-005` (backend scope)
   - migration matricu (`from_version -> to_version -> rezultat`)
   - open questions/risks (ako postoje)
3. Ne prelaziti na P7 bez potvrde orkestratora.

