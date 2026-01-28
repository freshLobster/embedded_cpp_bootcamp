#!/usr/bin/env bash
set -euo pipefail

if [[ $# -lt 2 ]]; then
  echo "Usage: $0 <user@host> <remote_dir> [binary_name]" >&2
  exit 1
fi

TARGET="$1"
REMOTE_DIR="$2"
BINARY="${3:-platform_core_app}"

cmake --build --preset release

scp "build/release/${BINARY}" "${TARGET}:${REMOTE_DIR}/${BINARY}"
ssh "${TARGET}" "chmod +x ${REMOTE_DIR}/${BINARY} && ${REMOTE_DIR}/${BINARY} --help >/dev/null 2>&1 || true"
echo "Deployed ${BINARY} to ${TARGET}:${REMOTE_DIR}"
