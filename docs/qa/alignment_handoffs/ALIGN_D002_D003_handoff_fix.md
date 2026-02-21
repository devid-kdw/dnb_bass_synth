# ALIGN D002/D003 Handoff Fix (F-ALIGN-002, F-ALIGN-003)

Date: 2026-02-21  
Owner: TechStack/Repo Agent  
Scope: P4-gate alignment remediation for `F-ALIGN-002` and `F-ALIGN-003`

## 1. Changed Files
- `CMakeLists.txt`
- `tests/CMakeLists.txt`
- `.gitmodules`
- `tools/scripts/init_submodules.sh`
- `extern/benchmark` (gitlink)
- `extern/catch2` (gitlink)
- `extern/clap-cleveraudio` (gitlink)
- `extern/hiir` (gitlink)
- `extern/json` (gitlink)
- `extern/juce` (gitlink)
- `extern/spdlog` (gitlink)
- `extern/.gitkeep` (removed)
- `src/app/PluginEditor.h` (minimal include fix needed to satisfy mandatory build verification)

## 2. Verification Commands + Result
1. `tools/scripts/init_submodules.sh`  
   Result: **PASS**

2. `git submodule status`  
   Result: **PASS**
   - `extern/benchmark` -> `6ebb28710424e07e6f35308f2a3997e34bedd6b8`
   - `extern/catch2` -> `50e9dbfc4e17d5a26a53584c3fc66facf4197192`
   - `extern/clap-cleveraudio` -> `29ffcc273be7c7c651f6c9953b99e69700e2387a`
   - `extern/hiir` -> `4589fedb4d08b899514cb605ccd7418bf262ab18`
   - `extern/json` -> `8167d2f64122c3ef7e5a0d9cab239fdba37aa54c`
   - `extern/juce` -> `501c07674e1ad693085a7e7c398f205c2677f5da`
   - `extern/spdlog` -> `c49c7cf96093d662826a76608d57be4611751c0e`

3. `git ls-files --stage` (`160000` gitlinks evidence)  
   Result: **PASS**
   - all required `extern/*` paths are tracked as `160000` gitlink entries.

4. clean configure:  
   `cmake -S . -B build_clean_alignment_fix -DDNB_ENABLE_PLUGIN_TARGET=ON -DDNB_BUILD_TESTS=ON -DDNB_BUILD_BENCH=ON`  
   Result: **PASS**

5. build + test:
   - `cmake --build build --parallel` -> **PASS**
   - `cd build && ctest --output-on-failure` -> **PASS** (`17/17`)

6. policy checks:
   - `FetchContent` not active in tests path -> **PASS**
   - `_deps/catch2-src` fallback not active by default -> **PASS**
     - `DNB_ENABLE_TESTS_CATCH2_BINARY_DIR_FALLBACK:BOOL=OFF` in `build/CMakeCache.txt` and `build_clean_alignment_fix/CMakeCache.txt`

## 3. Closure Map

### F-ALIGN-002 (submodule model declared but not pinned in repo index)
Status: **Closed -> Review**

Closure evidence:
- required extern modules now exist as pinned gitlinks (`160000`) in index.
- `.gitmodules` covers required module set.
- `tools/scripts/init_submodules.sh` remains canonical bootstrap and executed successfully.
- `extern/.gitkeep` removed to avoid placeholder-only extern tracking.

### F-ALIGN-003 (tests CMake default fallback to `${CMAKE_BINARY_DIR}/_deps/catch2-src`)
Status: **Closed -> Review**

Closure evidence:
- `tests/CMakeLists.txt` default path is strict submodule-first:
  - use `extern/catch2` when present
  - otherwise `FATAL_ERROR`
- compatibility fallback is available only behind explicit flag:
  - `DNB_ENABLE_TESTS_CATCH2_BINARY_DIR_FALLBACK` (OFF by default)
- no `FetchContent` activation in current tests dependency path.

## 4. Open Questions / Constraints
- `extern/hiir` was pinned to a reachable upstream (`https://github.com/unevens/hiir.git`) because previously configured URL was not resolvable; if project governance requires a different canonical mirror, `.gitmodules` URL can be adjusted without changing pinned gitlink model.

## 5. Proposed Status
- `F-ALIGN-002`: **Review**
- `F-ALIGN-003`: **Review**
