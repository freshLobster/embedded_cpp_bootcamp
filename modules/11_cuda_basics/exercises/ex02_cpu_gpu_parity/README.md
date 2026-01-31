# 11_cuda_basics - ex02_cpu_gpu_parity

## 1) Title + Mission
Mission: implement a CPU reference add function that serves as the correctness baseline for GPU parity checks. (Source: [CUDA C++ Programming Guide](https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html))

## 2) What you are building (plain English)
You are building a CPU function that adds two integer vectors element by element and returns the result. This reference is used to verify GPU outputs match CPU behavior. (Source: [cppreference: std::vector](https://en.cppreference.com/w/cpp/container/vector))

## 3) Why it matters (embedded/robotics/defense relevance)
GPU acceleration only helps if results are correct. A CPU reference implementation is the gold standard for validating correctness during GPU bring-up and integration. (Source: [CUDA C++ Programming Guide](https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html))

## 4) Concepts (short lecture)
CPU/GPU parity means the GPU implementation produces the same results as a trusted CPU reference for the same inputs. This is essential before optimizing for performance. (Source: [CUDA C++ Programming Guide](https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html))

Vector addition is intentionally simple. It isolates correctness from performance and lets you validate that data is processed as expected. (Source: [cppreference: std::vector](https://en.cppreference.com/w/cpp/container/vector))

Example (not your solution): CPU vector add.
```cpp
std::vector<int> add_cpu(const std::vector<int>& a, const std::vector<int>& b) {
    std::vector<int> out;
    // Reserve once to avoid repeated reallocations.
    out.reserve(a.size());
    for (size_t i = 0; i < a.size(); ++i) {
        // Element-wise addition.
        out.push_back(a[i] + b[i]);
    }
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
1) Read `learner/src/main.cpp` and define the CPU reference behavior.
   The function must return a vector where each element is the sum of the corresponding elements in `a` and `b`. This output is the baseline for GPU parity checks. (Source: [cppreference: std::vector](https://en.cppreference.com/w/cpp/container/vector))
   How: write the expected output for the test inputs (1,2,3) and (4,5,6) so you can validate quickly.
   - **Expected result:** you can write the element-wise addition formula.

2) Implement `add_cpu` with a single loop.
   Create an output vector, reserve capacity equal to `a.size()`, and push back `a[i] + b[i]` for each index. This avoids repeated reallocations and keeps the function deterministic. (Source: [cppreference: std::vector::reserve](https://en.cppreference.com/w/cpp/container/vector/reserve))
   How: use a `size_t` loop over `a.size()` and push each sum into the output. Keep the body minimal so it mirrors what a GPU kernel would do.
   - **Expected result:** adding {1,2,3} and {4,5,6} yields {5,7,9}.

3) Implement `exercise()` to validate the reference output.
   Construct two small vectors, call `add_cpu`, and verify the result values. Return 0 on success. (Source: [cppreference: assert](https://en.cppreference.com/w/cpp/error/assert))
   How: check both the size and a couple of element values so you know the loop ran correctly.
   - **Expected result:** `exercise()` returns 0 when the output matches expected values.

4) Remove `#error TODO_implement_exercise`, rebuild, and run tests.
   If tests fail, check that your loop bounds match the vector size and that you reserved capacity before pushing. (Source: [cppreference: std::vector::size](https://en.cppreference.com/w/cpp/container/vector/size))
   How: remove `#error`, rebuild, and run `ctest`. If the output vector is empty, you likely forgot to push values.
   - **Expected result:** `ctest` reports `100% tests passed`.

5) Capture artifacts.
   Save build output to `learner/artifacts/build.log` and test output to `learner/artifacts/ctest.log`. (Source: [CUDA C++ Programming Guide](https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html))
   How: redirect outputs with `> file 2>&1` so you capture errors.
   - **Expected result:** artifacts exist and contain your outputs.

## 9) Verification
- `ctest --test-dir build_learner --output-on-failure` must report `100% tests passed`.

## 10) Artifacts to save
- `build.log` and `ctest.log` in `learner/artifacts/`.

## 11) Grade this exercise
- Learner attempt: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/11_cuda_basics/exercises/ex02_cpu_gpu_parity`
- Solution check: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/11_cuda_basics/exercises/ex02_cpu_gpu_parity --use-solution`

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- Build fails: include `<vector>`.
- Test fails: verify element-wise addition and index bounds.

## 13) Stretch goals
- Add a size mismatch check and return an empty vector on mismatch.
- Add a GPU stub and compare outputs when CUDA is available.
