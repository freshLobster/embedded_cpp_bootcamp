# 12_cuda_perf - ex03_jetson

## 1) Title + Mission
Mission: implement a simple bottleneck classifier to reason about CPU/GPU/IO constraints on Jetson-class systems. (Source: [CUDA C++ Programming Guide](https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html))

## 2) What you are building (plain English)
You are building a function that returns a list of bottleneck labels based on boolean flags. This is a toy model of how you would annotate profiling conclusions in a Jetson pipeline. (Source: [CUDA C++ Programming Guide](https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html))

## 3) Why it matters (embedded/robotics/defense relevance)
Jetson-class systems are constrained by CPU, GPU, and IO bandwidth. Correctly identifying the dominant bottleneck is essential for targeted optimization and realistic performance budgets. (Source: [CUDA C++ Programming Guide](https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html))

## 4) Concepts (short lecture)
Performance analysis is about isolating the limiting resource. Even a simple classifier that labels CPU/GPU/IO constraints helps structure analysis and reporting. (Source: [CUDA C++ Programming Guide](https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html))

Returning an ordered list of bottlenecks makes downstream reporting deterministic and easy to test. (Source: [cppreference: std::vector](https://en.cppreference.com/w/cpp/container/vector))

Example (not your solution): classify bottlenecks.
```cpp
std::vector<std::string> bottlenecks(bool cpu, bool gpu, bool io) {
    std::vector<std::string> out;
    // Preserve order: cpu, gpu, io.
    if (cpu) out.push_back("cpu");
    if (gpu) out.push_back("gpu");
    if (io) out.push_back("io");
    return out;
}
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
1) Read `learner/src/main.cpp` and identify the expected ordering.
   The function should add "cpu", "gpu", and "io" in that order when the corresponding flags are true. The test checks the order, so do not sort or reorder. (Source: [cppreference: std::vector](https://en.cppreference.com/w/cpp/container/vector))
   How: write the order "cpu -> gpu -> io" next to your code so you do not accidentally reorder the pushes.
   - **Expected result:** you can list the exact output order.

2) Implement `bottlenecks(bool cpu, bool gpu, bool io)`.
   Create an empty vector of strings. If `cpu` is true, push "cpu"; if `gpu` is true, push "gpu"; if `io` is true, push "io". This keeps the output deterministic and easy to test. (Source: [cppreference: std::vector::push_back](https://en.cppreference.com/w/cpp/container/vector/push_back))
   How: build the vector in the exact order of the flags. Use `push_back` with string literals.
   - **Expected result:** with cpu=true and io=true, output is {"cpu","io"}.

3) Implement `exercise()` to validate results.
   Call `bottlenecks(true, false, true)` and confirm you get two entries, "cpu" then "io". Return 0 on success. (Source: [cppreference: std::vector](https://en.cppreference.com/w/cpp/container/vector))
   How: check both the size and the order of elements so you catch accidental reordering.
   - **Expected result:** `exercise()` returns 0.

4) Remove `#error TODO_implement_exercise`, rebuild, and run tests.
   If tests fail, check that you did not reorder the output or insert extra whitespace. (Source: [cppreference: std::string](https://en.cppreference.com/w/cpp/string/basic_string))
   How: remove the `#error`, rebuild, and run `ctest`. If the order is wrong, update the push order in `bottlenecks`.
   - **Expected result:** `ctest` reports `100% tests passed`.

5) Capture artifacts.
   Save build output to `learner/artifacts/build.log` and test output to `learner/artifacts/ctest.log`. (Source: [CUDA C++ Programming Guide](https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html))
   How: redirect outputs with `> file 2>&1` so you capture error messages.
   - **Expected result:** artifacts exist and contain your outputs.

## 9) Verification
- `ctest --test-dir build_learner --output-on-failure` must report `100% tests passed`.

## 10) Artifacts to save
- `build.log` and `ctest.log` in `learner/artifacts/`.

## 11) Grade this exercise
- Learner attempt: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/12_cuda_perf/exercises/ex03_jetson`
- Solution check: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/12_cuda_perf/exercises/ex03_jetson --use-solution`

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- Build fails: include `<string>` and `<vector>`.
- Test fails: verify output ordering.

## 13) Stretch goals
- Add a severity score next to each bottleneck.
- Add a function that formats the list for logging.
