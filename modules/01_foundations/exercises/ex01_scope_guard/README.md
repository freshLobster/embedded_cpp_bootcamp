# 01_foundations - ex01_scope_guard

## 1) Title + Mission
Mission: Implement a RAII scope guard that invokes cleanup exactly once on scope exit and supports move-only transfer and explicit dismissal.【https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines†L10094-L10094】

## 2) What you are building (plain English)
You are building a minimal scope guard type that owns a cleanup action and runs it deterministically when the guard leaves scope, mirroring how critical resources are safely released in C++.【https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines†L10094-L10094】

## 3) Why it matters (embedded/robotics/defense relevance)
Mission-critical software cannot rely on humans to remember cleanup paths; deterministic scope-based cleanup avoids leaks and double-releases even when control flow changes unexpectedly.【https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines†L10094-L10094】

## 4) Concepts (short lecture)
RAII ties resource lifetime to object lifetime so cleanup is automatic and deterministic, which is foundational for safe embedded systems where failure paths are common.【https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines†L10094-L10094】

A scope guard is a move-only owner of a cleanup callback. Move-only semantics matter because the cleanup must run exactly once; copying would duplicate ownership. The rule of three/five/zero explains when you must define copy and move operations explicitly for resource owners.【https://en.cppreference.com/w/cpp/language/rule_of_three†L501-L501】

The guard stores a callable (typically a lambda) and invokes it in the destructor if it is still active. `std::function` is a type-erased callable holder; it can be empty or contain a target callable, which makes it a convenient wrapper for a cleanup callback.【https://en.cppreference.com/w/cpp/utility/functional/function†L569-L569】

Example (not your solution): a minimal guard skeleton that still needs correct move semantics.
```cpp
class Guard {
public:
    explicit Guard(std::function<void()> fn) : fn_(std::move(fn)) {}
    Guard(const Guard&) = delete;
    Guard& operator=(const Guard&) = delete;
    ~Guard() { if (active_ && fn_) fn_(); }
    void dismiss() { active_ = false; }
    // TODO: add move constructor/assignment that transfer ownership.
private:
    std::function<void()> fn_;
    bool active_{true};
};
```

Example usage (not your solution):
```cpp
bool cleaned = false;
{ Guard g([&] { cleaned = true; }); }
// cleaned must be true after scope exit.
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
1) Open `learner/src/main.cpp` and read the ScopeGuard skeleton and TODO comments.
   - Identify which operations are deleted, which must be implemented, and how the tests in `exercise()` check behavior.
   - **Expected result:** you can describe when the callback must run and when it must not.
2) Implement the constructor and `dismiss()`.
   - The constructor should store the callable and mark the guard active.
   - `dismiss()` should permanently disable cleanup without destroying the callable.
   - **Expected result:** you can create a guard and stop it from firing on scope exit.
3) Implement the destructor.
   - If the guard is active and the callable is non-empty, invoke it exactly once.
   - Avoid throwing from the destructor (keep it noexcept by behavior).
   - **Expected result:** callbacks run when the guard leaves scope unless dismissed.
4) Implement move constructor and move assignment.
   - Transfer the callable and the `active_` state.
   - Ensure the source guard is dismissed after the move to prevent double execution.
   - If move-assigning onto an active guard, run its current cleanup before overwriting (the tests depend on exact-once semantics).
   - **Expected result:** moving a guard transfers ownership and cleanup still runs exactly once.
5) Remove `#error TODO_implement_exercise`, rebuild, and run tests.
   - **Expected result:** `ctest` reports `100% tests passed`.
6) Save artifacts.
   - Copy build/test output into `learner/artifacts/build.log` and `learner/artifacts/ctest.log`.
   - **Expected result:** both files exist and contain the command output.

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
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/01_foundations/exercises/ex01_scope_guard`
- Solution check:
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/01_foundations/exercises/ex01_scope_guard --use-solution`
- High-level scoring:
  - Configure/build: 40 points
  - Tests: 40 points
  - Artifacts present: 20 points

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- If build fails: verify CMake + compiler version.
- If tests fail: re-check your logic against the required behavior.

## 13) Stretch goals
- Add a guard that can be constructed from any callable without heap allocation.
- Add a small test to verify that move-assigning a dismissed guard does not invoke the callback.
