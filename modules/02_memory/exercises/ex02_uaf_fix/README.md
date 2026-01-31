# 02_memory - ex02_uaf_fix

## 1) Title + Mission
Mission: eliminate a use-after-free risk by enforcing correct ownership and object lifetime using `std::unique_ptr`. (Source: [cppreference: object lifetime](https://en.cppreference.com/w/cpp/language/lifetime))

## 2) What you are building (plain English)
You are building a safe factory function that returns a payload with a clear owner. The caller owns the payload and can safely use it without touching freed memory. (Source: [cppreference: std::unique_ptr](https://en.cppreference.com/w/cpp/memory/unique_ptr))

## 3) Why it matters (embedded/robotics/defense relevance)
Use-after-free bugs are catastrophic in embedded systems because they can corrupt memory, cause intermittent faults, and escape unit tests. A correct ownership model makes these bugs impossible rather than unlikely. (Source: [cppreference: object lifetime](https://en.cppreference.com/w/cpp/language/lifetime))

## 4) Concepts (short lecture)
Object lifetime is well-defined: it begins when storage is initialized and ends when the object is destroyed or its storage is reused. Accessing an object after its lifetime ends is undefined behavior, which can manifest as random crashes. (Source: [cppreference: object lifetime](https://en.cppreference.com/w/cpp/language/lifetime))

`std::unique_ptr` represents exclusive ownership of a heap-allocated object. When the unique pointer goes out of scope, it automatically deletes the object. This makes ownership explicit and prevents dangling pointers. (Source: [cppreference: std::unique_ptr](https://en.cppreference.com/w/cpp/memory/unique_ptr))

AddressSanitizer (ASan) is a runtime tool that detects use-after-free and other memory errors. It is a fast, practical way to confirm that your fixes work. (Source: [LLVM AddressSanitizer](https://clang.llvm.org/docs/AddressSanitizer.html))

Example (not your solution): returning a `unique_ptr` avoids returning a pointer to a local variable.
```cpp
std::unique_ptr<Payload> make_payload(int n) {
    auto p = std::make_unique<Payload>();
    // Fill with a known pattern so callers can validate results.
    for (int i = 1; i <= n; ++i) {
        p->data.push_back(i);
    }
    return p; // ownership transfers to caller
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
sudo apt-get install -y build-essential cmake ninja-build git python3 python3-venv clang clang-format clang-tidy gdb
```

Run these in **this exercise folder**:
```
cmake --version
```
Expected output (example): `cmake version 3.22.1`.

```
c++ --version
```
Expected output (example): `g++ (Ubuntu 11.4.0)` or `clang version 14.x`.

If you will use Ninja:
```
ninja --version
```
Expected output: a version number (e.g., `1.10.1`). If Ninja is missing, use the Visual Studio generator on Windows.

## 7) Build instructions (learner + solution)
### Learner path (fails initially until you implement)
```
cmake -S learner -B build_learner -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build_learner
ctest --test-dir build_learner --output-on-failure
```
Expected initial failure: compilation error due to `#error TODO_implement_exercise`.

Windows (no Ninja):
```
cmake -S learner -B build_learner -G "Visual Studio 17 2022"
cmake --build build_learner --config Debug
ctest --test-dir build_learner -C Debug --output-on-failure
```

### Solution path (must pass immediately)
```
cmake -S solution -B build_solution -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build_solution
ctest --test-dir build_solution --output-on-failure
```
Expected output: `100% tests passed`.

Windows (no Ninja):
```
cmake -S solution -B build_solution -G "Visual Studio 17 2022"
cmake --build build_solution --config Debug
ctest --test-dir build_solution -C Debug --output-on-failure
```

## 8) Step-by-step implementation instructions
1) Read `learner/src/main.cpp` and identify the lifetime hazard.
   The exercise requires a factory that returns a payload. If you returned a pointer or reference to a local variable, the object would be destroyed at function exit and any later access would be use-after-free. Your fix must guarantee the payload outlives the factory scope. (Source: [cppreference: object lifetime](https://en.cppreference.com/w/cpp/language/lifetime))
   How: find `make_payload()` and check what it returns. If it returns a pointer/reference to a local variable, that is the bug you must replace with heap ownership.
   - **Expected result:** you can explain why stack allocation is invalid for the returned payload.

2) Implement `Payload::sum()` as a read-only aggregation.
   Iterate through `data`, add each value to a local accumulator, and return it. Do not mutate the vector or store state globally. This method is the correctness check used by the tests. (Source: [cppreference: std::vector](https://en.cppreference.com/w/cpp/container/vector))
   How: loop over `data` with a range-based for loop, add each element to an `int total`, and return `total`.
   - **Expected result:** `sum()` returns 15 for the sequence {1,2,3,4,5}.

3) Implement `make_payload()` with explicit ownership transfer.
   Allocate the `Payload` on the heap with `std::make_unique<Payload>()`. Populate `data` with values 1..n, then return the `unique_ptr` by value. The returned pointer transfers ownership to the caller and guarantees the data survives beyond the factory call. (Source: [cppreference: std::unique_ptr](https://en.cppreference.com/w/cpp/memory/unique_ptr))
   How: create `auto p = std::make_unique<Payload>();`, push values into `p->data`, then `return p;`.
   - **Expected result:** the returned `unique_ptr` is non-null and valid after the function returns.

4) Remove `#error TODO_implement_exercise`, rebuild, and run tests.
   If the build fails, confirm you included `<memory>` and that your function signatures match the declarations. (Source: [cppreference: std::unique_ptr](https://en.cppreference.com/w/cpp/memory/unique_ptr))
   How: remove the `#error` line, rebuild, then run `ctest --test-dir build_learner --output-on-failure`.
   - **Expected result:** `ctest` reports `100% tests passed`.

5) Capture artifacts.
   Redirect build output to `learner/artifacts/build.log` and test output to `learner/artifacts/ctest.log` so the grader can verify you ran the commands. (Source: [cppreference: std::unique_ptr](https://en.cppreference.com/w/cpp/memory/unique_ptr))
   How: run `cmake --build build_learner > learner/artifacts/build.log 2>&1` and `ctest --test-dir build_learner --output-on-failure > learner/artifacts/ctest.log 2>&1`.
   - **Expected result:** both log files exist and contain the command output.

## 9) Verification
- `ctest --test-dir build_learner --output-on-failure` must report `100% tests passed`.
- If it fails, stop and read `troubleshooting.md`.

## 10) Artifacts to save
Place these in `learner/artifacts/`:
- `build.log` - stdout/stderr from the build step.
- `ctest.log` - stdout/stderr from the test step.
Example snippet for `ctest.log`:
```
1/1 Test #1: ...   Passed
100% tests passed, 0 tests failed out of 1
```

## 11) Grade this exercise
- Learner attempt:
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/02_memory/exercises/ex02_uaf_fix`
- Solution check:
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/02_memory/exercises/ex02_uaf_fix --use-solution`
- High-level scoring:
  - Configure/build: 40 points
  - Tests: 40 points
  - Artifacts present: 20 points

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- If build fails: ensure you included `<memory>` and removed `#error`.
- If tests fail: confirm that `make_payload()` returns a heap-allocated object and that `sum()` is correct.

## 13) Stretch goals
- Add a `validate()` method that checks the vector is non-empty and returns a boolean.
- Add an AddressSanitizer run and save the log to `learner/artifacts/asan.log`.
