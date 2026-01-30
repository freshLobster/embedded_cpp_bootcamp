# 12_cuda_perf - ex01_nsys

## 1) Title + Mission
Mission: implement profiling marker output suitable for Nsight Systems range collection. (Source: [Nsight Systems documentation](https://docs.nvidia.com/nsight-systems/))

## 2) What you are building (plain English)
You are building a small function that returns a marker string representing a profiling range. This mirrors how you would annotate CPU code to make Nsight traces easier to interpret. (Source: [Nsight Systems documentation](https://docs.nvidia.com/nsight-systems/))

## 3) Why it matters (embedded/robotics/defense relevance)
GPU profiling without clear markers is noisy. Range annotations let you isolate critical sections (e.g., perception kernels) and measure their impact on end-to-end latency. (Source: [Nsight Systems documentation](https://docs.nvidia.com/nsight-systems/))

## 4) Concepts (short lecture)
Nsight Systems can capture CPU/GPU timelines and ranges. Adding explicit markers makes it possible to correlate code regions with timing events. (Source: [Nsight Systems documentation](https://docs.nvidia.com/nsight-systems/))

Even when you cannot run Nsight, representing ranges as explicit strings is a useful teaching proxy for where you would instrument code in production. (Source: [Nsight Systems documentation](https://docs.nvidia.com/nsight-systems/))

Example (not your solution): simple marker string.
```cpp
std::string profile_markers() {
    return "nsys:range=compute";
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

If Nsight Systems is available, verify it:
```
nsys --version
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
1) Read `learner/src/main.cpp` and locate the marker function.
   The exercise expects a string that includes "nsys" so tests can detect it. The exact content is not critical as long as it is deterministic and clearly indicates a profiling range. (Source: [Nsight Systems documentation](https://docs.nvidia.com/nsight-systems/))
   - **Expected result:** you can describe the string format you will return.

2) Implement `profile_markers()` with a clear, fixed string.
   Return a constant string such as `"nsys:range=compute"`. This models how you would name a profiling range in real code. (Source: [Nsight Systems documentation](https://docs.nvidia.com/nsight-systems/))
   - **Expected result:** the string contains "nsys" and a range name.

3) Implement `exercise()` to validate the marker.
   Call `profile_markers()` and verify the string contains `"nsys"`. Return 0 on success. (Source: [cppreference: std::string::find](https://en.cppreference.com/w/cpp/string/basic_string/find))
   - **Expected result:** `exercise()` returns 0.

4) Remove `#error TODO_implement_exercise`, rebuild, and run tests.
   If tests fail, verify your string contains "nsys" and is not empty. (Source: [cppreference: std::string](https://en.cppreference.com/w/cpp/string/basic_string))
   - **Expected result:** `ctest` reports `100% tests passed`.

5) Capture artifacts.
   Save build output to `learner/artifacts/build.log` and test output to `learner/artifacts/ctest.log`. If you run `nsys`, save a note in `learner/artifacts/nsys_notes.txt`. (Source: [Nsight Systems documentation](https://docs.nvidia.com/nsight-systems/))
   - **Expected result:** artifacts exist and contain your outputs.

## 9) Verification
- `ctest --test-dir build_learner --output-on-failure` must report `100% tests passed`.

## 10) Artifacts to save
- `build.log` and `ctest.log` in `learner/artifacts/`.
- `nsys_notes.txt` if you used Nsight.

## 11) Grade this exercise
- Learner attempt: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/12_cuda_perf/exercises/ex01_nsys`
- Solution check: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/12_cuda_perf/exercises/ex01_nsys --use-solution`

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- Build fails: include `<string>`.
- Test fails: ensure the string contains "nsys".

## 13) Stretch goals
- Add multiple range markers separated by commas.
- Add a timestamp prefix to the marker string.
