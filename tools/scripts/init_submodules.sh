#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "${ROOT_DIR}"

if [[ ! -f ".gitmodules" ]]; then
  echo "Missing .gitmodules in ${ROOT_DIR}"
  exit 1
fi

echo "[init_submodules] syncing submodule metadata"
git submodule sync --recursive

echo "[init_submodules] initializing and updating extern submodules"
git submodule update --init --recursive

echo "[init_submodules] done"
