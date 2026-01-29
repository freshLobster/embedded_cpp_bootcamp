
# Troubleshooting - Memory
- Configure fails (No C/CXX compiler): install build-essential/clang or run in VS x64 prompt. Re-run `cmake --preset dev`.
- Linker missing Windows SDK libs (kernel32.lib): build inside WSL or use MSVC toolchain; rerun configure.
- ctest finds 0 tests: ensure you built preset `dev` and added `GTEST_SKIP` appropriately; rerun `ctest -N` to list.
- Permission denied writing artifacts: check path `modules/02_memory_memory/artifacts` exists; create if missing.
- Sanitizer unavailable (TSan on MSVC): use WSL/Clang; set `PLATFORM_ENABLE_TSAN` only on supported toolchains.
- CUDA errors (if applicable): verify `nvidia-smi` works; rebuild with `--preset cuda`.
