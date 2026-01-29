# 04_architecture - ex01_topic_contract

## 1) Title + Mission
Mission: Implement a topic contract view using non-owning string and span types to avoid copies in the hot path.【https://en.cppreference.com/w/cpp/string/basic_string_view†L389-L389】【https://en.cppreference.com/w/cpp/container/span†L400-L400】
## 2) What you are building (plain English)
You are building a small contract parser that accepts non-owning views of bytes and strings, so the contract can be validated without allocating.【https://en.cppreference.com/w/cpp/string/basic_string_view†L389-L389】
## 3) Why it matters (embedded/robotics/defense relevance)
Autonomy middleware moves high-rate data; using views avoids allocations and keeps ownership boundaries explicit across modules.【https://en.cppreference.com/w/cpp/container/span†L400-L400】
## 4) Concepts (short lecture)
string_view and span describe contiguous sequences without owning them, which lets you parse and validate data without copying it.【https://en.cppreference.com/w/cpp/string/basic_string_view†L389-L389】【https://en.cppreference.com/w/cpp/container/span†L400-L400】

Clear ownership boundaries improve modular architecture because the producer remains responsible for data lifetime while consumers use read-only views.【https://en.cppreference.com/w/cpp/container/span†L400-L400】
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
Expected initial failure: compilation error due to `#error TODO_implement_exercise`.

### Solution path (must pass immediately)
```
cmake -S solution -B build_solution -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build_solution
ctest --test-dir build_solution --output-on-failure
```

## 8) Step-by-step implementation instructions
1) Open `learner/src/main.cpp` and read the TODOs.
2) Implement the required logic in `exercise()`.
3) Rebuild and run tests.

## 9) Verification
- `ctest --test-dir build_learner --output-on-failure` must report `100% tests passed`.

## 10) Artifacts to save
- `build.log` and `ctest.log` in `learner/artifacts/`.

## 11) Grade this exercise
- Learner attempt: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/04_architecture/exercises/ex01_topic_contract`
- Solution check: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/04_architecture/exercises/ex01_topic_contract --use-solution`

## 12) If it fails (quick triage)
See `troubleshooting.md`.

## 13) Stretch goals
- Add an edge-case test.
