# Pre-P4 Knowledge Alignment Audit

Date: 2026-02-21  
Reviewer: Orchestrator

## 1. Scope and Method
Audit cilj: provjera uskladjenosti trenutnog stanja projekta sa 4 knowledge dokumenta prije pokretanja P4.

Pregledani izvori istine:
1. `knowledge/DNB Bass Synth VST Plugin Research.pdf`
2. `knowledge/DNB bass synth document for developer.pdf`
3. `knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx`
4. `knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx`

Za trazenje i citiranje koristeni su ekstrakti:
- `docs/qa/knowledge_extract/knowledge_pdf_extract.txt`
- `docs/qa/knowledge_extract/knowledge_docx_extract.txt`

## 2. Alignment Summary

### 2.1 Aligned
1. Restriction-first i DnB-specific scope je zadrzan (nema general-synth drift).
2. Domain constraints (sub phase lock value, xover range, FM curated set, OTT cap) su implementirani u:
   - `src/domain/DnBLimits.h`
   - `src/domain/ConstraintEngine.cpp`
3. P3 compile blockeri iz prethodnog reviewa su zatvoreni i test coverage je prosiren (`17/17` tests pass).

### 2.2 Controlled Deviations (documented)
1. MVP style set je trenutno zamrznut na `Tech/Neuro/Dark` i dodatni style modovi su deferani kroz schema freeze:
   - `docs/spec/p1_schema_freeze.md:32`
2. P1 macro contract je trenutno 4 canonical makroa, sa 10 target u P5:
   - `docs/spec/p1_schema_freeze.md:43`

Ovo je dokumentirano i trenutno nije neautorizirani drift.

## 3. Critical Deviations (must-fix)

### D-001 (Critical): Oversampling implementation is still placeholder, not polyphase FIR/HIIR
Knowledge requirement:
- per-module OS + polyphase FIR + HIIR recommendation
  - `docs/qa/knowledge_extract/knowledge_docx_extract.txt:370`
  - `docs/qa/knowledge_extract/knowledge_docx_extract.txt:423`
  - `docs/qa/knowledge_extract/knowledge_docx_extract.txt:470`

Current state:
- `src/dsp/core/Oversampler.h:31` placeholder upsample
- `src/dsp/core/Oversampler.h:44` simple decimation downsample

Impact:
- P3 nonlinear modules (FM/wavefolder/saturator path) nisu na kvaliteti trazenoj u knowledge dokumentima.

### D-002 (High): Tech stack dependency model significantly diverges from defined architecture
Knowledge requirement:
- extern submodule model and CMake plugin wiring
  - `docs/qa/knowledge_extract/knowledge_docx_extract.txt:1944`
  - `docs/qa/knowledge_extract/knowledge_docx_extract.txt:2378`
  - `docs/qa/knowledge_extract/knowledge_docx_extract.txt:2400`

Current state:
- `extern/` je prazan (`extern/.gitkeep` only)
- `.gitmodules` ne postoji
- top-level CMake nema JUCE/plugin target:
  - `CMakeLists.txt:1`
- test deps su i dalje `FetchContent`:
  - `tests/CMakeLists.txt:3`

Impact:
- projekt trenutno ne slijedi finalni dependency/target model iz tech stack dokumenta.

### D-003 (High): ADR baseline from tech stack is incomplete
Knowledge requirement:
- inicijalni ADR paket (JUCE odluka, per-module OS, domain gate, CLAP passive)
  - `docs/qa/knowledge_extract/knowledge_docx_extract.txt:2603`
  - `docs/qa/knowledge_extract/knowledge_docx_extract.txt:2612`

Current state:
- prisutan je samo:
  - `docs/adr/ADR-005-P1-Test-Dependency.md`

Impact:
- arhitekturne odluke iz knowledge baze nisu formalno dokumentirane u repou kako je propisano.

## 4. Non-blocking / Phase-Pending Items
1. Engine orchestration i note management (P4 scope) jos nije implementiran:
   - `src/engine/.gitkeep`
2. App/plugin wiring (`PluginProcessor`, `PluginEditor`, APVTS layout) jos nije implementiran (P5 scope):
   - `src/app/.gitkeep`

Ovo je u skladu s faznim planom i nije samo po sebi drift.

## 5. Pre-P4 Gate Decision
Verdict: **NO-GO za "bez odstupanja" kriterij**.

Razlog:
1. D-001 (oversampling kvalitet) je direktan konflikt s DSP supplement/tech stack smjernicama.
2. D-002 i D-003 su strukturni konflikti s tech stack dokumentom.

P4 se moze pokrenuti samo ako prihvatimo da postoje odstupanja; za strogi kriterij "ne smije biti odstupanja", potrebno je prvo zatvoriti D-001/D-002/D-003.
