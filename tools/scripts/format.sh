#!/usr/bin/env bash
set -euo pipefail

usage() {
  cat <<'EOF'
Usage:
  tools/scripts/format.sh --check
  tools/scripts/format.sh --fix
EOF
}

mode="check"
if [[ "${1:-}" == "--fix" ]]; then
  mode="fix"
elif [[ "${1:-}" == "--check" ]]; then
  mode="check"
else
  usage
  exit 2
fi

find_clang_format() {
  local candidates=(
    clang-format
    clang-format-21
    clang-format-20
    clang-format-19
    clang-format-18
    clang-format-17
    clang-format-16
    /opt/homebrew/opt/llvm/bin/clang-format
  )
  local c
  for c in "${candidates[@]}"; do
    if command -v "${c}" >/dev/null 2>&1; then
      command -v "${c}"
      return 0
    fi
    if [[ -x "${c}" ]]; then
      echo "${c}"
      return 0
    fi
  done
  return 1
}

clang_format_bin="$(find_clang_format || true)"
if [[ -z "${clang_format_bin}" ]]; then
  echo "clang-format not found. Install LLVM/clang-format first."
  exit 1
fi

tracked_sources=()
while IFS= read -r file; do
  tracked_sources+=("${file}")
done < <(
  git ls-files \
    | rg -N '^(src|tests|bench)/.*\.(h|hpp|hh|c|cc|cpp|cxx|mm)$'
)

if [[ "${#tracked_sources[@]}" -eq 0 ]]; then
  echo "No source files matched formatting patterns."
  exit 0
fi

echo "[format] using: ${clang_format_bin}"
echo "[format] mode: ${mode}"
echo "[format] files: ${#tracked_sources[@]}"

if [[ "${mode}" == "check" ]]; then
  "${clang_format_bin}" --dry-run --Werror "${tracked_sources[@]}"
  echo "[format] PASS"
else
  "${clang_format_bin}" -i "${tracked_sources[@]}"
  echo "[format] Updated files in-place"
fi
