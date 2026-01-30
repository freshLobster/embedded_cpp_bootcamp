# 04_architecture - ex03_backpressure

## 1) Title + Mission
Mission: Implement a bounded queue that applies backpressure by rejecting pushes when full.

## 2) What you are building (plain English)
You are building a fixed-capacity queue that tracks drops and allows consumers to pop items in FIFO order.

## 3) Why it matters (embedded/robotics/defense relevance)
Backpressure protects real-time pipelines from overload by forcing producers to respect downstream capacity limits.

## 4) Concepts (short lecture)
Backpressure is a policy that prevents unbounded growth: when a queue is full, producers must wait or drop. This keeps memory usage bounded and makes overload behavior explicit.

Even a non-blocking queue with a drop counter gives you a measurable signal of overload. A drop count is often the first indicator that a pipeline stage cannot keep up.

Example (not your solution): a simple bounded queue with drop counting.
```cpp
class BoundedQueue {
public:
    explicit BoundedQueue(size_t cap) : cap_(cap) {}
    bool try_push(int v) {
        if (q_.size() >= cap_) { ++drops_; return false; }
        q_.push_back(v); return true;
    }
    bool try_pop(int& out) {
        if (q_.empty()) return false;
        out = q_.front(); q_.pop_front(); return true;
    }
    size_t drops() const { return drops_; }
private:
    size_t cap_;
    size_t drops_{0};
    std::deque<int> q_;
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
1) Open `learner/src/main.cpp` and review the `BoundedQueue` skeleton.
   - Identify the capacity limit and drop counter.
   - **Expected result:** you can describe what should happen when the queue is full.
2) Implement `try_push`.
   - If the queue is at capacity, increment `drops_` and return false.
   - Otherwise push and return true.
   - **Expected result:** pushing into a full queue fails predictably.
3) Implement `try_pop`.
   - If empty, return false; otherwise pop and return the front element.
   - **Expected result:** FIFO order is preserved.
4) Implement `size()` and `drops()` accessors if needed.
5) Remove `#error TODO_implement_exercise`, build, and run tests.
6) Save artifacts.

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
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/04_architecture/exercises/ex03_backpressure`
- Solution check:
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/04_architecture/exercises/ex03_backpressure --use-solution`
- High-level scoring:
  - Configure/build: 40 points
  - Tests: 40 points
  - Artifacts present: 20 points

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- If build fails: verify CMake + compiler version.
- If tests fail: re-check your logic against the required behavior.

## 13) Stretch goals
- Add a blocking `push` that waits until space is available.
- Add a test that verifies drop count under load.
