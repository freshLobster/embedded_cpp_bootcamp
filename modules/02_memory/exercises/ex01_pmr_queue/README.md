# 02_memory - ex01_pmr_queue

## 1) Title + Mission
Mission: Implement a queue that uses polymorphic memory resources for allocator control and bounded allocation behavior.【https://en.cppreference.com/w/cpp/memory/memory_resource†L463-L463】【https://en.cppreference.com/w/cpp/memory/polymorphic_allocator†L478-L478】

## 2) What you are building (plain English)
You are building a small queue whose storage is supplied by a memory_resource, allowing you to swap allocation strategy without changing the container type.【https://en.cppreference.com/w/cpp/memory/memory_resource†L463-L463】【https://en.cppreference.com/w/cpp/memory/polymorphic_allocator†L478-L478】

## 3) Why it matters (embedded/robotics/defense relevance)
Allocator control is critical in embedded systems where you must bound memory growth; PMR lets you enforce those constraints without rewriting your data structures.【https://en.cppreference.com/w/cpp/memory/monotonic_buffer_resource†L485-L485】

## 4) Concepts (short lecture)
`std::pmr::memory_resource` is an abstract interface that defines how memory is allocated and deallocated. `std::pmr::polymorphic_allocator` forwards container allocations to a runtime-selected resource, decoupling the container type from the allocation strategy.【https://en.cppreference.com/w/cpp/memory/memory_resource†L463-L463】【https://en.cppreference.com/w/cpp/memory/polymorphic_allocator†L478-L478】

`std::pmr::monotonic_buffer_resource` is a fast arena allocator that releases all allocations only when the resource is destroyed. It is ideal for bounded, phase-based allocation patterns common in robotics pipelines.【https://en.cppreference.com/w/cpp/memory/monotonic_buffer_resource†L485-L485】

Example (not your solution): building a PMR vector on a fixed buffer.
```cpp
std::byte buffer[1024];
std::pmr::monotonic_buffer_resource res(buffer, sizeof(buffer));
std::pmr::vector<int> v(&res);
v.push_back(42); // allocated from buffer
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
1) Open `learner/src/main.cpp` and inspect the `PmrQueue` skeleton.
   - Identify where the allocator should be stored and how `head_` tracks consumption.
   - **Expected result:** you can describe how `size()` should be computed.
2) Implement the constructor and `resource()`.
   - Store the `std::pmr::memory_resource*` and expose it for tests.
   - **Expected result:** `resource()` returns the same pointer passed in.
3) Implement `push`, `pop`, and `size`.
   - `push` appends to the PMR vector.
   - `pop` returns false if empty, otherwise returns and advances the head index.
   - `size` returns remaining elements (total minus head index).
   - **Expected result:** the test sequence behaves like a queue.
4) Remove `#error TODO_implement_exercise`, rebuild, and run tests.
5) Save artifacts in `learner/artifacts/`.

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
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/02_memory/exercises/ex01_pmr_queue`
- Solution check:
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/02_memory/exercises/ex01_pmr_queue --use-solution`
- High-level scoring:
  - Configure/build: 40 points
  - Tests: 40 points
  - Artifacts present: 20 points

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- If build fails: verify CMake + compiler version.
- If tests fail: re-check your logic against the required behavior.

## 13) Stretch goals
- Add a `clear()` method that resets the queue without deallocating.
- Add a capacity limit and return false on push when full.
