# TechStack/Repo Alignment Fix Tasklist (F-ALIGN-002, F-ALIGN-003)

Last updated: 2026-02-21  
Root: `/Users/grzzi/Desktop/dnb_bass_synth`

## 1. Obavezno prije pocetka
1. Procitaj:
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/qa/alignment_remediation_review.md`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/qa/alignment_handoffs/ALIGN_D002_D003_handoff.md`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/master_implementation_plan.md`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/project_rules.md`
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/techstack_repo_agent_brief.md`
   - `/Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx`
   - `/Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx`
2. Potvrdi rad iskljucivo u root folderu.

## 2. Scope i cilj
Zatvoriti odstupanja:
- `F-ALIGN-002` (submodule model nije pinan u indexu)
- `F-ALIGN-003` (tests CMake default fallback na `_deps`)

## 3. Obavezni taskovi (F-ALIGN-002)
1. Dependency model:
   - Zadrzi `.gitmodules` i `tools/scripts/init_submodules.sh` kao canonical bootstrap.
   - Osiguraj da submodule pathovi budu stvarno pinani kao gitlink entries (`mode 160000`) u repo indexu.
   - Ukloni oslanjanje na `extern/.gitkeep` kao jedini tracked extern artefakt.
2. CMake alignment:
   - Zadrzi CMake baseline uskladen s tech stack arhitekturom.
   - Ne uvoditi `FetchContent`.
   - Ne uvoditi skriveni dependency fallback koji maskira neinicijalizirane submodule.

## 4. Obavezni taskovi (F-ALIGN-003)
1. `tests/CMakeLists.txt`
   - Ukloni default fallback granu koja koristi `${CMAKE_BINARY_DIR}/_deps/catch2-src`.
   - Default path mora biti:
     - koristi `extern/catch2` ako postoji
     - inace `FATAL_ERROR` s jasnom porukom da treba pokrenuti `tools/scripts/init_submodules.sh`
2. Ako je potreban compatibility fallback:
   - dozvoli ga samo kroz eksplicitan CMake flag (OFF po defaultu).
   - mora biti jasno dokumentiran kao privremeni compatibility mode.
3. `D-003` ADR baseline je vec zatvoren:
   - ne otvarati nove ADR izmjene osim minimalne korekcije formatiranja ako je nuzno.

## 5. Zabranjeno
1. Nema mijenjanja DSP algoritama (`src/dsp/`) u ovom tasku.
2. Nema UI scope creepa.
3. Nema izlaska izvan root foldera.

## 6. Verifikacija
1. `tools/scripts/init_submodules.sh`
2. `git submodule status`
3. `git ls-files --stage`:
   - potvrdi `160000` gitlink entries za trazene `extern/*` submodule pathove.
4. clean configure:
   - `cmake -S . -B build_clean_alignment_fix -DDNB_ENABLE_PLUGIN_TARGET=ON -DDNB_BUILD_TESTS=ON -DDNB_BUILD_BENCH=ON`
5. build + test:
   - `cmake --build build --parallel`
   - `cd build && ctest --output-on-failure`
6. policy grep check:
   - potvrdi da nema aktivnog `_deps/catch2-src` default puta u tests CMake.
   - potvrdi da `FetchContent` nije aktivan dependency mehanizam.

## 7. Obavezni output
1. Handoff packet spremiti u:
   - `/Users/grzzi/Desktop/dnb_bass_synth/docs/qa/alignment_handoffs/ALIGN_D002_D003_handoff_fix.md`
2. Handoff mora sadrzavati:
   - changed files
   - test komande + rezultat
   - closure map za `F-ALIGN-002`, `F-ALIGN-003`
   - dokaz submodule pinninga (`git submodule status` + `git ls-files --stage` excerpt)
   - otvorena pitanja / ogranicenja
3. Predlozi status samo do `Review`.
