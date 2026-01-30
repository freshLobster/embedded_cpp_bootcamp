# 01_foundations - ex02_message_bus_view

## 1) Title + Mission
Mission: Implement a const-correct, non-owning bus view that exposes subscribers without copying or allowing mutation.【https://en.cppreference.com/w/cpp/container/span†L400-L400】

## 2) What you are building (plain English)
You are building a read-only view type that provides non-owning access to subscriber metadata, so callers can inspect without taking ownership or modifying the underlying storage.【https://en.cppreference.com/w/cpp/string/basic_string_view†L389-L389】

## 3) Why it matters (embedded/robotics/defense relevance)
In autonomy pipelines, passing views instead of owning copies preserves performance and keeps ownership boundaries explicit, which reduces accidental allocations and data races.【https://en.cppreference.com/w/cpp/container/span†L400-L400】

## 4) Concepts (short lecture)
`std::string_view` and `std::span` are non-owning views: they refer to a contiguous sequence of characters or objects without managing lifetime. This allows zero-copy inspection when a consumer only needs read access.【https://en.cppreference.com/w/cpp/string/basic_string_view†L389-L389】【https://en.cppreference.com/w/cpp/container/span†L400-L400】

Const-correctness matters for APIs that expose internal state. A read-only view should not allow modification of the underlying container, which means the view should return `std::string_view` or `const` references and never non-const accessors.【https://en.cppreference.com/w/cpp/string/basic_string_view†L389-L389】

A view must never outlive the storage it refers to. The safest mental model is that the view is a temporary lens that is valid only as long as the owning `MessageBus` object is alive and has not reallocated its storage.【https://en.cppreference.com/w/cpp/container/span†L400-L400】

Example (not your solution): a view over a vector of strings using `std::string_view`.
```cpp
class BusView {
public:
    explicit BusView(const std::vector<std::string>* subs) : subs_(subs) {}
    size_t size() const { return subs_ ? subs_->size() : 0; }
    std::string_view at(size_t i) const { return (*subs_)[i]; }
private:
    const std::vector<std::string>* subs_{nullptr};
};
```

Example usage (not your solution):
```cpp
MessageBus bus;
bus.subscribe("imu");
BusView v = bus.view();
// v.at(0) returns a string_view without copying.
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
1) Open `learner/src/main.cpp` and review the `MessageBus` and `BusView` skeletons.
   - Identify which methods must be const and which should avoid copying.
   - **Expected result:** you can explain why `BusView` must not own data.
2) Implement `MessageBus::subscribe`.
   - Store the subscriber name in the internal container (move from the parameter).
   - **Expected result:** the bus stores names without additional copies.
3) Implement `MessageBus::view` and `BusView::size`.
   - `view()` should return a `BusView` that refers to the internal container.
   - `size()` should handle the null-pointer case safely.
   - **Expected result:** `view.size()` matches the subscriber count.
4) Implement `BusView::at` to return a `std::string_view`.
   - Do not return `std::string` or a mutable reference.
   - **Expected result:** callers can read values without modifying them.
5) Remove `#error TODO_implement_exercise`, rebuild, and run tests.
   - **Expected result:** `ctest` reports `100% tests passed`.
6) Save artifacts in `learner/artifacts/`.

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
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/01_foundations/exercises/ex02_message_bus_view`
- Solution check:
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/01_foundations/exercises/ex02_message_bus_view --use-solution`
- High-level scoring:
  - Configure/build: 40 points
  - Tests: 40 points
  - Artifacts present: 20 points

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- If build fails: verify CMake + compiler version.
- If tests fail: re-check your logic against the required behavior.

## 13) Stretch goals
- Add bounds checking and return an empty view for invalid indices.
- Implement a `BusView::begin()/end()` pair to allow ranged-for iteration.
