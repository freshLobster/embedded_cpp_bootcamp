# ex01_cross_build – aarch64 cross compile

What you are building: Cross-built binary for SBC.
Why it matters: Deployment to Raspberry/Orange Pi.

Prerequisites check
- `aarch64-linux-gnu-g++ --version`

Files you will touch
- None (build only)
- `modules/08_cross_deploy/artifacts/ex01_file.txt`

Steps
1. Build: `./scripts/cross_compile_aarch64.sh`
2. Verify binary arch:
```
file build/aarch64/platform_core_app > modules/08_cross_deploy/artifacts/ex01_file.txt
```
Expected: ELF 64-bit LSB aarch64.

Verification
- Artifact shows correct arch.

Stop here and commit
- Message: "Module08: cross build aarch64"

If it fails
- Install toolchain: `sudo apt install gcc-aarch64-linux-gnu g++-aarch64-linux-gnu`.
