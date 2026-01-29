# ex01_qemu – Run aarch64 binary under QEMU user mode

What you are building: Deterministic run of platform_core_app via qemu-aarch64.
Why it matters: CI-friendly simulation.

Prerequisites check
- `qemu-aarch64 --version`
- aarch64 binary present (Module08)

Files you will touch
- `modules/10_sim/artifacts/ex01_qemu.log`

Steps
1. Run binary:
```
qemu-aarch64 -L /usr/aarch64-linux-gnu ./build/aarch64/platform_core_app > modules/10_sim/artifacts/ex01_qemu.log 2>&1 & sleep 10; pkill platform_core_app
```
2. Compute checksum of log: `sha256sum modules/10_sim/artifacts/ex01_qemu.log > modules/10_sim/artifacts/ex01_qemu.sha`

Verification
- Log not empty; checksum recorded.

Stop here and commit
- Message: "Module10: QEMU run"

If it fails
- Missing loader path: install `qemu-user` and `libc6-arm64-cross`.
