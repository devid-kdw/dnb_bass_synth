# TechStack/Repo Alignment Fix Prompt (F-ALIGN-002, F-ALIGN-003) (Copy/Paste)

```text
TI SI TECHSTACK/REPO AGENT ZA DnB Bass Synth VST3.

RADNI ROOT:
/Users/grzzi/Desktop/dnb_bass_synth

TASK: P4-gate alignment remediation za zatvaranje nalaza `F-ALIGN-002` i `F-ALIGN-003`.

OBAVEZNO PROCI TAJ REDOSLIJED DOKUMENATA:
1) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/alignment_remediation_review.md
2) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/alignment_handoffs/ALIGN_D002_D003_handoff.md
3) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/techstack_repo_alignment_tasklist.md
4) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/techstack_repo_agent_brief.md
5) /Users/grzzi/Desktop/dnb_bass_synth/docs/master_implementation_plan.md
6) /Users/grzzi/Desktop/dnb_bass_synth/docs/project_rules.md
7) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx
8) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx
9) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB bass synth document for developer.pdf
10) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB Bass Synth VST Plugin Research.pdf

OBAVEZNE IZMJENE:
1) Zatvori `F-ALIGN-002`:
   - osiguraj da extern submodules nisu samo deklarirani nego i pinani kao gitlink entries u repo indexu.
   - potvrdi da su trazeni extern moduli pokriveni kroz `.gitmodules` i `tools/scripts/init_submodules.sh`.
2) Zatvori `F-ALIGN-003`:
   - ukloni implicitni fallback na `${CMAKE_BINARY_DIR}/_deps/catch2-src` iz aktivnog tests patha.
   - default ponasanje mora biti strict submodule-first (fail ako `extern/catch2` nije inicijaliziran).
   - opcionalni compatibility fallback je dozvoljen samo iza eksplicitnog OFF-by-default CMake flaga.
3) Ne otvaraj novi scope:
   - `D-003` (ADR baseline) je vec zatvoren; ne raditi nove ADR promjene osim minimalnih korekcija tipfelera/formata.

OGRANICENJA:
- Ne radi izvan root foldera.
- Ne mijenjaj DSP algoritme (`src/dsp/`) u ovom tasku.
- Ne ulazi u P4/P5 feature implementaciju.
- Ne uvodi neodobrene dependencyje bez obrazlozenja.

OBAVEZNA VERIFIKACIJA:
1) `tools/scripts/init_submodules.sh`
2) `git submodule status`
3) `git ls-files --stage` mora pokazati gitlink (`160000`) za trazene `extern/*` submodule pathove
4) clean configure:
   - `cmake -S . -B build_clean_alignment_fix -DDNB_ENABLE_PLUGIN_TARGET=ON -DDNB_BUILD_TESTS=ON -DDNB_BUILD_BENCH=ON`
5) build + test:
   - `cmake --build build --parallel`
   - `cd build && ctest --output-on-failure`
6) policy check:
   - potvrdi da `FetchContent` nije aktivan test dependency path
   - potvrdi da `_deps/catch2-src` fallback nije aktivan po defaultu

OBAVEZNI OUTPUT:
1) Handoff packet u:
   /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/alignment_handoffs/ALIGN_D002_D003_handoff_fix.md
2) U handoffu navedi:
   - changed files
   - test komande + rezultat
   - closure map za `F-ALIGN-002`, `F-ALIGN-003`
   - otvorena pitanja (ako postoje)
3) Predlozi status samo do `Review`.
```
