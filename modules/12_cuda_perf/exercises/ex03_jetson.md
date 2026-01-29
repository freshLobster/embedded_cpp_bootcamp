# ex03_jetson – Jetson-style constraints

What you are building: Note and optional build for aarch64 CUDA with reduced resources.
Why it matters: Anticipate Jetson deployment limits.

Prerequisites check
- aarch64 CUDA sysroot available (or document unavailability).

Files you will touch
- `docs/cuda/jetson_adr.md` (create outline if missing)
- `modules/12_cuda_perf/artifacts/ex03_notes.txt`

Steps
1. Draft ADR: constraints (power, shared mem), preferred deployment pattern, sync pitfalls.
2. Attempt cross-build: `cmake --preset aarch64 -DPLATFORM_ENABLE_CUDA=ON` (if toolchain available). Record outcome.
3. Save notes/outcome to artifacts file.

Verification
- ADR updated; artifacts file describes result.

Stop here and commit
- Message: "Module12: Jetson constraints"

If it fails
- No sysroot: document as such; mark follow-up action.
