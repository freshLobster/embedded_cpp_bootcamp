# 05_scheduling - ex03_priority

## 1) Title + Mission
Mission: implement a priority-based dispatcher using `std::priority_queue` so high-priority tasks run first. (Source: [cppreference: std::priority_queue](https://en.cppreference.com/w/cpp/container/priority_queue))

## 2) What you are building (plain English)
You are building a dispatcher that orders tasks by priority, ensuring the most important work is processed before lower-priority tasks. (Source: [cppreference: std::priority_queue](https://en.cppreference.com/w/cpp/container/priority_queue))

## 3) Why it matters (embedded/robotics/defense relevance)
Priority scheduling is central to control systems: safety-critical tasks must run ahead of best-effort tasks. A correct priority queue prevents low-priority work from starving critical control loops. (Source: [cppreference: std::priority_queue](https://en.cppreference.com/w/cpp/container/priority_queue))

## 4) Concepts (short lecture)
`std::priority_queue` is a container adaptor that always exposes the "largest" element according to a comparator. By defining a comparator that orders by priority, you can model a dispatcher that always executes the highest-priority task. (Source: [cppreference: std::priority_queue](https://en.cppreference.com/w/cpp/container/priority_queue))

Custom comparators define the ordering rule. In a priority queue, the comparator returns true if the first argument should come *after* the second, which can be confusing. This exercise forces you to reason about comparator direction. (Source: [cppreference: Compare](https://en.cppreference.com/w/cpp/named_req/Compare))

Example (not your solution): comparator for higher priority first.
```cpp
struct ByPriority {
    bool operator()(const Item& a, const Item& b) const {
        // Return true if a has lower priority than b.
        return a.prio < b.prio;
    }
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
1) Read `ByPriority` and `Dispatcher` in `learner/src/main.cpp`.
   You must define a comparator that makes the highest `prio` come out first. Remember: the priority_queue places the "largest" element by comparator at the top. (Source: [cppreference: std::priority_queue](https://en.cppreference.com/w/cpp/container/priority_queue))
   - **Expected result:** you can explain which direction the comparator should return.

2) Implement `ByPriority::operator()`.
   Return true when `a` has lower priority than `b`. This makes the queue treat higher priorities as "larger" and pop them first. (Source: [cppreference: Compare](https://en.cppreference.com/w/cpp/named_req/Compare))
   - **Expected result:** items with priority 3 are dispatched before priority 2.

3) Implement `Dispatcher::dispatch_next`.
   Use `pq_.top()` to read the highest-priority item, then `pop()` to remove it. Return the item by value. (Source: [cppreference: std::priority_queue::top](https://en.cppreference.com/w/cpp/container/priority_queue/top))
   - **Expected result:** the first dispatch returns the priority-3 item.

4) Remove `#error TODO_implement_exercise`, rebuild, and run tests.
   - **Expected result:** `ctest` reports `100% tests passed`.

5) Capture artifacts.
   Save build and test output into `learner/artifacts/build.log` and `learner/artifacts/ctest.log`.
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
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/05_scheduling/exercises/ex03_priority`
- Solution check:
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/05_scheduling/exercises/ex03_priority --use-solution`
- High-level scoring:
  - Configure/build: 40 points
  - Tests: 40 points
  - Artifacts present: 20 points

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- If build fails: ensure you removed `#error` and included `<queue>`.
- If tests fail: double-check comparator direction and `dispatch_next` logic.

## 13) Stretch goals
- Add FIFO behavior for equal priorities by adding a sequence counter.
- Add a method to inspect queue size and highest priority without popping.
