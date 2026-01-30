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
   `MessageBus` owns the subscriber list. `BusView` is just a borrowed window into that list. Any method on `BusView` must be read-only and must not allocate or copy. (Source: [cppreference: std::string_view](https://en.cppreference.com/w/cpp/string/basic_string_view))
   - **Expected result:** you can explain why returning `std::string` would violate the "no copies" goal.

2) Implement `MessageBus::subscribe` to store names.
   Use `std::move` on the incoming `std::string` to avoid an extra allocation and to make ownership transfer explicit. This mirrors production code where large strings or buffers should not be copied unnecessarily. (Source: [cppreference: std::move](https://en.cppreference.com/w/cpp/utility/move))
   - **Expected result:** subscribers are stored and owned by the bus.

3) Implement `MessageBus::view` and `BusView::size`.
   `view()` should return a `BusView` that points at `subscribers_`. `size()` should safely handle a null pointer by returning zero, because a view can be default-constructed in some APIs. This prevents crashes when a caller holds an empty view. (Source: [cppreference: std::span](https://en.cppreference.com/w/cpp/container/span))
   - **Expected result:** `view.size()` matches `subscribers_.size()` and is safe if the view is empty.

4) Implement `BusView::at` using `std::string_view`.
   Return `std::string_view` so callers can inspect without copying or mutating. Do not return `std::string` or non-const references. The test compares string content, so `std::string_view` is sufficient. (Source: [cppreference: std::string_view](https://en.cppreference.com/w/cpp/string/basic_string_view))
   - **Expected result:** `view.at(i)` returns a view of the stored string.

5) Remove `#error TODO_implement_exercise`, rebuild, and run tests.
   - **Expected result:** `ctest` reports `100% tests passed`.

6) Capture artifacts.
   Save build and test output into `learner/artifacts/build.log` and `learner/artifacts/ctest.log` so the grader can verify completion.
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
