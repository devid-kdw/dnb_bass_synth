#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "${ROOT_DIR}"

image_slider_file="src/ui/components/ImageSlider.h"
visual_feedback_file="src/ui/components/VisualFeedbackView.h"

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

if [[ ! -f "${image_slider_file}" ]]; then
  echo "[frontend-daw-guards] Missing ${image_slider_file}"
  exit 1
fi

if [[ ! -f "${visual_feedback_file}" ]]; then
  echo "[frontend-daw-guards] Missing ${visual_feedback_file}"
  exit 1
fi

echo "[frontend-daw-guards] checking knob endpoint guards (0% / 100%)"
required_slider_patterns=(
  'val <= 0.001f'
  'val >= 0.999f'
  'PathStrokeType::butt'
  'endpointAngle'
  'fillEllipse(endpoint.x'
)
for pattern in "${required_slider_patterns[@]}"; do
  if ! search_fixed_q "${pattern}" "${image_slider_file}"; then
    echo "[frontend-daw-guards] Missing knob endpoint guard pattern: ${pattern}"
    exit 1
  fi
done

echo "[frontend-daw-guards] checking center visual panel overlap guards"
required_visual_patterns=(
  'ui_panel_visual_feedback_frame_base_v001'
  'ui_visual_scope_grid_main_base_v001'
  'ui_visual_scope_frame_glow_active_v001'
  'const int barCount = 36;'
  'juce::Path waveform;'
)
for pattern in "${required_visual_patterns[@]}"; do
  if ! search_fixed_q "${pattern}" "${visual_feedback_file}"; then
    echo "[frontend-daw-guards] Missing visual guard/runtime pattern: ${pattern}"
    exit 1
  fi
done

if search_regex_n 'ui_visual_scope_(wave_overlay|spectrum_overlay)_base_v001' "${visual_feedback_file}"; then
  echo "[frontend-daw-guards] Static wave/spectrum overlay regression detected in VisualFeedbackView."
  exit 1
fi

echo "[frontend-daw-guards] PASS"
