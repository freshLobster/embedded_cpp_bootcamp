# 01_foundations - ex01_scope_guard

## 1) Title + Mission
Mission: implement a move-only RAII scope guard that runs a cleanup callback exactly once at scope exit unless dismissed. This is the smallest useful building block for deterministic cleanup in embedded C++ where control flow can fail early. (Source: [C++ Core Guidelines, RAII (R.1)](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines))

## 2) What you are building (plain English)
You are building a tiny class that owns a cleanup action and guarantees that the action runs when the guard object leaves scope. Think of it as a "safety net" that closes a file, releases a lock, or restores a hardware register when code exits early. (Source: [C++ Core Guidelines, RAII (R.1)](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines))

## 3) Why it matters (embedded/robotics/defense relevance)
Autonomy and embedded systems often have multiple exit paths (errors, timeouts, exception-like early returns). A scope guard makes cleanup deterministic and reduces risk of leaks, deadlocks, or inconsistent hardware state when you leave a scope unexpectedly. This is especially important in mission-critical code where "forgot to release" bugs can be catastrophic. (Source: [C++ Core Guidelines, RAII (R.1)](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines))

## 4) Concepts (short lecture)
RAII (Resource Acquisition Is Initialization) ties resource ownership to object lifetime: the constructor "acquires" the resource, and the destructor "releases" it. In practice, it means the cleanup runs no matter how the scope exits, which is the safest pattern for firmware, robotics, and autonomy systems that must be correct under faults. (Source: [C++ Core Guidelines, RAII (R.1)](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines))

Move-only ownership is crucial for a scope guard because the cleanup action must execute exactly once. If you allow copying, two guards might attempt to run the same cleanup, causing double free or double unlock. The Rule of Five explains when a class that owns resources must explicitly define or delete copy/move operations. (Source: [cppreference: Rule of Three/Five](https://en.cppreference.com/w/cpp/language/rule_of_three))

The cleanup action is typically a callable object. `std::function` is a type-erased wrapper that can store any callable with a given signature. It can be empty, which lets you treat "no cleanup" as a valid state. (Source: [cppreference: std::function](https://en.cppreference.com/w/cpp/utility/functional/function))

Example (not your solution): minimal RAII guard shape. Notice the comments describing why each decision exists.
```cpp
class Guard {
public:
    // Store the callback by value so it outlives the caller's scope.
    explicit Guard(std::function<void()> fn) : fn_(std::move(fn)) {}

    // Disallow copy to prevent double cleanup.
    Guard(const Guard&) = delete;
    Guard& operator=(const Guard&) = delete;

    // Destructor triggers cleanup if still active.
    ~Guard() { if (active_ && fn_) fn_(); }

    // Dismiss disables the cleanup path when it is no longer needed.
    void dismiss() { active_ = false; }

    // TODO: provide move constructor/assignment for transfer of ownership.
private:
    std::function<void()> fn_;
    bool active_{true};
};
```

Example usage (not your solution): cleanup runs on scope exit.
```cpp
bool cleaned = false;
{
    // The lambda captures by reference; the guard owns the lambda.
    Guard g([&] { cleaned = true; });
} // cleanup runs here
// cleaned must be true after the scope exits.
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
1) Read the ScopeGuard skeleton in `learner/src/main.cpp` and trace the tests in `exercise()`.
   The tests define the exact behavior: cleanup must run on scope exit, must not run if dismissed, and must still run exactly once after a move. You should be able to articulate which line in `exercise()` is proving which invariant. (Source: [C++ Core Guidelines, RAII (R.1)](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines))
   - **Expected result:** you can explain the three invariants in plain English and point to the test lines that enforce them.

2) Implement the constructor and `dismiss()` first, because they define the basic state machine.
   The constructor should store the callable by value and mark the guard as active. `dismiss()` should only flip a flag; it should not invoke the callback. This separates "ownership" (the stored callable) from "should I run it?" (the active flag). (Source: [cppreference: std::function](https://en.cppreference.com/w/cpp/utility/functional/function))
   - **Expected result:** a guard can be created and dismissed without running cleanup.

3) Implement the destructor to enforce the "exactly once" cleanup contract.
   In a destructor, you must avoid exceptions; just check `active_` and whether the callable is non-empty before invoking it. This is the RAII core: cleanup executes on scope exit no matter how the scope ends. (Source: [C++ Core Guidelines, RAII (R.1)](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines))
   - **Expected result:** the cleanup runs at end of scope unless dismissed.

4) Implement the move constructor.
   Move must transfer both the callable and the active flag. After moving, dismiss the source guard so it cannot run cleanup. This prevents double cleanup while still allowing transfer of ownership. (Source: [cppreference: Rule of Three/Five](https://en.cppreference.com/w/cpp/language/rule_of_three))
   - **Expected result:** moved-from guard is inert; moved-to guard owns cleanup.

5) Implement the move assignment operator with "clean up then overwrite."
   If the current guard is active, run its cleanup before you overwrite its callable. Then move the callable and active flag from the source and dismiss the source. This ordering avoids leaks (skipping cleanup) and avoids double cleanup. (Source: [C++ Core Guidelines, RAII (R.1)](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines))
   - **Expected result:** move assignment is safe even when the left-hand guard is active.

6) Remove `#error TODO_implement_exercise`, rebuild, and run tests.
   - **Expected result:** `ctest` reports `100% tests passed`.

7) Capture artifacts.
   Save the build and test output into `learner/artifacts/build.log` and `learner/artifacts/ctest.log` so the grader can verify evidence of completion.
   - **Expected result:** the two log files exist and contain your build/test output.

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
- If build fails: verify CMake + compiler version and ensure you removed the `#error`.
- If tests fail: inspect which return code failed in `exercise()` and match it to the invariant described in Step 1.

## 13) Stretch goals
- Implement a templated `ScopeGuard<F>` that avoids `std::function` heap allocation for small callables.
- Add a regression test to ensure move-assigning onto a dismissed guard does not call cleanup.
