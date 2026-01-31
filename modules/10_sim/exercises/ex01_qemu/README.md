# 10_sim - ex01_qemu

## 1) Title + Mission
Mission: implement a boot log parser that detects successful startup in a QEMU-style log. (Source: [QEMU documentation](https://www.qemu.org/docs/master/))

## 2) What you are building (plain English)
You are building a small function that scans a boot log string and returns true if it contains a "Boot OK" marker. This is a lightweight check used in simulated bring-up pipelines. (Source: [QEMU documentation](https://www.qemu.org/docs/master/))

## 3) Why it matters (embedded/robotics/defense relevance)
Simulation is used to validate firmware and OS bring-up before hardware is available. Automated log parsing lets CI determine whether a boot succeeded without manual inspection. (Source: [QEMU documentation](https://www.qemu.org/docs/master/))

## 4) Concepts (short lecture)
QEMU emits console logs during boot. Searching for known markers like "Boot OK" is a common pattern for automated validation. (Source: [QEMU documentation](https://www.qemu.org/docs/master/))

String scanning with `find` is a simple, deterministic way to implement such checks. It avoids regex overhead and is easy to validate in tests. (Source: [cppreference: std::string_view::find](https://en.cppreference.com/w/cpp/string/basic_string_view/find))

Example (not your solution): simple boot marker check.
```cpp
bool boot_ok(std::string_view log) {
    // Return true only when the success marker appears.
    return log.find("Boot OK") != std::string_view::npos;
}
```

## 5) Repo context (this folder only)
- `learner/`: incomplete code you must finish. Contains its own `CMakeLists.txt`, `include/`, `src/`, `tests/`, and `artifacts/`.
- `solution/`: working reference that compiles and passes tests immediately.
- `grading/`: rubric.json used by the grader.
- `tools/`: optional helper scripts (if any).
- `troubleshooting.md`: common failure modes.
- `references.md`: links to repo-level conventions.

## 6) Prerequisites checks
Install tools (Ubuntu/WSL2, run once):
```
sudo apt-get update
sudo apt-get install -y build-essential cmake ninja-build git python3 python3-venv clang clang-format clang-tidy gdb qemu-system
```

## 7) Build instructions (learner + solution)
### Learner path (fails initially until you implement)
```
cmake -S learner -B build_learner -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build_learner
ctest --test-dir build_learner --output-on-failure
```

### Solution path (must pass immediately)
```
cmake -S solution -B build_solution -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build_solution
ctest --test-dir build_solution --output-on-failure
```

## 8) Step-by-step implementation instructions
1) Read `learner/src/main.cpp` and identify the success condition.
   The `boot_ok` function should return true only if the log contains the exact substring "Boot OK". This is a deterministic marker used by tests. (Source: [cppreference: std::string_view::find](https://en.cppreference.com/w/cpp/string/basic_string_view/find))
   How: copy the literal `"Boot OK"` from the README into your notes so you do not accidentally alter capitalization or spacing.
   - **Expected result:** you can state the exact marker string.

2) Implement `boot_ok(std::string_view log)` using `find`.
   Use `log.find("Boot OK")` and compare against `std::string_view::npos`. This is the simplest and most deterministic implementation for this exercise. (Source: [cppreference: std::string_view::find](https://en.cppreference.com/w/cpp/string/basic_string_view/find))
   How: return the boolean expression directly; do not try to parse timestamps or other log content.
   - **Expected result:** logs containing the marker return true; logs without it return false.

3) Implement `exercise()` to validate both cases.
   Test a log containing "Boot OK" and a log containing "Boot FAIL". Return 0 only if the first passes and the second fails. (Source: [cppreference: assert](https://en.cppreference.com/w/cpp/error/assert))
   How: keep the test strings short and explicit so you can see failures at a glance.
   - **Expected result:** `exercise()` returns 0 when both checks behave correctly.

4) Remove `#error TODO_implement_exercise`, rebuild, and run tests.
   If tests fail, verify that you used the exact marker string and did not include extra whitespace. (Source: [cppreference: std::string_view](https://en.cppreference.com/w/cpp/string/basic_string_view))
   How: remove the `#error`, rebuild, then run `ctest`. If the test fails, print the return value from `boot_ok` temporarily to see which case is wrong.
   - **Expected result:** `ctest` reports `100% tests passed`.

5) Capture artifacts.
   Save build output to `learner/artifacts/build.log` and test output to `learner/artifacts/ctest.log`. (Source: [QEMU documentation](https://www.qemu.org/docs/master/))
   How: redirect outputs with `> file 2>&1` so you capture any error messages.
   - **Expected result:** artifacts exist and contain your outputs.

## 9) Verification
- `ctest --test-dir build_learner --output-on-failure` must report `100% tests passed`.

## 10) Artifacts to save
- `build.log` and `ctest.log` in `learner/artifacts/`.

## 11) Grade this exercise
- Learner attempt: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/10_sim/exercises/ex01_qemu`
- Solution check: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/10_sim/exercises/ex01_qemu --use-solution`

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- Build fails: ensure `<string_view>` is included.
- Test fails: check the exact marker string.

## 13) Stretch goals
- Add support for alternative success markers.
- Add a function that extracts boot time from a log line.
