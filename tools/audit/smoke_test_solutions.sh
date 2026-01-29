#!/usr/bin/env bash
set -euo pipefail

exercises=(
  "modules/01_foundations/exercises/ex01_scope_guard"
  "modules/06_debugging/exercises/ex01_asan"
  "modules/11_cuda_basics/exercises/ex01_env"
)

for ex in "${exercises[@]}"; do
  echo "== Smoke test: $ex (solution)"
  pushd "$ex" >/dev/null
  rm -rf build_solution
  if command -v ninja >/dev/null 2>&1; then
    cmake -S solution -B build_solution -G Ninja -DCMAKE_BUILD_TYPE=Debug
    cmake --build build_solution
    ctest --test-dir build_solution --output-on-failure
  else
    cmake -S solution -B build_solution -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug
    cmake --build build_solution
    ctest --test-dir build_solution --output-on-failure
  fi
  popd >/dev/null
done
