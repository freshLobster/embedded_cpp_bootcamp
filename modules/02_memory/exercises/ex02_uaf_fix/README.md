# 02_memory - ex02_uaf_fix

## 1) Title + Mission
Mission: Fix a use-after-free pattern by enforcing correct ownership and lifetime in the API you implement.【https://en.cppreference.com/w/cpp/language/lifetime†L494-L494】

## 2) What you are building (plain English)
You are building a safe factory and access path for a payload so that consumers never access objects after their lifetime ends.【https://en.cppreference.com/w/cpp/language/lifetime†L494-L494】

## 3) Why it matters (embedded/robotics/defense relevance)
Use-after-free is undefined behavior with catastrophic consequences; eliminating it requires explicit ownership and a correct mental model of object lifetime.【https://en.cppreference.com/w/cpp/language/lifetime†L494-L494】

## 4) Concepts (short lecture)
C++ object lifetimes begin and end at precise points. Accessing an object after its lifetime ends is undefined behavior and can manifest as rare, difficult-to-debug crashes in the field.【https://en.cppreference.com/w/cpp/language/lifetime†L494-L494】

`std::unique_ptr` represents exclusive ownership of an object and releases it automatically when it goes out of scope. Returning a `unique_ptr` from a factory is the simplest way to guarantee the caller owns the data and prevents use-after-free of stack-allocated temporaries.【https://en.cppreference.com/w/cpp/memory/unique_ptr†L510-L510】

AddressSanitizer is a fast memory error detector that can catch use-after-free bugs during testing, making lifetime errors visible before deployment.【https://clang.llvm.org/docs/AddressSanitizer.html†L85-L85】

Example (not your solution): a safe factory that returns ownership.
```cpp
std::unique_ptr<Payload> make_payload(int n) {
    auto p = std::make_unique<Payload>();
    for (int i = 0; i < n; ++i) p->data.push_back(i);
    return p; // caller owns the payload
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

Optional heap profiling:
```
sudo apt-get install -y valgrind
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


## 8) Step-by-step implementation instructions
1) Open `learner/src/main.cpp` and read the `Payload` and factory TODOs.
   - Identify where the original use-after-free would occur and what ownership should look like.
   - **Expected result:** you can state who owns the payload after creation.
2) Implement the `Payload` data structure and `sum()` helper.
   - Keep it simple and deterministic so tests are stable.
   - **Expected result:** `sum()` produces the expected total.
3) Implement a safe factory that returns ownership.
   - Use `std::unique_ptr` and never return references to local objects.
   - **Expected result:** the caller can safely access the payload after the factory returns.
4) Update `exercise()` to build and validate a payload and remove `#error`.
5) Build, run tests, and save artifacts.

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
- If build fails: verify CMake + compiler version.
- If tests fail: re-check your logic against the required behavior.

## 13) Stretch goals
- Add a test that verifies empty payload behavior.
- Add a `make_payload(size_t count, int start)` overload and validate it.
