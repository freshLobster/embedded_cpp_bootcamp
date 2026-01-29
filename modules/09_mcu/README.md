# Module 09_mcu - MCU

**Mission:** ESP32-C3 firmware loop, ISR/task race, UART bridge.

**Estimated time:** 2-4 hours.

## Setup checklist (WSL2 primary, Windows notes)
- WSL2 Ubuntu: `sudo apt-get update && sudo apt-get install -y build-essential cmake ninja-build git python3 python3-venv clang clang-format clang-tidy gdb`
- Optional MCU tooling: `sudo apt-get install -y openocd esptool`
- Verify compiler: `clang++ --version` (expect version output). On Windows native: open "x64 Native Tools" and run `cl /?`.
- Repo root contains `CMakePresets.json` and `tools/grader/grade.py`.
## Lecture

### RTOS tasks on ESP32-class MCUs
ESP-IDF uses FreeRTOS as its operating system layer, which provides task scheduling, synchronization primitives, and time services on the ESP32 family. That means your firmware is not just a loop; it is a set of tasks with priorities that the scheduler runs according to policy. Understanding that model is essential when you need to reason about jitter, preemption, and deadlines in embedded autonomy. This module assumes the RTOS model and makes you structure firmware accordingly. ?cite?turn22view2?

Because FreeRTOS is the foundation, you must treat task priorities and synchronization as first-class design decisions. A low-priority task that holds a shared resource can block a higher-priority task, which shows up as jitter or missed deadlines. The exercises in this module use that tension to force you to see how task design affects latency. That experience will transfer directly to larger MCU systems with more sensors and control loops. ?cite?turn22view2?

### Interrupts and ISR/task races
ESP-IDF provides an interrupt allocation API and documents interrupt levels, which control what can and cannot run inside an ISR. This matters because ISRs must be short, deterministic, and careful about which services they call. When you mix ISR code with task-level code, you are creating a concurrency boundary that is easy to get wrong. The ISR/task race exercise in this module makes those mistakes visible. ?cite?turn22view1?

FreeRTOS is explicit that interrupt service routines must use ISR-safe API variants (the "FromISR" forms) and cannot call arbitrary kernel functions. That rule is a common source of subtle bugs when developers try to do too much work inside an interrupt. Properly deferring work to a task or queue is the safe pattern. You will practice that pattern and see what goes wrong when you violate it. ?cite?turn22view3?

### UART as a reliable host bridge
The ESP-IDF UART driver provides access to the UART peripheral for transmitting and receiving data through a standard driver API. UART remains the most common bridge between an MCU and a host system because it is simple, deterministic, and easy to debug. In this module you will build a UART-based bridge for logs and control signals, which mirrors how many robotics subsystems talk to higher-level controllers. The UART exercises force you to handle framing and buffering explicitly. ?cite?turn22view0?

A UART link is only as reliable as the firmware that manages it. Buffer sizes, interrupt-driven receive paths, and task scheduling decisions determine whether you drop bytes or meet latency targets. The UART driver gives you the primitives, but your design determines the system behavior under load. That is why the module pairs UART work with timing validation and race detection. ?cite?turn22view0?



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
