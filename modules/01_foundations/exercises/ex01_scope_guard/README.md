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
1) Read the ScopeGuard skeleton in `learner/src/main.cpp` and map each method to a behavior in `exercise()`.
   The tests define the contract: (a) cleanup runs on scope exit, (b) cleanup does not run when dismissed, and (c) cleanup runs exactly once after a move. For each check in `exercise()`, write a short note in your own words describing which method must make that check pass. This forces you to reason about invariants before coding. (Source: [C++ Core Guidelines, RAII (R.1)](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines))
   How: create a small table with each `exercise()` block in the left column and the method(s) responsible in the right column (constructor, destructor, dismiss, move ctor, move assign).
   - **Expected result:** you can explain, line by line, which invariants are being tested and which method establishes them.

2) Implement the constructor and `dismiss()` to establish the guard's state machine.
   In the constructor, move the callback into `fn_` and set `active_ = true`. This makes the guard responsible for calling the cleanup later. In `dismiss()`, flip `active_` to false and do nothing else; do not call the callback here. The goal is that "active means will run on destruction" and "dismissed means will never run." This separation keeps ownership (the stored function) independent from the execution decision (the active flag). (Source: [cppreference: std::function](https://en.cppreference.com/w/cpp/utility/functional/function))
   How: in the constructor body, use `fn_(std::move(fn))` and set `active_` to `true`. In `dismiss()`, set `active_ = false` and do not touch `fn_`.
   - **Expected result:** you can create a guard and then call `dismiss()` without invoking the callback.

3) Implement the destructor with a strict "exactly once" rule.
   The destructor should check `active_` first, then check `fn_` is non-empty, then invoke it. Do not throw or allocate in the destructor. You may optionally set `active_ = false` after invoking to make repeated calls impossible in debug builds. This is the core RAII behavior: cleanup runs at scope exit regardless of how the scope ends. (Source: [C++ Core Guidelines, RAII (R.1)](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines))
   How: guard the call with `if (active_ && fn_) { fn_(); active_ = false; }` and keep the body minimal.
   - **Expected result:** a guard that reaches scope exit without `dismiss()` will always invoke its callback once.

4) Implement the move constructor with ownership transfer.
   Move the callback and copy the active flag from `other`. Immediately call `other.dismiss()` so the moved-from guard is inert. This avoids double invocation when both guards are destroyed. This step makes "exactly once" true even when ownership is transferred mid-scope. (Source: [cppreference: Rule of Three/Five](https://en.cppreference.com/w/cpp/language/rule_of_three))
   How: in the member initializer list, `fn_(std::move(other.fn_))` and `active_(other.active_)`, then call `other.dismiss()` in the body.
   - **Expected result:** a moved-from guard will not trigger cleanup on destruction; the moved-to guard will.

5) Implement move assignment using "clean up then overwrite."
   If `*this` currently owns an active cleanup, you must run it before you overwrite `fn_` and `active_`. Otherwise you would leak a cleanup action. After cleaning up (if needed), move the callback and active flag from `other`, then dismiss `other`. This ordering is crucial: "old resource cleaned, new resource owned." (Source: [C++ Core Guidelines, RAII (R.1)](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines))
   How: inside `operator=`, first check `if (active_ && fn_) { fn_(); }`, then move `fn_` and `active_` from `other`, and finally call `other.dismiss()`.
   - **Expected result:** move-assigning onto an active guard does not lose or duplicate cleanup.

6) Remove `#error TODO_implement_exercise` and compile.
   Run the learner build commands. If you hit a compiler error, fix missing includes or signature mismatches first. Only then run `ctest`. (Source: [C++ Core Guidelines, RAII (R.1)](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines))
   How: delete the `#error` line, rebuild, and run `ctest --test-dir build_learner --output-on-failure` to confirm the self-check passes.
   - **Expected result:** compilation succeeds and `ctest` reports `100% tests passed`.

7) Capture artifacts exactly as the grader expects.
   Redirect the build output to `learner/artifacts/build.log` and the test output to `learner/artifacts/ctest.log`. These files are evidence that you ran the correct commands. (Source: [C++ Core Guidelines, RAII (R.1)](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines))
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
