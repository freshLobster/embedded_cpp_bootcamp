# 06_debugging - ex03_gdb_remote

## 1) Title + Mission
Mission: implement a deterministic checksum routine and use it to practice remote debugging workflows. (Source: [RFC 1071](https://www.rfc-editor.org/rfc/rfc1071))

## 2) What you are building (plain English)
You are building a small checksum function and a call chain that makes it easy to practice stepping and inspecting values in a debugger. The checksum itself is simple, but the goal is to make the debug flow repeatable. (Source: [RFC 1071](https://www.rfc-editor.org/rfc/rfc1071))

## 3) Why it matters (embedded/robotics/defense relevance)
Remote debugging on embedded targets is common in autonomy systems. A deterministic function with a clear call chain lets you verify your debugging setup, symbol loading, and stack inspection before you debug real faults. (Source: [GDB manual](https://sourceware.org/gdb/current/onlinedocs/gdb/))

## 4) Concepts (short lecture)
Checksums are a lightweight integrity mechanism. While not cryptographically secure, they are often used in low-level protocols to detect corruption and make debugging more trustworthy. (Source: [RFC 1071](https://www.rfc-editor.org/rfc/rfc1071))

GDB and gdbserver let you debug a program running on a different machine. This is the standard pattern for SBCs and MCUs where you cannot easily run the debugger locally. (Source: [GDB manual](https://sourceware.org/gdb/current/onlinedocs/gdb/))

Example (not your solution): simple checksum over a string.
```cpp
int checksum(std::string_view s) {
    int sum = 0;
    for (unsigned char c : s) {
        // Add each byte to a running total.
        sum += static_cast<int>(c);
    }
    return sum;
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
sudo apt-get install -y build-essential cmake ninja-build git python3 python3-venv clang clang-format clang-tidy gdb gdbserver
```

Verify gdb and gdbserver:
```
gdb --version
gdbserver --version
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
1) Read `learner/src/main.cpp` and define the behavior you need.
   The TODO asks for a checksum routine and a predictable call chain. The solution should be simple and deterministic so that you can step through it in a debugger and see expected values. (Source: [GDB manual](https://sourceware.org/gdb/current/onlinedocs/gdb/))
   - **Expected result:** you can describe the checksum algorithm in one sentence.

2) Implement `checksum` as a byte-sum.
   Iterate over each byte in a `std::string_view` and add its value to a running integer sum. Use `unsigned char` to avoid sign-extension issues. This makes the checksum repeatable across platforms. (Source: [RFC 1071](https://www.rfc-editor.org/rfc/rfc1071))
   - **Expected result:** checksum("GDB") returns a positive integer.

3) Implement `exercise()` to drive the checksum.
   Call `checksum("GDB")` and validate that the return value is greater than zero. Return 0 on success and non-zero on failure. This creates a minimal, predictable call chain for debugging. (Source: [GDB manual](https://sourceware.org/gdb/current/onlinedocs/gdb/))
   - **Expected result:** `exercise()` returns 0 when checksum is implemented correctly.

4) Remove `#error TODO_implement_exercise`, rebuild, and run tests.
   If tests fail, check that you included `<string_view>` and that your loop uses unsigned bytes. (Source: [RFC 1071](https://www.rfc-editor.org/rfc/rfc1071))
   - **Expected result:** `ctest` reports `100% tests passed`.

5) Practice local debugging with gdb.
   Run `gdb ./build_learner/ex03_gdb_remote`, set a breakpoint on `checksum`, and step through the loop. Inspect `sum` as it updates. This ensures your symbols and debug flow are correct before going remote. (Source: [GDB manual](https://sourceware.org/gdb/current/onlinedocs/gdb/))
   - **Expected result:** you can step through the loop and observe `sum` changing.

6) (Optional) practice remote debugging with gdbserver.
   Start `gdbserver :1234 ./build_learner/ex03_gdb_remote` on the target, then connect from your host: `gdb` -> `target remote <ip>:1234`. Set breakpoints and step as above. (Source: [GDB manual](https://sourceware.org/gdb/current/onlinedocs/gdb/))
   - **Expected result:** breakpoints hit on the target and values are visible remotely.

7) Capture artifacts.
   Save build output to `learner/artifacts/build.log`, test output to `learner/artifacts/ctest.log`, and any gdb session notes to `learner/artifacts/gdb_notes.txt`. (Source: [GDB manual](https://sourceware.org/gdb/current/onlinedocs/gdb/))
   - **Expected result:** artifacts exist and contain your command outputs.

## 9) Verification
- `ctest --test-dir build_learner --output-on-failure` must report `100% tests passed`.

## 10) Artifacts to save
- `build.log` and `ctest.log` in `learner/artifacts/`.
- `gdb_notes.txt` with key commands and observations.

## 11) Grade this exercise
- Learner attempt: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/06_debugging/exercises/ex03_gdb_remote`
- Solution check: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/06_debugging/exercises/ex03_gdb_remote --use-solution`

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- Build fails: ensure `<string_view>` is included and `checksum` is defined.
- Test fails: check your loop and ensure you sum bytes as unsigned.

## 13) Stretch goals
- Add a second function in the call chain and practice stepping across it.
- Add a command list in `gdb` to print `sum` at each breakpoint.
