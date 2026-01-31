# 01_foundations - ex02_message_bus_view

## 1) Title + Mission
Mission: implement a const-correct, non-owning "view" of a message bus subscriber list that exposes read-only access without copying. This is a core API design skill for real-time systems where ownership boundaries must be explicit. (Source: [cppreference: std::string_view](https://en.cppreference.com/w/cpp/string/basic_string_view))

## 2) What you are building (plain English)
You are building a lightweight wrapper that lets callers inspect subscribers without taking ownership or modifying the underlying list. The view is like a transparent window: it shows what is inside, but it cannot change or own the storage. (Source: [cppreference: std::string_view](https://en.cppreference.com/w/cpp/string/basic_string_view))

## 3) Why it matters (embedded/robotics/defense relevance)
Passing ownership through API boundaries is expensive and risky in embedded systems. Views avoid unnecessary allocations and keep ownership explicit, which reduces latency spikes and prevents accidental mutation of shared state. This is especially important in autonomy pipelines where data is shared across threads and components. (Source: [cppreference: std::span](https://en.cppreference.com/w/cpp/container/span))

## 4) Concepts (short lecture)
`std::string_view` is a non-owning view of a character sequence. It stores a pointer and a length, which means it does not allocate or copy. The caller must ensure the underlying string outlives the view. This is perfect for read-only inspection without copying. (Source: [cppreference: std::string_view](https://en.cppreference.com/w/cpp/string/basic_string_view))

`std::span` is the generalization of this idea for arbitrary contiguous sequences (e.g., arrays and `std::vector`). A `span` does not own its elements, so it is a fast, safe way to "borrow" a range of objects for read-only access. The same lifetime rule applies: the owner must outlive the view. (Source: [cppreference: std::span](https://en.cppreference.com/w/cpp/container/span))

Const-correctness is an API contract: if a function promises read-only access, it must return const references or views so callers cannot mutate state through the API. This prevents accidental modification of shared data structures. (Source: [cppreference: const and constness](https://en.cppreference.com/w/cpp/language/cv))

Example (not your solution): read-only view over `std::vector<std::string>` with comments showing the non-owning contract.
```cpp
class BusView {
public:
    // The view stores only a pointer; it does not own the vector.
    explicit BusView(const std::vector<std::string>* subs) : subs_(subs) {}

    // Size returns 0 if the pointer is null; no mutation is possible here.
    size_t size() const { return subs_ ? subs_->size() : 0; }

    // Return a non-owning view into the string storage.
    std::string_view at(size_t i) const { return (*subs_)[i]; }
private:
    const std::vector<std::string>* subs_{nullptr};
};
```

Example usage (not your solution):
```cpp
MessageBus bus;
// Subscribe registers ownership inside the bus.
bus.subscribe("imu");
BusView v = bus.view();
// v.at(0) is a string_view; it does not copy or allocate.
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
1) Read `learner/src/main.cpp` and identify the ownership boundary.
   `MessageBus` owns the `std::vector<std::string>`; `BusView` is only a non-owning lens. That means `BusView` must never allocate or copy, and it must never allow mutation. If you returned `std::string` or a non-const reference, you would either copy or allow modification, both of which violate the contract. (Source: [cppreference: std::string_view](https://en.cppreference.com/w/cpp/string/basic_string_view))
   How: draw a simple diagram showing `MessageBus` owning the vector and `BusView` pointing to it. Note that the view must become invalid if the bus is destroyed.
   - **Expected result:** you can explain, in one sentence, why a view must never outlive the bus.

2) Implement `MessageBus::subscribe` to store names with explicit ownership.
   The parameter is passed by value so the caller can pass an rvalue or lvalue. Inside, move it into `subscribers_` with `push_back(std::move(name))` so the bus becomes the sole owner of the string. This mirrors real systems where message metadata is owned by the bus and should not be duplicated. (Source: [cppreference: std::move](https://en.cppreference.com/w/cpp/utility/move))
   How: implement the function body in one line: `subscribers_.push_back(std::move(name));` and do not return anything.
   - **Expected result:** after subscribing, the bus owns the string and no extra copies are made.

3) Implement `MessageBus::view` and `BusView::size` with null safety.
   `view()` should return `BusView(&subscribers_)`. In `BusView::size`, check `subs_` for null and return 0 if it is null. This makes the view safe even if a caller constructs a default view or if a future API returns an empty view. (Source: [cppreference: std::span](https://en.cppreference.com/w/cpp/container/span))
   How: in `view()`, return a `BusView` constructed with the address of the vector. In `size()`, use `return subs_ ? subs_->size() : 0;`.
   - **Expected result:** `view.size()` is correct and never crashes when the view is empty.

4) Implement `BusView::at` to return `std::string_view`.
   Access the string in the vector and return a `string_view` that refers to it. Do not return `std::string` or a mutable reference. This ensures zero-copy, read-only access and preserves the bus's ownership boundary. (Source: [cppreference: std::string_view](https://en.cppreference.com/w/cpp/string/basic_string_view))
   How: return `std::string_view((*subs_)[idx])` (after ensuring `subs_` is non-null in your logic or by relying on the test inputs).
   - **Expected result:** the returned view compares equal to the stored name but does not allocate.

5) Remove `#error TODO_implement_exercise`, rebuild, and run tests.
   If compilation fails, double-check that your method signatures match the declarations and that you did not return a temporary `std::string` from `at`. (Source: [cppreference: std::string_view](https://en.cppreference.com/w/cpp/string/basic_string_view))
   How: remove the `#error` line, rebuild, then run `ctest --test-dir build_learner --output-on-failure`.
   - **Expected result:** `ctest` reports `100% tests passed`.

6) Capture artifacts.
   Redirect build output to `learner/artifacts/build.log` and test output to `learner/artifacts/ctest.log` so grading can verify your work. (Source: [cppreference: std::string_view](https://en.cppreference.com/w/cpp/string/basic_string_view))
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
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/01_foundations/exercises/ex02_message_bus_view`
- Solution check:
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/01_foundations/exercises/ex02_message_bus_view --use-solution`
- High-level scoring:
  - Configure/build: 40 points
  - Tests: 40 points
  - Artifacts present: 20 points

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- If build fails: verify CMake + compiler version and remove the `#error`.
- If tests fail: confirm `BusView` returns views, not copies, and that `size()` handles null safely.

## 13) Stretch goals
- Add `begin()`/`end()` to iterate over subscribers without exposing mutation.
- Add a safe bounds check and return an empty `std::string_view` for out-of-range indices.
