# Module 10_sim - Simulation

**Mission:** QEMU/Renode for deterministic repro + CI harness.

**Estimated time:** 2-4 hours.

## Setup checklist (WSL2 primary, Windows notes)
- WSL2 Ubuntu: `sudo apt-get update && sudo apt-get install -y build-essential cmake ninja-build git python3 python3-venv clang clang-format clang-tidy gdb`
- Optional (QEMU): `sudo apt-get install -y qemu-system-aarch64 qemu-user-static`
- Verify compiler: `clang++ --version` (expect version output). On Windows native: open "x64 Native Tools" and run `cl /?`.
- Repo root contains `CMakePresets.json` and `tools/grader/grade.py`.
## Lecture

### QEMU system emulation for full-stack tests
QEMU system emulation provides a virtual model of an entire machine, including CPU, memory, and devices. That scope is important because it lets you run software that expects a complete hardware platform, not just isolated libraries. For robotics and autonomy stacks, this means you can exercise boot sequences, drivers, and user-space pipelines in a controlled environment. This module uses QEMU to reproduce issues before you reach hardware. ?cite?turn25view0?

Because QEMU models the full system, you can test how your software behaves when the platform is slower, missing devices, or configured differently (inference). This is a practical way to find assumptions that would otherwise surface only on the SBC. It also gives you a way to capture logs and artifacts consistently across runs. The goal is to treat simulation as a first-class engineering environment, not a toy. ?cite?turn25view0?

### Renode for IoT and MCU simulation
Renode is a development framework for simulating IoT systems, which makes it suitable for MCU-class firmware and multi-node setups. The project positions itself for development and CI use, emphasizing that you can work with simulated targets rather than depending on physical boards. That aligns with the needs of embedded autonomy teams where hardware availability is limited. In this module, Renode provides the MCU-side counterpart to QEMU's SBC-side emulation. ?cite?turn25view1?

Renode's system simulation model means you can represent different boards and peripherals and run the same firmware across them (inference). That capability is valuable for reproducing issues and for validating behavior across variants without building a hardware lab for each one. It also lets you instrument the system at a level that is difficult on real hardware. The exercises will have you capture deterministic artifacts from those simulated runs. ?cite?turn25view1?

### Simulation as a CI and repro harness
When you combine QEMU's full-system emulation with Renode's IoT focus, you get a practical simulation stack for end-to-end tests (inference). That means you can run a Linux host image with QEMU and attach a simulated MCU or peripheral model in Renode to reproduce full pipeline behavior. This is the foundation of the CI harness in this module. The intent is to make bugs reproducible without waiting for hardware. ?cite?turn25view0?turn25view1?

Simulation does not replace hardware, but it gives you a deterministic starting point for debugging and regression checks (inference). Once a failure is reproducible in a simulator, you can fix it and then confirm on the real device, which shortens the feedback loop. That workflow is what lets high-assurance teams move quickly while still being disciplined. The exercises require you to save trace and log artifacts so you can prove reproducibility. ?cite?turn25view0?turn25view1?



## Start here
1) Pick one exercise folder below and `cd` into it.
2) Follow the exercise README exactly; it includes build/test commands and grading steps.
3) Save outputs in that exercise's `learner/artifacts/`.

## Exercises (per-folder)
| Exercise | Link |
|---|---|
| ex01_qemu | [ex01_qemu](exercises/ex01_qemu/README.md) |
| ex02_renode | [ex02_renode](exercises/ex02_renode/README.md) |
| ex03_ci_harness | [ex03_ci_harness](exercises/ex03_ci_harness/README.md) |

## Done definition
- Each exercise you attempt has passing tests and saved artifacts.
- The per-exercise grader reports a numeric score.
- Module-level artifacts (if any) are stored in `modules/10_sim/artifacts/`.

## Grade this module
- Module-level grader: `python3 tools/grader/grade.py --module modules/10_sim`
- JSON: `python3 tools/grader/grade.py --module 10 --json`
- Per-exercise grading is done inside each exercise folder README.
