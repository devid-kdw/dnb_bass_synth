# ADR 005: P1 Test Dependency Strategy (FetchContent vs Git Submodule)

## Kontekst
Tijekom P1 (Domain Constraint Core) implementacije, za validaciju izolirane domenske logike dodani su `Catch2` unit testovi. Trenutno arhitektonsko ograničenje iz TechStack dokumenta (`Docs/knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx`) preferira kontrolirano korištenje dependencyja preko `/extern` foldera koristeći git submodules (kako bi se osigurao potpuni source kod kod buildanja na izoliranim CI workerima).
Međutim, testovi su trenutno u konfiguraciji u `tests/CMakeLists.txt` iskoristili `FetchContent` opciju za `Catch2` umjesto preporučenog repozitorijskog submodula.

## Odluka
Za P1 fazu ograničenog dometa i brzine (unit testovi bez audio rendera) odobrava se `FetchContent` za `Catch2`.

## Posljedice
- **Prednosti:** P1 testovi se brzo pokreću i ne zahtijevaju od korisnika inicijalizaciju novog submodula sada dok traje zamrzavanje ugovora. Nema smetnje za provjeru P1 koda.
- **Nedostaci:** Manje determinizma u slučaju nestanka CMake server linkova prilikom obimnih buildanja unutar CI/CD-a (rješava P8) i duži "clean build" u početku.

## Prijelazni plan (Migration Plan)
Prije završetka **P2 (DSP Core Primitives)** ili najkasnije **P7 (QA + Render + Bench)**, ovaj dependency će biti migriran na službeni `extern/catch2` submodul sukladno izvornom TechStack pravilu, eliminirajući daljnju potrebu za on-the-fly fetch mehanizmom u CI pipelineu.
