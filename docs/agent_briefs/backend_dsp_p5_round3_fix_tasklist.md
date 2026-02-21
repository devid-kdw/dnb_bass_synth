# Backend/DSP P5 Round-3 Fix Tasklist (Final P5 Gate)

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
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P5_handoff_fix_round2.md`
2. Potvrdi da radis samo u rootu.
3. Ovaj fix paket zatvara nalaze: `F-P5R3-001`, `F-P5R3-002`, `F-P5R3-003`.

## 2. Scope i cilj
Cilj je finalno zatvoriti P5 gate bez laznog APVTS contracta i s dokazivim runtime ponasanjem.

## 3. Obavezni taskovi
1. APVTS contract inventory i cleanup (`F-P5R3-001`)
   - Enumeriraj sve aktivne APVTS parametre.
   - Za svaki parametar:
     - `wired`: ima runtime efekt i dokaz,
     - `deferred`: uklonjen iz aktivnog P5 layouta + razlog.
   - Nema dead/no-op host parametara.
2. `macro.roller_dynamics` audio-path closure (`F-P5R3-002`)
   - Osiguraj realan audio utjecaj u render pathu (ne samo domain vrijednosti).
   - Ne narusavati sub safety i restriction-first pristup.
3. Evidence tests (`F-P5R3-002`)
   - Dodaj test koji dokazuje audio output delta za `macro.roller_dynamics` (0.0 vs 1.0) pod istim kontroliranim uvjetima.
   - Odrzi/azuriraj style mode + style morph evidence testove.
4. Handoff integrity (`F-P5R3-003`)
   - Handoff mora imati evidence-backed inventory.
   - Bez netocnih tvrdnji tipa "wired" bez runtime puta i testa.

## 4. Zabranjeno
1. Nema rada izvan roota.
2. Nema bypassa `domain/ConstraintEngine`.
3. Nema uvodenja novih dependencyja.
4. Nema ulaska u P6/P7 scope.

## 5. Verifikacija (obavezno)
1. `tools/scripts/init_submodules.sh`
2. `cmake --build build --parallel`
3. `cd build && ctest --output-on-failure`
4. U handoffu explicitno potvrdi da APVTS inventory nema `dead/no-op`.

## 6. Obavezni output
1. Handoff packet spremiti u:
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P5_handoff_fix_round3.md`
2. Handoff mora sadrzavati:
   - Phase ID + predlozeni status transition (`Review -> Review`)
   - changed files (tocne putanje)
   - test komande + rezultat
   - closure map za `F-P5R3-001`, `F-P5R3-002`, `F-P5R3-003`
   - APVTS inventory: `param_id | status | code_path | test_evidence`
   - otvorena pitanja / ogranicenja
3. Stop nakon handoffa, bez prelaska na P6.
