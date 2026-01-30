# 01_foundations - ex03_interface_review

## 1) Title + Mission
Mission: Refactor an owning buffer interface to follow the rule of three/five/zero and expose a stable, safe API surface.【https://en.cppreference.com/w/cpp/language/rule_of_three†L501-L501】

## 2) What you are building (plain English)
You are building a small owning buffer type whose copy/move behavior is explicit and safe, with clear semantics for resource ownership and transfer.【https://en.cppreference.com/w/cpp/language/rule_of_three†L501-L501】

## 3) Why it matters (embedded/robotics/defense relevance)
Large robotics codebases live or die by interface hygiene; ambiguous ownership and missing move semantics lead to leaks and latent correctness bugs.【https://en.cppreference.com/w/cpp/language/rule_of_three†L501-L501】

## 4) Concepts (short lecture)
The rule of three/five/zero explains when classes that manage resources must explicitly define copy, move, and destruction behavior to avoid double-free or leaks. If you own a resource, you must decide how copying and moving behave.【https://en.cppreference.com/w/cpp/language/rule_of_three†L501-L501】

`std::unique_ptr` expresses exclusive ownership of dynamically allocated objects and automatically releases them in its destructor. Using `unique_ptr` inside your class is a classic rule-of-zero strategy because the compiler-generated destructor and move operations are correct by default.【https://en.cppreference.com/w/cpp/memory/unique_ptr†L510-L510】

Move semantics transfer ownership without copying. `std::move` does not move by itself; it marks an object as eligible to be moved-from so that ownership can be transferred efficiently.【https://en.cppreference.com/w/cpp/utility/move†L435-L435】

Example (not your solution): an owning buffer using `unique_ptr` with explicit move, and copy deleted.
```cpp
class Buffer {
public:
    explicit Buffer(size_t n) : size_(n), data_(n ? std::make_unique<int[]>(n) : nullptr) {}
    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;
    Buffer(Buffer&& other) noexcept : size_(other.size_), data_(std::move(other.data_)) { other.size_ = 0; }
    // TODO: add move assignment and accessor methods.
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
1) Open `learner/src/main.cpp` and read the `Buffer` skeleton and TODO markers.
   - Identify which special member functions are deleted and which must be implemented.
   - **Expected result:** you can explain why copying is unsafe for this class.
2) Implement the constructor and basic accessors.
   - Allocate the buffer if `size > 0`.
   - Provide `size()` and `operator[]` for const and non-const access.
   - **Expected result:** callers can read and write elements safely.
3) Implement move constructor and move assignment.
   - Transfer ownership of the buffer and reset the moved-from object to a safe empty state.
   - **Expected result:** moved-from buffers are valid but empty.
4) Implement `sum()`.
   - Iterate over the buffer and return the sum of values.
   - **Expected result:** test code that moves and sums passes.
5) Remove `#error TODO_implement_exercise`, rebuild, and run tests.
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
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/01_foundations/exercises/ex03_interface_review`
- Solution check:
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/01_foundations/exercises/ex03_interface_review --use-solution`
- High-level scoring:
  - Configure/build: 40 points
  - Tests: 40 points
  - Artifacts present: 20 points

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- If build fails: verify CMake + compiler version.
- If tests fail: re-check your logic against the required behavior.

## 13) Stretch goals
- Add a bounds-checked `at()` method that returns an error code or throws.
- Add a `swap()` method and use it in move assignment.
