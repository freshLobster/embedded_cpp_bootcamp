# 05_scheduling - ex03_priority

## 1) Title + Mission
Mission: Implement a priority-based dispatcher using a priority_queue to select the next task.【https://en.cppreference.com/w/cpp/container/priority_queue†L395-L395】

## 2) What you are building (plain English)
You are building a dispatcher that orders tasks by priority, ensuring higher-priority work is executed first.【https://en.cppreference.com/w/cpp/container/priority_queue†L395-L395】

## 3) Why it matters (embedded/robotics/defense relevance)
Priority scheduling is a standard control-system tactic for meeting deadlines when multiple tasks compete for CPU time.【https://en.cppreference.com/w/cpp/container/priority_queue†L395-L395】

## 4) Concepts (short lecture)
`std::priority_queue` is a container adaptor that provides access to the highest-priority element according to a comparator. It is the simplest way to model priority-based dispatching in standard C++.【https://en.cppreference.com/w/cpp/container/priority_queue†L395-L395】

The comparator defines what "higher priority" means. A common pattern is to store an integer priority and order by larger values first.

Example (not your solution): a priority queue with a custom comparator.
```cpp
struct Item { int prio; int value; };
struct ByPriority { bool operator()(const Item& a, const Item& b) const { return a.prio < b.prio; } };
std::priority_queue<Item, std::vector<Item>, ByPriority> pq;
pq.push({2, 10});
pq.push({1, 5});
// pq.top().prio == 2
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
1) Open `learner/src/main.cpp` and inspect the dispatcher skeleton.
   - Identify the item type and comparator requirements.
   - **Expected result:** you can describe which task should be chosen first.
2) Implement the comparator and push/pop logic.
   - Ensure `top()` returns the highest-priority element.
   - **Expected result:** tasks are ordered by priority.
3) Implement `dispatch_next()` (or equivalent) to pop and return the chosen task.
4) Remove `#error TODO_implement_exercise`, build, and run tests.
5) Save artifacts.

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
- If build fails: verify CMake + compiler version.
- If tests fail: re-check your logic against the required behavior.

## 13) Stretch goals
- Add stable ordering for equal priorities (e.g., FIFO by insertion order).
- Add a test with mixed priorities and equal-priority tasks.
