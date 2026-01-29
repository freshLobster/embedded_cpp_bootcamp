# 02_memory - ex01_pmr_queue

## 1) Title + Mission
Mission: Implement a queue that uses polymorphic memory resources for allocator control and bounded allocation behavior.【https://en.cppreference.com/w/cpp/memory/memory_resource†L463-L463】【https://en.cppreference.com/w/cpp/memory/polymorphic_allocator†L478-L478】
## 2) What you are building (plain English)
You are building a small queue whose storage is supplied by a memory_resource, allowing you to swap allocation strategy without changing the container type.【https://en.cppreference.com/w/cpp/memory/memory_resource†L463-L463】【https://en.cppreference.com/w/cpp/memory/polymorphic_allocator†L478-L478】
## 3) Why it matters (embedded/robotics/defense relevance)
Allocator control is critical in embedded systems where you must bound memory growth; PMR lets you enforce those constraints without rewriting your data structures.【https://en.cppreference.com/w/cpp/memory/monotonic_buffer_resource†L485-L485】
## 4) Concepts (short lecture)
std::pmr::memory_resource provides an abstract interface for allocation behavior, and polymorphic_allocator routes allocations through that interface.【https://en.cppreference.com/w/cpp/memory/memory_resource†L463-L463】【https://en.cppreference.com/w/cpp/memory/polymorphic_allocator†L478-L478】

monotonic_buffer_resource is a specialized resource that releases allocations only when destroyed, which is ideal for bounded, phase-based allocations.【https://en.cppreference.com/w/cpp/memory/monotonic_buffer_resource†L485-L485】
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
1) Open `learner/src/main.cpp` and read the TODOs.
   - Identify the required behavior for a queue backed by std::pmr::vector using a provided polymorphic allocator.
   - **Expected result:** you can explain what `exercise()` must verify before it returns success.
2) Implement the required logic in `exercise()`.
   - Introduce any helper classes or functions directly in `learner/src/main.cpp` or in `learner/include/` if you prefer.
   - **Expected result:** the code compiles without `#error` and the logic enforces the required behavior.
3) Rebuild and run tests.
   - Run `cmake --build build_learner` and `ctest --test-dir build_learner --output-on-failure`.
   - **Expected result:** tests pass and return 0.
4) Save artifacts.
   - Copy build and test output to `learner/artifacts/build.log` and `learner/artifacts/ctest.log`.
   - **Expected result:** those files exist and contain your command output.

## 9) Verification
- `ctest --test-dir build_learner --output-on-failure` must report `100% tests passed`.
- If it fails, stop and read `troubleshooting.md`.

## 10) Artifacts to save
Place these in `learner/artifacts/`:
- `build.log` - stdout/stderr from the build step.
- `ctest.log` - stdout/stderr from the test step.

## 11) Grade this exercise
- Learner attempt:
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/02_memory/exercises/ex01_pmr_queue`
- Solution check:
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/02_memory/exercises/ex01_pmr_queue --use-solution`

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- If build fails: verify CMake + compiler version.
- If tests fail: re-check your logic against the required behavior.

## 13) Stretch goals
- Add an extra test case that exercises an edge condition.
- Move helper logic into `learner/include/` and keep the interface clean.
