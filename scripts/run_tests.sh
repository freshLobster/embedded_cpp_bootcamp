#!/usr/bin/env bash
set -euo pipefail

cmake --build --preset dev
ctest --preset dev --output-on-failure
