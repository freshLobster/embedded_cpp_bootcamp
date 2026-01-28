#!/usr/bin/env bash
set -euo pipefail

cmake --preset aarch64
cmake --build --preset aarch64
