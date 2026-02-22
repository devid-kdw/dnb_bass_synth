#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "${ROOT_DIR}"

manifest_csv="assets/ui/designer/p7/manifests/p7_ui_png_manifest.csv"
runtime_dir="assets/ui/runtime/p7"
cmake_file="CMakeLists.txt"

macro_panel_file="src/ui/components/MacroPanel.h"
style_selector_file="src/ui/components/StyleSelector.h"
style_morph_file="src/ui/components/StyleMorphControl.h"
visual_feedback_file="src/ui/components/VisualFeedbackView.h"

if [[ ! -f "${manifest_csv}" ]]; then
  echo "[frontend-assets] Missing manifest CSV: ${manifest_csv}"
  exit 1
fi

if [[ ! -d "${runtime_dir}" ]]; then
  echo "[frontend-assets] Missing runtime asset directory: ${runtime_dir}"
  exit 1
fi

tmp_dir="$(mktemp -d "${TMPDIR:-/tmp}/dnb_frontend_assets.XXXXXX")"
trap 'rm -rf "${tmp_dir}"' EXIT

manifest_assets="${tmp_dir}/manifest_assets.txt"
cmake_runtime_assets="${tmp_dir}/cmake_runtime_assets.txt"
disk_runtime_assets="${tmp_dir}/disk_runtime_assets.txt"
ui_used_assets="${tmp_dir}/ui_used_assets.txt"

tail -n +2 "${manifest_csv}" | cut -d, -f1 | tr -d '\r' | sort -u > "${manifest_assets}"
rg --no-filename -o 'assets/ui/runtime/p7/[a-z0-9_]+\.png' "${cmake_file}" \
  | sed 's#assets/ui/runtime/p7/##' \
  | sort -u > "${cmake_runtime_assets}"
find "${runtime_dir}" -maxdepth 1 -type f -name '*.png' -print \
  | sed 's#.*/##' \
  | sort -u > "${disk_runtime_assets}"
rg --no-filename -o 'UIAssets::[a-z0-9_]+_png' src/ui \
  | sed 's/UIAssets:://' \
  | sed 's/_png$/.png/' \
  | sort -u > "${ui_used_assets}"

manifest_count="$(wc -l < "${manifest_assets}" | tr -d ' ')"
cmake_count="$(wc -l < "${cmake_runtime_assets}" | tr -d ' ')"
disk_count="$(wc -l < "${disk_runtime_assets}" | tr -d ' ')"
ui_used_count="$(wc -l < "${ui_used_assets}" | tr -d ' ')"

if [[ "${manifest_count}" -ne 60 ]]; then
  echo "[frontend-assets] Manifest count mismatch: expected 60, got ${manifest_count}"
  exit 1
fi

if [[ "${cmake_count}" -ne 60 ]]; then
  echo "[frontend-assets] CMake runtime asset count mismatch: expected 60, got ${cmake_count}"
  exit 1
fi

missing_from_manifest="${tmp_dir}/missing_from_manifest.txt"
comm -23 "${cmake_runtime_assets}" "${manifest_assets}" > "${missing_from_manifest}"
if [[ -s "${missing_from_manifest}" ]]; then
  echo "[frontend-assets] Runtime assets in CMake missing from manifest:"
  cat "${missing_from_manifest}"
  exit 1
fi

missing_on_disk="${tmp_dir}/missing_on_disk.txt"
comm -23 "${cmake_runtime_assets}" "${disk_runtime_assets}" > "${missing_on_disk}"
if [[ -s "${missing_on_disk}" ]]; then
  echo "[frontend-assets] Runtime assets in CMake missing on disk:"
  cat "${missing_on_disk}"
  exit 1
fi

used_missing_manifest="${tmp_dir}/used_missing_manifest.txt"
comm -23 "${ui_used_assets}" "${manifest_assets}" > "${used_missing_manifest}"
if [[ -s "${used_missing_manifest}" ]]; then
  echo "[frontend-assets] UI-referenced assets missing from manifest:"
  cat "${used_missing_manifest}"
  exit 1
fi

used_missing_disk="${tmp_dir}/used_missing_disk.txt"
comm -23 "${ui_used_assets}" "${disk_runtime_assets}" > "${used_missing_disk}"
if [[ -s "${used_missing_disk}" ]]; then
  echo "[frontend-assets] UI-referenced assets missing from runtime directory:"
  cat "${used_missing_disk}"
  exit 1
fi

echo "[frontend-assets] checking control state completeness"
macro_ids=(
  "neuro_formant"
  "fm_metal"
  "roller_dynamics"
  "liquid_depth"
  "sub_punch"
  "fm_pressure"
  "cutoff_motion"
  "fold_bite"
  "table_drift"
  "smash_glue"
)
macro_states=("idle" "hover" "active")
for macro_id in "${macro_ids[@]}"; do
  for macro_state in "${macro_states[@]}"; do
    token="ui_macro_knob_${macro_id}_${macro_state}_v001"
    if ! rg -q "${token}" "${macro_panel_file}"; then
      echo "[frontend-assets] Missing macro state token in MacroPanel: ${token}"
      exit 1
    fi
  done
done

style_modes=("tech" "neuro" "dark")
style_states=("idle" "selected" "disabled")
for style_mode in "${style_modes[@]}"; do
  for style_state in "${style_states[@]}"; do
    token="ui_style_mode_${style_mode}_${style_state}_v001"
    if ! rg -q "${token}" "${style_selector_file}"; then
      echo "[frontend-assets] Missing style state token in StyleSelector: ${token}"
      exit 1
    fi
  done
done

morph_tokens=(
  "ui_style_morph_track_main_base_v001"
  "ui_style_morph_thumb_main_base_v001"
  "ui_style_morph_glow_main_active_v001"
)
for token in "${morph_tokens[@]}"; do
  if ! rg -q "${token}" "${style_morph_file}"; then
    echo "[frontend-assets] Missing morph asset token in StyleMorphControl: ${token}"
    exit 1
  fi
done

visual_tokens=(
  "ui_panel_visual_feedback_frame_base_v001"
  "ui_visual_scope_grid_main_base_v001"
  "ui_visual_scope_frame_glow_active_v001"
)
for token in "${visual_tokens[@]}"; do
  if ! rg -q "${token}" "${visual_feedback_file}"; then
    echo "[frontend-assets] Missing visual feedback token in VisualFeedbackView: ${token}"
    exit 1
  fi
done

if rg -n 'ui_visual_scope_(wave_overlay|spectrum_overlay)_base_v001' "${visual_feedback_file}"; then
  echo "[frontend-assets] VisualFeedbackView reintroduced static wave/spectrum overlays."
  exit 1
fi

echo "[frontend-assets] PASS (manifest=${manifest_count}, cmake_runtime=${cmake_count}, runtime_disk=${disk_count}, ui_used=${ui_used_count})"
