# Module 06_debugging - Debugging

**Mission:** Sanitizers, gdb/gdbserver, artifacts.

**Estimated time:** 2-4 hours.

## Setup checklist (WSL2 primary, Windows notes)
- WSL2 Ubuntu: `sudo apt-get update && sudo apt-get install -y build-essential cmake ninja-build git python3 python3-venv clang clang-format clang-tidy gdb`
- Verify compiler: `clang++ --version` (expect version output). On Windows native: open "x64 Native Tools" and run `cl /?`.
- Repo root contains `CMakePresets.json` and `tools/grader/grade.py`.
## Lecture

### Memory safety and undefined behavior detection
AddressSanitizer (ASan) is a runtime memory error detector for C and C++ that catches issues like use-after-free, heap buffer overflows, and stack buffer overflows. It works by instrumenting code at compile time and adding runtime checks, which makes it ideal for finding safety bugs that are otherwise nondeterministic. In embedded and defense systems, ASan is a fast feedback tool for hardening memory safety before field testing. You will use it in this module to make memory faults reproducible and visible. ([AddressSanitizer](https://clang.llvm.org/docs/AddressSanitizer.html))

UndefinedBehaviorSanitizer (UBSan) targets undefined behavior in C/C++ that can lead to silent miscompilations or unpredictable failures. It instruments operations that are undefined by the language rules and reports when they occur at runtime. In safety-critical code, the goal is to eliminate UB entirely because compilers are allowed to assume it never happens. UBSan makes those assumptions explicit and testable. ([UndefinedBehaviorSanitizer](https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html))

### Concurrency bugs and data races
ThreadSanitizer (TSan) is a data race detector for C/C++ that finds concurrent accesses that are not properly synchronized. Data races are especially pernicious in robotics pipelines because they appear only under specific timing and load conditions. TSan provides concrete, stack-trace-level evidence of races, which turns "heisenbugs" into actionable defects. The exercises here force you to observe and then eliminate a race using proper synchronization. ([ThreadSanitizer](https://clang.llvm.org/docs/ThreadSanitizer.html))

Dynamic race detection still requires interpretation. A TSan report tells you where the conflicting accesses occurred, but you must decide whether to fix it with locks, atomics, or a redesign to reduce shared state. That design step is why this module pairs sanitizer work with a logging artifact and a fix-proof step. Your goal is to be able to explain the race in a code review and demonstrate the correction with the sanitizer output. ([ThreadSanitizer](https://clang.llvm.org/docs/ThreadSanitizer.html))

### Remote debugging with gdbserver
`gdbserver` runs on the target system and communicates with a host GDB to debug a program remotely. The standard usage is `gdbserver COMM PROGRAM`, which starts the program under control of the remote debugger so you can attach from your development machine. This is the core workflow for SBC and MCU debugging when you cannot run a full debugger locally. The module's remote debugging exercise mirrors the real workflow used on fielded hardware. ([GDB Server](https://sourceware.org/gdb/current/onlinedocs/gdb/GDB-Server.html))

Remote debugging is more than "attach and step"; it is about verifying that build artifacts, symbols, and runtime behavior match what you expect on the target. The gdbserver model enforces that separation and forces you to treat the target as the truth source for timing and IO. That mindset matters when your Windows host is not representative of ARM Linux or microcontroller behavior. You will capture logs and debugger transcripts as proof of correctness. ([GDB Server](https://sourceware.org/gdb/current/onlinedocs/gdb/GDB-Server.html))



## Start here
1) Pick one exercise folder below and `cd` into it.
2) Follow the exercise README exactly; it includes build/test commands and grading steps.
3) Save outputs in that exercise's `learner/artifacts/`.

## Exercises (per-folder)
| Exercise | Link |
|---|---|
| ex01_asan | [ex01_asan](exercises/ex01_asan/README.md) |
| ex02_tsan | [ex02_tsan](exercises/ex02_tsan/README.md) |
| ex03_gdb_remote | [ex03_gdb_remote](exercises/ex03_gdb_remote/README.md) |

## Done definition
- Each exercise you attempt has passing tests and saved artifacts.
- The per-exercise grader reports a numeric score.
- Module-level artifacts (if any) are stored in `modules/06_debugging/artifacts/`.

## Grade this module
- Module-level grader: `python3 tools/grader/grade.py --module modules/06_debugging`
- JSON: `python3 tools/grader/grade.py --module 06 --json`
- Per-exercise grading is done inside each exercise folder README.
