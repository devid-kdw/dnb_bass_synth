# Handoff Packet: Phase 1 (Domain Constraint Core)

**Phase ID**: P1
**Status Transition**: Planned -> Review

## 1. Popis promijenjenih datoteka
- `CMakeLists.txt` (osnovno omogućavanje testova)
- `tests/CMakeLists.txt` (uključivanje Catch2 preko FetchContent-a)
- `src/domain/DnBLimits.h` (ograničenja parametarskog domena specifična za DnB)
- `src/domain/ParameterSpec.h` (specifikacija i identifikatori parametara za UI)
- `src/domain/StyleMode.h` (definicija stilova i ograničenja zvuka prema podžanru)
- `src/domain/MacroMap.h` (mapiranje 0.0-1.0 vrijednosti makroa na interne metaparametre prikladne žanru)
- `src/domain/ConstraintEngine.h` (glavni mehanizam osiguranja granica te pretvaranja UI ulaza u RT-sigurna DSP ograničenja)
- `src/domain/ConstraintEngine.cpp` (implementacija mehanizma normalizacije domene)
- `tests/unit/test_parameter_ranges.cpp` (Catch2 unit test za granice envelopa/xovera i fixnu fazu)
- `tests/unit/test_macro_constraints.cpp` (Catch2 unit test utjecaja makroa na signalni path)
- `tests/unit/test_style_modes.cpp` (Catch2 unit test za restrikciju po modovima i odbijanje nedozvoljene FM modulacije)
- `tools/extract_pdf.py` (pomoćni alat)

## 2. Test komande i rezultat
**Pokrenuta komanda**:
```bash
cmake -B build -S . && cmake --build build && cd build && ctest -V
```

**Rezultat**:
Uspješna provjera svih asociranih zahtjeva testnih jedinica iz domene. Nema runtime errora ni kršenja barijere C++20 standarda.
```
100% tests passed, 0 tests failed out of 5
Total Test time (real) =   0.05 sec
Exit code: 0
```

## 3. Poznata ograničenja / otvorena pitanja
- Trenutno testovi ovise o `Catch2` skinutom putem `FetchContent` opcije u CMake podsustavu radi direktne sigurnosti buildanja (izbjegava se problem zaboravljenih submodula kod CI/CD alata, kao što je istaknuto u originalnim dokumentima).
- `ParameterSpec` je napisan u header-only definiciji s `constexpr` objektima što je sigurno za čitanje od strane DSP niti, ali UI binding i tipizaciju mora prihvatiti frontend agent prije implementacije makroa.

## 4. ADR prijedlog
- Nema dodatnih promjena arhitekture u ovoj fazi o kojima treba raspravljati; `src/domain` uspješno provodi zapriječeni pristup opisan u dokumentu pod ADR-003, odnosno DSP ne dobiva raw parametre niti provjerava pravila, već čita `ResolvedParams` iz `ConstraintEngine`-a. 
