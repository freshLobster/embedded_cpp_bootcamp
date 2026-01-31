# 06_debugging - ex01_asan

## 1) Title + Mission
Mission: remove out-of-bounds behavior and validate the fix with AddressSanitizer so memory errors become observable during development. (Source: [LLVM AddressSanitizer](https://clang.llvm.org/docs/AddressSanitizer.html))

## 2) What you are building (plain English)
You are building a small, bounds-checked buffer type and a short self-test that proves reads and writes stay in range. The goal is to eliminate undefined behavior that would otherwise be silent. (Source: [cppreference: assert](https://en.cppreference.com/w/cpp/error/assert))

## 3) Why it matters (embedded/robotics/defense relevance)
Out-of-bounds writes can corrupt control data, leading to unpredictable actuator commands and nondeterministic crashes. AddressSanitizer makes these defects reproducible in the lab instead of on a robot in the field. (Source: [LLVM AddressSanitizer](https://clang.llvm.org/docs/AddressSanitizer.html))

## 4) Concepts (short lecture)
AddressSanitizer (ASan) instruments code to detect memory errors such as out-of-bounds access and use-after-free. It provides fast feedback during testing and is widely used in safety-oriented C++ development. (Source: [LLVM AddressSanitizer](https://clang.llvm.org/docs/AddressSanitizer.html))

Bounds checking is a simple, explicit guardrail. Using `assert(idx < size)` is a direct way to catch invalid access in debug builds and force you to encode the contract of your buffer API. (Source: [cppreference: assert](https://en.cppreference.com/w/cpp/error/assert))

Example (not your solution): bounds-checked access with comments.
```cpp
class SafeBuffer {
public:
    explicit SafeBuffer(size_t n) : data_(n, 0) {}
    void write(size_t idx, int value) {
        // Enforce the contract: idx must be in range.
        assert(idx < data_.size());
        data_[idx] = value;
    }
    int read(size_t idx) const {
        // Same guard on reads.
        assert(idx < data_.size());
        return data_[idx];
    }
private:
    std::vector<int> data_;
};
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
sudo apt-get install -y build-essential cmake ninja-build git python3 python3-venv clang clang-format clang-tidy gdb
```

Verify clang is available for ASan:
```
clang++ --version
```
Expected output: a version string such as `clang version 14.x`.

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

Optional ASan build (WSL/Linux):
```
cmake -S learner -B build_asan -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS="-fsanitize=address"
cmake --build build_asan
ctest --test-dir build_asan --output-on-failure
```

## 8) Step-by-step implementation instructions
1) Read `learner/src/main.cpp` and outline the API you need.
   The TODOs describe a `SafeBuffer` class and an `exercise()` self-test. Before touching code, write down the required methods (constructor, `write`, `read`) and the contract for each (index must be `< size`). This prevents you from inventing behavior while you code and makes the buffer's invariants explicit. (Source: [cppreference: assert](https://en.cppreference.com/w/cpp/error/assert))
   How: open the file, search for `TODO` and `#error`, and list each function that has a stub. Confirm that `exercise()` will call those functions; this is the harness the tests rely on.
   - **Expected result:** you can state each method and its precondition without guessing.

2) Implement `SafeBuffer` storage so size is correct immediately.
   Use `std::vector<int>` for storage and initialize it to `n` elements with value `0`. Do not use `reserve()`; it changes capacity but leaves size at 0, which would make bounds checks reject all indices. (Source: [cppreference: std::vector](https://en.cppreference.com/w/cpp/container/vector))
   How: in the constructor, either use the member-initializer list `data_(n, 0)` or call `data_.assign(n, 0)` in the body. Verify that `size()` returns `n` by temporarily adding a debug `assert(data_.size() == n);`.
   - **Expected result:** constructing `SafeBuffer(3)` yields `size() == 3`.

3) Add bounds checks in `write` and `read`.
   Both methods must enforce the same rule: `idx` is valid only when `idx < data_.size()`. This is a debug-time contract check; you are intentionally making invalid access fail fast. (Source: [cppreference: assert](https://en.cppreference.com/w/cpp/error/assert))
   How: place `assert(idx < data_.size());` as the first line in each method, then perform the access using `data_[idx]`. Use `size_t` for indices to match `vector::size()` and avoid signed/unsigned warnings.
   - **Expected result:** valid indices work; invalid indices trigger a clear assertion in debug builds.

4) Implement `exercise()` as a deterministic self-check.
   The test must not depend on random values or external input. Use a small buffer, write known values, then read them back and compare to the expected results. (Source: [cppreference: assert](https://en.cppreference.com/w/cpp/error/assert))
   How: create `SafeBuffer buf(3)`, write values 1, 2, 3 to indices 0, 1, 2, then read them back. Return a unique non-zero code for each failure so the exact failure is obvious from logs.
   - **Expected result:** `exercise()` returns 0 when all reads match expected values.

5) Remove `#error TODO_implement_exercise`, rebuild, and run tests.
   The `#error` is there to force you to finish the implementation before compiling. Only remove it after `SafeBuffer` and `exercise()` are complete. (Source: [cppreference: assert](https://en.cppreference.com/w/cpp/error/assert))
   How: re-run `cmake --build build_learner` and then `ctest --test-dir build_learner --output-on-failure`. If you see a failure, re-check the bounds check and ensure you did not use `<=` by mistake. (Source: [cppreference: std::vector::size](https://en.cppreference.com/w/cpp/container/vector/size))
   - **Expected result:** `ctest` reports `100% tests passed`.

6) Run ASan to confirm no memory errors remain (optional but recommended).
   ASan instruments your binary to detect out-of-bounds access. Even if the tests pass, ASan gives stronger evidence that your contract is enforced. (Source: [LLVM AddressSanitizer](https://clang.llvm.org/docs/AddressSanitizer.html))
   How: configure a separate build with ASan enabled, for example:
   `cmake -S learner -B build_asan -G Ninja -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_CXX_FLAGS="-fsanitize=address -fno-omit-frame-pointer"`
   Then build and run `ctest --test-dir build_asan --output-on-failure`.
   - **Expected result:** ASan reports no errors for the corrected implementation.

7) Capture artifacts for grading and review.
   You need logs for build, test, and optional ASan output. These show evidence that you ran the correct commands. (Source: [LLVM AddressSanitizer](https://clang.llvm.org/docs/AddressSanitizer.html))
   How: redirect outputs to `learner/artifacts/`:
   `cmake --build build_learner > learner/artifacts/build.log 2>&1`
   `ctest --test-dir build_learner --output-on-failure > learner/artifacts/ctest.log 2>&1`
   `ctest --test-dir build_asan --output-on-failure > learner/artifacts/asan.log 2>&1` (if you ran ASan).
   - **Expected result:** all required logs exist in the artifacts folder with readable content.

## 9) Verification
- `ctest --test-dir build_learner --output-on-failure` must report `100% tests passed`.

## 10) Artifacts to save
- `build.log` and `ctest.log` in `learner/artifacts/`.
- `asan.log` if you ran ASan.

## 11) Grade this exercise
- Learner attempt: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/06_debugging/exercises/ex01_asan`
- Solution check: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/06_debugging/exercises/ex01_asan --use-solution`

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- Build fails: confirm you included `<vector>` and `<cassert>` and removed `#error`.
- Test fails: confirm `write/read` use `<` bounds, not `<=`.

## 13) Stretch goals
- Add a `size()` accessor and test it.
- Add a negative test that intentionally triggers ASan (save the log as evidence).
