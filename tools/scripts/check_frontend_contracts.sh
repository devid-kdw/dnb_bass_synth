#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "${ROOT_DIR}"

binding_file="src/ui/bindings/BindingLayer.h"
plugin_processor_file="src/app/PluginProcessor.cpp"
plugin_editor_file="src/app/PluginEditor.cpp"

have_rg=0
if command -v rg >/dev/null 2>&1; then
  have_rg=1
fi

search_fixed_q() {
  local needle="$1"
  shift
  if [[ "${have_rg}" -eq 1 ]]; then
    rg -Fq -- "${needle}" "$@"
  else
    grep -Fq -- "${needle}" "$@"
  fi
}

search_regex_n() {
  local pattern="$1"
  shift
  if [[ "${have_rg}" -eq 1 ]]; then
    rg -n -- "${pattern}" "$@"
  else
    grep -RInE -- "${pattern}" "$@"
  fi
}

if [[ ! -f "${binding_file}" ]]; then
  echo "[frontend-contract] Missing ${binding_file}"
  exit 1
fi

echo "[frontend-contract] checking canonical BindingLayer parameter IDs"
required_binding_tokens=(
  "macroNeuroFormant.id"
  "macroFmMetal.id"
  "macroRollerDyn.id"
  "macroLiquidDepth.id"
  "macroSubPunch.id"
  "macroFmPressure.id"
  "macroCutoffMotion.id"
  "macroFoldBite.id"
  "macroTableDrift.id"
  "macroSmashGlue.id"
  "macroStyleMorph.id"
  "styleMode.id"
)

for token in "${required_binding_tokens[@]}"; do
  if ! search_fixed_q "${token}" "${binding_file}"; then
    echo "[frontend-contract] Missing canonical token in BindingLayer: ${token}"
    exit 1
  fi
done

if search_regex_n "\"(macro\\.[a-z0-9_]+|style\\.mode|env\\.amp\\.[a-z0-9_]+)\"" "${binding_file}"; then
  echo "[frontend-contract] BindingLayer contains hardcoded raw param IDs (must use domain constants)."
  exit 1
fi

if ! search_fixed_q 'juce::StringArray{"Tech", "Neuro", "Dark"}' "${plugin_processor_file}"; then
  echo "[frontend-contract] Canonical style contract (Tech/Neuro/Dark) missing in PluginProcessor parameter layout."
  exit 1
fi

echo "[frontend-contract] checking legacy style.morph regression guard"
legacy_pattern='(^|[^A-Za-z0-9_.])style[.]morph([^A-Za-z0-9_]|$)'
legacy_scan_paths=(
  "src/ui"
  "src/app"
  "docs/spec/ui_graphic_asset_contract.md"
  "assets/ui/designer/p7/manifests/p7_ui_control_asset_map.md"
  "docs/qa/current_version_daw_test_checklist.md"
)

existing_paths=()
for path in "${legacy_scan_paths[@]}"; do
  if [[ -e "${path}" ]]; then
    existing_paths+=("${path}")
  fi
done

if [[ "${#existing_paths[@]}" -gt 0 ]] && search_regex_n "${legacy_pattern}" "${existing_paths[@]}"; then
  echo "[frontend-contract] Found forbidden legacy token style.morph in runtime/active contract paths."
  exit 1
fi

echo "[frontend-contract] checking UI -> DSP bypass guards"
if search_regex_n '#include\\s+\".*\\/dsp\\/.*\"' src/ui "${plugin_editor_file}"; then
  echo "[frontend-contract] UI/App editor includes DSP headers directly."
  exit 1
fi

if search_regex_n '(^|[^A-Za-z0-9_])(synthEngine|constraintEngine)([^A-Za-z0-9_]|$)' src/ui; then
  echo "[frontend-contract] UI layer references engine/domain runtime internals directly."
  exit 1
fi

if ! search_fixed_q 'make_unique<dnb_bass::ui::BindingLayer>' "${plugin_editor_file}"; then
  echo "[frontend-contract] PluginEditor does not instantiate BindingLayer."
  exit 1
fi

if ! search_fixed_q 'audioProcessor.getApvts()' "${plugin_editor_file}"; then
  echo "[frontend-contract] PluginEditor does not wire UI through APVTS."
  exit 1
fi

echo "[frontend-contract] PASS"
