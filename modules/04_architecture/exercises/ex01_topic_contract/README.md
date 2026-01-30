# 04_architecture - ex01_topic_contract

## 1) Title + Mission
Mission: Implement a topic contract view using non-owning string types to avoid copies in the hot path.【https://en.cppreference.com/w/cpp/string/basic_string_view†L389-L389】

## 2) What you are building (plain English)
You are building a small contract parser that accepts non-owning views of text and converts them into a structured `TopicContract`.【https://en.cppreference.com/w/cpp/string/basic_string_view†L389-L389】

## 3) Why it matters (embedded/robotics/defense relevance)
Autonomy middleware moves high-rate data; parsing without copies reduces latency and keeps ownership boundaries explicit.【https://en.cppreference.com/w/cpp/string/basic_string_view†L389-L389】

## 4) Concepts (short lecture)
`std::string_view` describes a constant contiguous sequence of characters without owning them. This lets you parse configuration strings without allocating or copying data.【https://en.cppreference.com/w/cpp/string/basic_string_view†L389-L389】

A topic contract is a small schema: name, type, and rate. Parsing it deterministically helps enforce interface contracts between pipeline stages.

Example (not your solution): parsing a `name:type:rate` string.
```cpp
bool parse_contract(std::string_view text, TopicContract& out) {
    auto first = text.find(':');
    auto second = text.find(':', first + 1);
    if (first == std::string_view::npos || second == std::string_view::npos) return false;
    out.name = std::string(text.substr(0, first));
    out.type = std::string(text.substr(first + 1, second - first - 1));
    out.rate_hz = std::stoi(std::string(text.substr(second + 1)));
    return !out.name.empty() && !out.type.empty() && out.rate_hz > 0;
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
1) Open `learner/src/main.cpp` and read the `TopicContract` and `parse_contract` stub.
   - Confirm the expected input format: `name:type:rate`.
   - **Expected result:** you can list the required fields and constraints.
2) Implement delimiter parsing using `find`.
   - Identify the two `:` separators and guard against missing delimiters.
   - **Expected result:** invalid strings return `false`.
3) Extract fields using `substr` and populate the output structure.
   - Convert the rate to an integer and validate it is positive.
   - **Expected result:** valid inputs produce the expected fields.
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
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/04_architecture/exercises/ex01_topic_contract`
- Solution check:
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/04_architecture/exercises/ex01_topic_contract --use-solution`
- High-level scoring:
  - Configure/build: 40 points
  - Tests: 40 points
  - Artifacts present: 20 points

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- If build fails: verify CMake + compiler version.
- If tests fail: re-check your logic against the required behavior.

## 13) Stretch goals
- Support whitespace trimming around fields.
- Add a `TopicContract::to_string()` helper for debugging.
