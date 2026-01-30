# 11_cuda_basics - ex03_raii_buffer

## 1) Title + Mission
Mission: implement an RAII buffer with correct move semantics to model safe CUDA resource ownership. (Source: [C++ Core Guidelines, RAII](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines))

## 2) What you are building (plain English)
You are building a small buffer class that owns heap memory, cannot be copied, and can be moved safely. This mirrors how you should wrap CUDA allocations in C++ RAII types. (Source: [cppreference: Rule of Five](https://en.cppreference.com/w/cpp/language/rule_of_three))

## 3) Why it matters (embedded/robotics/defense relevance)
GPU allocations must be released reliably. A move-only RAII wrapper makes ownership explicit and prevents leaks or double frees in complex pipelines. (Source: [C++ Core Guidelines, RAII](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines))

## 4) Concepts (short lecture)
RAII ties resource lifetime to object lifetime. For GPU buffers, that means allocating in the constructor and freeing in the destructor so cleanup happens even on early returns or errors. (Source: [C++ Core Guidelines, RAII](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines))

The Rule of Five states that owning types must define or delete copy/move operations to control ownership transfers. This is essential for move-only resource wrappers. (Source: [cppreference: Rule of Five](https://en.cppreference.com/w/cpp/language/rule_of_three))

Example (not your solution): move-only buffer pattern.
```cpp
class Buffer {
public:
    explicit Buffer(size_t n) : data_(n ? new int[n]() : nullptr), size_(n) {}
    ~Buffer() { delete[] data_; }
    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;
    Buffer(Buffer&& other) noexcept : data_(other.data_), size_(other.size_) {
        other.data_ = nullptr;
        other.size_ = 0;
    }
private:
    int* data_{nullptr};
    size_t size_{0};
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

## 7) Build instructions (learner + solution)
### Learner path (fails initially until you implement)
```
cmake -S learner -B build_learner -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build_learner
ctest --test-dir build_learner --output-on-failure
```

### Solution path (must pass immediately)
```
cmake -S solution -B build_solution -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build_solution
ctest --test-dir build_solution --output-on-failure
```

## 8) Step-by-step implementation instructions
1) Read `learner/src/main.cpp` and identify the ownership rules.
   The buffer owns raw memory. That means you must define a destructor, delete copy operations, and implement move operations that transfer ownership safely. (Source: [cppreference: Rule of Five](https://en.cppreference.com/w/cpp/language/rule_of_three))
   - **Expected result:** you can explain why copying is disallowed.

2) Implement the constructor and destructor.
   Allocate `n` elements when `n > 0` and set the pointer to `nullptr` when `n == 0`. In the destructor, delete the array and set the pointer to null if needed. This ensures deterministic cleanup. (Source: [C++ Core Guidelines, RAII](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines))
   - **Expected result:** a buffer of size 0 has a null pointer and is safe to destroy.

3) Delete copy constructor and copy assignment.
   Explicitly `= delete` both operations so the compiler cannot generate them. This prevents double-free errors when two objects believe they own the same buffer. (Source: [cppreference: Rule of Five](https://en.cppreference.com/w/cpp/language/rule_of_three))
   - **Expected result:** attempts to copy fail at compile time.

4) Implement move constructor and move assignment.
   Transfer the pointer and size, then null out the source pointer and set its size to 0. In move assignment, release any existing memory before taking ownership of the new one. (Source: [cppreference: std::move](https://en.cppreference.com/w/cpp/utility/move))
   - **Expected result:** moved-from objects are empty but safe to destroy.

5) Implement accessors (`size()` and `data()`).
   Return the current size and raw pointer. These are needed for tests and would be required for any wrapper that exposes CUDA buffers. (Source: [C++ Core Guidelines, RAII](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines))
   - **Expected result:** `size()` returns the expected size and `data()` is non-null when size > 0.

6) Remove `#error TODO_implement_exercise`, rebuild, and run tests.
   If tests fail, check that move assignment deletes the old buffer and that the moved-from object is reset. (Source: [cppreference: Rule of Five](https://en.cppreference.com/w/cpp/language/rule_of_three))
   - **Expected result:** `ctest` reports `100% tests passed`.

7) Capture artifacts.
   Save build output to `learner/artifacts/build.log` and test output to `learner/artifacts/ctest.log`. (Source: [C++ Core Guidelines, RAII](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines))
   - **Expected result:** artifacts exist and contain your outputs.

## 9) Verification
- `ctest --test-dir build_learner --output-on-failure` must report `100% tests passed`.

## 10) Artifacts to save
- `build.log` and `ctest.log` in `learner/artifacts/`.

## 11) Grade this exercise
- Learner attempt: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/11_cuda_basics/exercises/ex03_raii_buffer`
- Solution check: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/11_cuda_basics/exercises/ex03_raii_buffer --use-solution`

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- Build fails: ensure copy operations are deleted and move ops are defined.
- Test fails: verify you reset the moved-from object and handle size 0.

## 13) Stretch goals
- Replace `new[]/delete[]` with real `cudaMalloc/cudaFree` behind a compile guard.
- Add a `reset()` method that frees and reallocates.
