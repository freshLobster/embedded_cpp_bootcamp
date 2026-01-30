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
   The TODO asks for a bounds-checked buffer and a small `exercise()` function. Write down the functions you will implement (constructor, write, read) and the contract for each (index must be < size). This makes the expected behavior explicit before you code. (Source: [cppreference: assert](https://en.cppreference.com/w/cpp/error/assert))
   - **Expected result:** you can list the methods and their preconditions.

2) Implement a `SafeBuffer` class with internal storage.
   Use `std::vector<int>` for storage. Implement a constructor that allocates `n` elements and initializes them to zero. This keeps the object in a valid, deterministic state even before any writes. (Source: [cppreference: std::vector](https://en.cppreference.com/w/cpp/container/vector))
   - **Expected result:** constructing `SafeBuffer(3)` creates storage with size 3.

3) Add bounds-checked `write` and `read`.
   In both methods, use `assert(idx < data_.size())` before accessing the vector. Then perform the write or read. The key is that out-of-range access should fail fast in debug builds. (Source: [cppreference: assert](https://en.cppreference.com/w/cpp/error/assert))
   - **Expected result:** valid indices work; invalid indices trigger an assertion in debug builds.

4) Implement `exercise()` to validate the contract.
   Create a buffer of size 3, write values to indices 0, 1, 2, and read them back to verify correctness. Return 0 on success and non-zero on failure. This makes the test deterministic and self-contained. (Source: [cppreference: assert](https://en.cppreference.com/w/cpp/error/assert))
   - **Expected result:** `exercise()` returns 0 when read/write works correctly.

5) Remove `#error TODO_implement_exercise`, rebuild, and run tests.
   If the test fails, check that you used `size_t` consistently and that your bounds check uses `<` rather than `<=`. (Source: [cppreference: std::vector::size](https://en.cppreference.com/w/cpp/container/vector/size))
   - **Expected result:** `ctest` reports `100% tests passed`.

6) Run ASan to confirm no memory errors remain (optional but recommended).
   Build with `-fsanitize=address` and run the tests. If you still have out-of-bounds access, ASan will report it immediately with a stack trace. Save that output as part of your artifacts if it appears. (Source: [LLVM AddressSanitizer](https://clang.llvm.org/docs/AddressSanitizer.html))
   - **Expected result:** ASan reports no errors for the corrected implementation.

7) Capture artifacts.
   Redirect build output to `learner/artifacts/build.log` and test output to `learner/artifacts/ctest.log`. If you ran ASan, save the output to `learner/artifacts/asan.log`. (Source: [LLVM AddressSanitizer](https://clang.llvm.org/docs/AddressSanitizer.html))
   - **Expected result:** all required logs exist in the artifacts folder.

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
