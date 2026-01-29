# Module 09_mcu - MCU

**Mission:** ESP32-C3 firmware loop, ISR/task race, UART bridge.

**Estimated time:** 2-4 hours.

## Setup checklist (WSL2 primary, Windows notes)
- WSL2 Ubuntu: `sudo apt-get update && sudo apt-get install -y build-essential cmake ninja-build git python3 python3-venv clang clang-format clang-tidy gdb`
- Optional MCU tooling: `sudo apt-get install -y openocd esptool`
- Verify compiler: `clang++ --version` (expect version output). On Windows native: open "x64 Native Tools" and run `cl /?`.
- Repo root contains `CMakePresets.json` and `tools/grader/grade.py`.

## Start here
1) Pick one exercise folder below and `cd` into it.
2) Follow the exercise README exactly; it includes build/test commands and grading steps.
3) Save outputs in that exercise's `learner/artifacts/`.

## Exercises (per-folder)
| Exercise | Link |
|---|---|
| ex01_firmware_build | [ex01_firmware_build](exercises/ex01_firmware_build/README.md) |
| ex02_race | [ex02_race](exercises/ex02_race/README.md) |
| ex03_uart_bridge | [ex03_uart_bridge](exercises/ex03_uart_bridge/README.md) |

## Done definition
- Each exercise you attempt has passing tests and saved artifacts.
- The per-exercise grader reports a numeric score.
- Module-level artifacts (if any) are stored in `modules/09_mcu/artifacts/`.

## Grade this module
- Module-level grader: `python3 tools/grader/grade.py --module modules/09_mcu`
- JSON: `python3 tools/grader/grade.py --module 09 --json`
- Per-exercise grading is done inside each exercise folder README.
- Hardware checks require `--enable-hardware` to score full points.
