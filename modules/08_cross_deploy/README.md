# Module 08_cross_deploy - Cross & Deploy

**Mission:** aarch64 cross, SBC deploy, systemd, remote checks.

**Estimated time:** 2-4 hours.

## Setup checklist (WSL2 primary, Windows notes)
- WSL2 Ubuntu: `sudo apt-get update && sudo apt-get install -y build-essential cmake ninja-build git python3 python3-venv clang clang-format clang-tidy gdb`
- Verify compiler: `clang++ --version` (expect version output). On Windows native: open "x64 Native Tools" and run `cl /?`.
- Repo root contains `CMakePresets.json` and `tools/grader/grade.py`.
## Lecture

### Cross-compilation with CMake toolchains
CMake uses a toolchain file to control cross-compilation, and you pass it via `CMAKE_TOOLCHAIN_FILE` at configure time. That file sets up the compilers, target system, and related settings so CMake generates build rules for the target architecture instead of the host. For aarch64 SBCs this is non-negotiable: without a toolchain file you will build for the wrong CPU and only discover it on deployment. This module uses a toolchain file to make the target explicit and repeatable. ?cite?turn18view0?turn17view1?

A toolchain file is also the right place to encode the sysroot and include paths that match the target device. When those settings live in one file, your build is reproducible in CI and for every developer, which is critical for defense and robotics programs that require auditability. You are not just compiling; you are defining a controlled build environment. The cross-build exercise makes you validate that environment by running on real hardware. ?cite?turn18view0?turn17view1?

### Deployment and service management with systemd
On modern Linux SBCs, systemd service unit files are how you define long-running services and their startup behavior. A service unit is described by a `.service` file, which tells systemd how to start, stop, and manage your process. That makes it the right vehicle for deploying robotics pipeline components that should boot with the device and restart on failure. In this module you will package your binary as a service rather than a one-off command. ?cite?turn18view1?

Using systemd is more than convenience; it makes lifecycle and fault handling explicit. When your service is described declaratively, you can reason about dependencies, restarts, and ordering just like any other configuration artifact. That is a necessary step toward reproducible deployments on fielded hardware. The exercises focus on validating that the service behaves predictably across reboots. ?cite?turn18view1?

### Remote debugging on target hardware
`gdbserver` is designed to run on the target and communicate with a host GDB for remote debugging. The documented usage is `gdbserver COMM PROGRAM`, which starts the program under the control of the remote debugger. This is the standard pattern for debugging on SBCs where local debugging is limited or too intrusive. It is also the only realistic option when you need to inspect timing or I/O behavior on the device itself. ?cite?turn18view2?

Remote debugging works best when you have matching symbols and a clean deployment pipeline. The gdbserver workflow reinforces that separation of host and target while still letting you inspect state, set breakpoints, and validate fixes in situ. That combination is essential for cross-compiled robotics software where a host-only test is not representative. This module makes you practice the full loop: build, deploy, attach, and verify. ?cite?turn18view2?



## Start here
1) Pick one exercise folder below and `cd` into it.
2) Follow the exercise README exactly; it includes build/test commands and grading steps.
3) Save outputs in that exercise's `learner/artifacts/`.

## Exercises (per-folder)
| Exercise | Link |
|---|---|
| ex01_cross_build | [ex01_cross_build](exercises/ex01_cross_build/README.md) |
| ex02_deploy | [ex02_deploy](exercises/ex02_deploy/README.md) |
| ex03_latency_on_hw | [ex03_latency_on_hw](exercises/ex03_latency_on_hw/README.md) |

## Done definition
- Each exercise you attempt has passing tests and saved artifacts.
- The per-exercise grader reports a numeric score.
- Module-level artifacts (if any) are stored in `modules/08_cross_deploy/artifacts/`.

## Grade this module
- Module-level grader: `python3 tools/grader/grade.py --module modules/08_cross_deploy`
- JSON: `python3 tools/grader/grade.py --module 08 --json`
- Per-exercise grading is done inside each exercise folder README.
- Hardware checks require `--enable-hardware` to score full points.
