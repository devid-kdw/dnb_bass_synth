# P8 Frontend CI/CD Hardening Handoff

Date: 2026-02-22  
Owner: Frontend/UI agent  
Phase: P8  
Status proposal: `Review`

## 1. Scope
P8 frontend support closure for:
1. CI contract hardening (canonical param IDs + legacy naming regression guard)
2. Asset integrity hardening (runtime/manifest consistency + control state completeness)
3. DAW regression static guard hardening (knob endpoints, center panel overlap)
4. Architecture boundary guard reinforcement (no UI->DSP bypass, APVTS/domain contract path preserved)

## 2. Changed Files
1. `.github/workflows/ci.yml`
2. `src/ui/components/VisualFeedbackView.h`
3. `tools/scripts/check_frontend_contracts.sh`
4. `tools/scripts/check_frontend_assets.sh`
5. `tools/scripts/check_frontend_daw_guards.sh`
6. `docs/qa/frontend_phase_handoffs/P8_handoff.md`

## 3. Closure Map (P8 Frontend Scope)
| Scope Item | Closure | Evidence |
|---|---|---|
| Canonical `param_id` validation for UI binding layer | Added dedicated CI/script gate that validates BindingLayer uses canonical domain tokens (`macro*.id`, `styleMode.id`) and rejects hardcoded raw param IDs. | `tools/scripts/check_frontend_contracts.sh`, `.github/workflows/ci.yml` |
| Block legacy naming regression (`style.morph`) | Added explicit legacy token scan in runtime/active contract paths; command returns zero matches. | `tools/scripts/check_frontend_contracts.sh`, command output in section 4.4 |
| Runtime assets must match manifest | Added CI/script gate: CMake runtime list (60), runtime dir (60), and UI-used assets all checked against manifest (missing = 0). | `tools/scripts/check_frontend_assets.sh`, command output in section 4.5 |
| No missing/dead UI control states in scope | Added explicit control-state completeness checks (10 macro knobs x3 states, style mode x3 states per mode, morph assets, visual feedback panel/frame/grid/glow). Activated visual panel frame asset in runtime view. | `tools/scripts/check_frontend_assets.sh`, `src/ui/components/VisualFeedbackView.h` |
| Knob endpoint guard (`0%` / `100%`) | Added static DAW guard check verifying snap thresholds + butt-capped stroke + endpoint marker remain in `ImageSlider`. | `tools/scripts/check_frontend_daw_guards.sh` |
| Center visual panel overlap regression guard | Added static DAW guard check enforcing no static wave/spectrum overlay usage in active paint path while preserving runtime bars/wave path and frame/grid/glow layers. | `tools/scripts/check_frontend_daw_guards.sh`, `src/ui/components/VisualFeedbackView.h` |
| No runtime UI->DSP bypass; APVTS + domain contract path only | Added guard checks for forbidden direct DSP includes/references in UI path and confirmed editor wiring via `BindingLayer` + `getApvts()`. | `tools/scripts/check_frontend_contracts.sh`, `src/app/PluginEditor.cpp` |

## 4. Verification Commands and Results

### 4.1 Required Submodule Init
Command:
```bash
tools/scripts/init_submodules.sh
```
Result:
- pass
- submodule sync/update completed for `extern/*`

### 4.2 Required Build
Command:
```bash
cmake --build build --parallel
```
Result:
- pass
- `DnBBassSynth_VST3` built successfully

### 4.3 Required Test Suite
Command:
```bash
cd build && ctest --output-on-failure
```
Result:
- pass
- `45/45` tests passed

### 4.4 Contract Legacy Token Check (`style.morph`)
Command:
```bash
rg -n "(^|[^A-Za-z0-9_.])style[.]morph([^A-Za-z0-9_]|$)" \
  src/ui src/app \
  docs/spec/ui_graphic_asset_contract.md \
  assets/ui/designer/p7/manifests/p7_ui_control_asset_map.md \
  docs/qa/current_version_daw_test_checklist.md || true
```
Result:
- pass
- no matches (`0`)

### 4.5 Asset Integrity Check (runtime used assets in manifest)
Command:
```bash
manifest_tmp=$(mktemp); used_tmp=$(mktemp)
tail -n +2 assets/ui/designer/p7/manifests/p7_ui_png_manifest.csv | cut -d, -f1 | tr -d '\r' | sort -u > "$manifest_tmp"
rg --no-filename -o 'UIAssets::[a-z0-9_]+_png' src/ui | sed 's/UIAssets:://' | sed 's/_png$/.png/' | sort -u > "$used_tmp"
missing=$(comm -23 "$used_tmp" "$manifest_tmp" | wc -l | tr -d ' ')
used_count=$(wc -l < "$used_tmp" | tr -d ' ')
manifest_count=$(wc -l < "$manifest_tmp" | tr -d ' ')
echo "manifest_count=${manifest_count}"
echo "ui_used_count=${used_count}"
echo "missing_in_manifest=${missing}"
rm -f "$manifest_tmp" "$used_tmp"
```
Result:
- `manifest_count=60`
- `ui_used_count=52`
- `missing_in_manifest=0`

### 4.6 New P8 Frontend Guard Scripts
Commands:
```bash
bash tools/scripts/check_frontend_contracts.sh
bash tools/scripts/check_frontend_assets.sh
bash tools/scripts/check_frontend_daw_guards.sh
```
Results:
1. `check_frontend_contracts.sh` -> pass
2. `check_frontend_assets.sh` -> pass (`manifest=60`, `cmake_runtime=60`, `runtime_disk=60`, `ui_used=52`)
3. `check_frontend_daw_guards.sh` -> pass

## 5. Runtime Bypass and Dead Control Confirmation
1. Runtime UI->DSP bypass: **not present** (UI wiring remains APVTS attachment based through `BindingLayer`; no direct DSP includes in UI path).
2. Dead control states in scoped controls: **not detected** (macro/style/morph/visual scoped states validated via script and active runtime references).
3. Center panel static/runtime overlap regression: **guarded** (static wave/spectrum overlays remain blocked from active view code path).

## 6. Known Limitations / Open Questions
1. None blocking for P8 frontend support scope.

## 7. Final Status Proposal
`Review`
