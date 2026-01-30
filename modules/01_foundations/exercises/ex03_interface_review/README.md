# 01_foundations - ex03_interface_review

## 1) Title + Mission
Mission: refactor a small owning type to follow the Rule of Five and correct move semantics, then prove the moved-from state is safe and predictable. (Source: [cppreference: Rule of Three/Five](https://en.cppreference.com/w/cpp/language/rule_of_three))

## 2) What you are building (plain English)
You are building a tiny owning buffer type that cannot be copied but can be moved safely. The goal is to make its interface and behavior consistent with the ownership model: one owner at a time, with a valid "empty" state after moves. (Source: [cppreference: std::unique_ptr](https://en.cppreference.com/w/cpp/memory/unique_ptr))

## 3) Why it matters (embedded/robotics/defense relevance)
In embedded systems, accidental copies or unclear ownership can lead to double free, stale pointers, or data races. A clean interface with explicit move-only semantics makes ownership transfer explicit and safe, which is essential in safety-critical code. (Source: [C++ Core Guidelines, resource management](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines))

## 4) Concepts (short lecture)
The Rule of Five says that if your type owns a resource (like heap memory), you should explicitly define or delete copy/move constructors and assignment operators, plus the destructor. This prevents implicit behavior that could double-free or leak resources. (Source: [cppreference: Rule of Three/Five](https://en.cppreference.com/w/cpp/language/rule_of_three))

`std::unique_ptr<T[]>` is a single-owner smart pointer that deletes its array when it goes out of scope. It is move-only, which makes it a great building block for move-only owning types. (Source: [cppreference: std::unique_ptr](https://en.cppreference.com/w/cpp/memory/unique_ptr))

Move semantics must leave the source object in a valid, empty state. "Valid" means you can safely destroy it or assign to it again without crashes. A common pattern is to reset the source size to zero after moving. (Source: [cppreference: std::move](https://en.cppreference.com/w/cpp/utility/move))

Example (not your solution): move-only buffer with explicit comments about the moved-from state.
```cpp
class Buffer {
public:
    explicit Buffer(size_t n) : size_(n), data_(n ? std::make_unique<int[]>(n) : nullptr) {}

    // Disallow copy to enforce single ownership.
    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;

    // Move transfers ownership and clears the source size.
    Buffer(Buffer&& other) noexcept
        : size_(other.size_), data_(std::move(other.data_)) {
        other.size_ = 0; // moved-from state is empty but valid
    }
private:
    size_t size_{0};
    std::unique_ptr<int[]> data_;
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
1) Inspect the `Buffer` interface in `learner/src/main.cpp` and restate the ownership model.
   The type owns heap memory via `std::unique_ptr<int[]>`, so it must be move-only. That means copy is deleted, move is defined, and moved-from objects must be safe to destroy and query. Write down what "safe" means here: `size()` should report 0 after a move, and `sum()` should return 0 because there are no elements. (Source: [cppreference: Rule of Three/Five](https://en.cppreference.com/w/cpp/language/rule_of_three))
   - **Expected result:** you can describe how a moved-from `Buffer` should behave.

2) Implement the move constructor with explicit state transfer.
   Move the `unique_ptr` to transfer ownership of the heap array. Copy `size_` so the new object knows how many elements exist. Then set `other.size_ = 0` so the source reports an empty, valid state. This is the canonical move pattern for owning types. (Source: [cppreference: std::unique_ptr](https://en.cppreference.com/w/cpp/memory/unique_ptr))
   - **Expected result:** moving a buffer transfers the array and empties the source.

3) Implement move assignment in a clear, safe order.
   First check for self-assignment. Then move the `unique_ptr` into `*this`, copy `size_`, and set `other.size_ = 0`. Because `unique_ptr` handles the old memory automatically, you do not need to delete anything manually. The critical part is leaving the source in a valid empty state. (Source: [cppreference: std::move](https://en.cppreference.com/w/cpp/utility/move))
   - **Expected result:** move assignment transfers ownership and leaves the source safe to destroy.

4) Implement `sum()` using the current `size_`.
   Iterate from `0` to `size_ - 1` and accumulate values. If `size_` is 0 (e.g., after a move), the loop should do nothing and return 0. This is how you make moved-from objects safe for simple queries. (Source: [cppreference: std::unique_ptr](https://en.cppreference.com/w/cpp/memory/unique_ptr))
   - **Expected result:** `sum()` returns 6 for `{1,2,3}` and 0 for an empty buffer.

5) Remove `#error TODO_implement_exercise`, rebuild, and run tests.
   If you see a failure, check whether you reset `other.size_` in both move operations and ensure `sum()` uses `size_` rather than a fixed count. (Source: [cppreference: Rule of Three/Five](https://en.cppreference.com/w/cpp/language/rule_of_three))
   - **Expected result:** `ctest` reports `100% tests passed`.

6) Capture artifacts.
   Redirect build output to `learner/artifacts/build.log` and test output to `learner/artifacts/ctest.log`. These logs are required for grading evidence. (Source: [cppreference: std::unique_ptr](https://en.cppreference.com/w/cpp/memory/unique_ptr))
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
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/01_foundations/exercises/ex03_interface_review`
- Solution check:
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/01_foundations/exercises/ex03_interface_review --use-solution`
- High-level scoring:
  - Configure/build: 40 points
  - Tests: 40 points
  - Artifacts present: 20 points

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- If build fails: verify you removed the `#error` and defined all methods.
- If tests fail: check that `other.size_` is reset to 0 in both move operations.

## 13) Stretch goals
- Add a `data()` accessor that returns a `const int*` for read-only access.
- Add a small unit test that verifies `sum()` on an empty buffer returns 0.
