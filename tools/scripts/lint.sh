#!/usr/bin/env bash
set -euo pipefail

usage() {
  cat <<'EOF'
Usage:
  tools/scripts/lint.sh [--build-dir <dir>] [--checks <checks>]

Defaults:
  --build-dir build
  --checks -*,clang-analyzer-*
EOF
}

build_dir="build"
checks='-*,clang-analyzer-*'

while [[ $# -gt 0 ]]; do
  case "$1" in
  --build-dir)
    build_dir="${2:-}"
    shift 2
    ;;
  --checks)
    checks="${2:-}"
    shift 2
    ;;
  -h|--help)
    usage
    exit 0
    ;;
  *)
    echo "Unknown argument: $1"
    usage
    exit 2
    ;;
  esac
done

find_clang_tidy() {
  local candidates=(
    clang-tidy
    clang-tidy-21
    clang-tidy-20
    clang-tidy-19
    clang-tidy-18
    clang-tidy-17
    clang-tidy-16
    /opt/homebrew/opt/llvm/bin/clang-tidy
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

clang_tidy_bin="$(find_clang_tidy || true)"
if [[ -z "${clang_tidy_bin}" ]]; then
  echo "clang-tidy not found. Install LLVM/clang-tidy first."
  exit 1
fi

compile_db="${build_dir}/compile_commands.json"
if [[ ! -f "${compile_db}" ]]; then
  echo "Missing ${compile_db}. Configure with -DCMAKE_EXPORT_COMPILE_COMMANDS=ON first."
  exit 1
fi

lint_files=()

collect_compile_files() {
  if command -v jq >/dev/null 2>&1; then
    jq -r '.[].file' "${compile_db}"
    return 0
  fi

  if command -v rg >/dev/null 2>&1; then
    rg -N --no-filename -o '"file": "[^"]+"' "${compile_db}" \
      | sed -E 's/"file": "([^"]+)"/\1/'
    return 0
  fi

  grep -oE '"file": "[^"]+"' "${compile_db}" \
    | sed -E 's/"file": "([^"]+)"/\1/'
}

while IFS= read -r file; do
  lint_files+=("${file}")
done < <(
  collect_compile_files \
    | sed 's#\\\\#/#g' \
    | sort -u \
    | {
      if command -v rg >/dev/null 2>&1; then
        rg -N '(src|tests|bench)/.*\.(c|cc|cpp|cxx)$'
      else
        grep -E '(src|tests|bench)/.*\.(c|cc|cpp|cxx)$'
      fi
    } \
    | {
      if command -v rg >/dev/null 2>&1; then
        rg -N -v '/extern/'
      else
        grep -Ev '/extern/'
      fi
    } \
    || true
)

if [[ "${#lint_files[@]}" -eq 0 ]]; then
  echo "No lintable files discovered in ${compile_db}."
  exit 1
fi

echo "[lint] using: ${clang_tidy_bin}"
echo "[lint] build dir: ${build_dir}"
echo "[lint] checks: ${checks}"
echo "[lint] files: ${#lint_files[@]}"

status=0
extra_args=()
if [[ "$(uname -s)" == "Darwin" ]]; then
  sdk_path="$(xcrun --show-sdk-path 2>/dev/null || true)"
  if [[ -n "${sdk_path}" ]]; then
    extra_args+=(--extra-arg=-isysroot)
    extra_args+=(--extra-arg="${sdk_path}")
  fi
fi

for f in "${lint_files[@]}"; do
  if [[ "${f}" == /* ]]; then
    target="${f}"
  else
    target="${PWD}/${f}"
  fi

  if [[ ! -f "${target}" ]]; then
    continue
  fi

  if ! "${clang_tidy_bin}" -p "${build_dir}" -checks="${checks}" -quiet \
      "${extra_args[@]}" "${target}"; then
    status=1
  fi
done

if [[ "${status}" -ne 0 ]]; then
  echo "[lint] FAIL"
  exit "${status}"
fi

echo "[lint] PASS"
