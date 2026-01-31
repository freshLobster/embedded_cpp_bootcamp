# 04_architecture - ex01_topic_contract

## 1) Title + Mission
Mission: parse a topic contract string using non-owning views to avoid unnecessary copies in the hot path. (Source: [cppreference: std::string_view](https://en.cppreference.com/w/cpp/string/basic_string_view))

## 2) What you are building (plain English)
You are building a small parser that takes a string like `name:type:rate` and converts it into a structured `TopicContract`. The parser must be strict, rejecting malformed inputs. (Source: [cppreference: std::string_view](https://en.cppreference.com/w/cpp/string/basic_string_view))

## 3) Why it matters (embedded/robotics/defense relevance)
Robotics middleware often parses high-rate message descriptors. Using non-owning views avoids unnecessary allocations and keeps latency predictable. Strict parsing prevents bad configuration from propagating into runtime faults. (Source: [cppreference: std::string_view](https://en.cppreference.com/w/cpp/string/basic_string_view))

## 4) Concepts (short lecture)
`std::string_view` is a lightweight, non-owning reference to a string. It lets you parse text without allocating or copying. The caller must ensure the original string outlives the view. (Source: [cppreference: std::string_view](https://en.cppreference.com/w/cpp/string/basic_string_view))

Parsing with `string_view` typically means splitting by delimiters and then validating each segment. You can convert to owning `std::string` only after validation to minimize overhead. (Source: [cppreference: std::string_view::substr](https://en.cppreference.com/w/cpp/string/basic_string_view/substr))

Example (not your solution): splitting on delimiters with explicit comments.
```cpp
std::string_view text = "sensor.raw:float:50";
size_t first = text.find(':');
size_t second = text.find(':', first + 1);
// name = "sensor.raw", type = "float", rate = "50"
std::string_view name = text.substr(0, first);
std::string_view type = text.substr(first + 1, second - first - 1);
std::string_view rate = text.substr(second + 1);
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
1) Read `parse_contract` in `learner/src/main.cpp` and restate the contract format.
   The contract is `name:type:rate`. You must parse exactly three fields separated by `:` and reject anything else. That means `"invalid"` (no delimiters) and `"name:type"` (missing rate) must return false. (Source: [cppreference: std::string_view::find](https://en.cppreference.com/w/cpp/string/basic_string_view/find))
   How: write the format on paper and list two valid and two invalid examples so you can compare against your parser behavior.
   - **Expected result:** you can describe the valid format and list at least two invalid examples.

2) Split the input into three `string_view` segments.
   Find the first `:` and the second `:`. Use `substr` to create views for the name, type, and rate segments without allocating. This keeps parsing fast and avoids temporary strings until you know the input is valid. (Source: [cppreference: std::string_view::substr](https://en.cppreference.com/w/cpp/string/basic_string_view/substr))
   How: call `find(':')` for the first delimiter and then `find(':', first+1)` for the second, then build `substr` views for each segment.
   - **Expected result:** you can print the three segments for a valid input like `sensor.raw:float:50`.

3) Validate each segment before copying.
   Check that `name` and `type` are non-empty. For the rate, iterate over each character and ensure it is a digit, building the integer value as you go. Reject any non-digit characters and any rate value <= 0. This strict validation prevents silent misconfiguration. (Source: [cppreference: std::isdigit](https://en.cppreference.com/w/cpp/string/byte/isdigit))
   How: loop over the rate segment with `for (char c : rate_view)` and build `rate = rate * 10 + (c - '0')`, returning false on any non-digit.
   - **Expected result:** inputs like `sensor.raw:float:0` and `sensor.raw:float:5ms` return false.

4) Assign validated fields into the output struct.
   After validation, copy the `string_view` segments into `std::string` fields of `TopicContract`, then set `rate_hz` to the parsed integer. This is the only point where you allocate and copy, and it happens only for valid inputs. (Source: [cppreference: std::string](https://en.cppreference.com/w/cpp/string/basic_string))
   How: assign `out.name = std::string(name_view); out.type = std::string(type_view); out.rate_hz = rate;` and return true.
   - **Expected result:** the output struct fields match the parsed input exactly.

5) Remove `#error TODO_implement_exercise`, rebuild, and run tests.
   If the test fails, print the parsed fields in a debugger or temporarily add logging to confirm your delimiters and rate parsing. (Source: [cppreference: std::string_view](https://en.cppreference.com/w/cpp/string/basic_string_view))
   How: remove the `#error` line, rebuild, then run `ctest --test-dir build_learner --output-on-failure`.
   - **Expected result:** `ctest` reports `100% tests passed`.

6) Capture artifacts.
   Redirect build output to `learner/artifacts/build.log` and test output to `learner/artifacts/ctest.log` to satisfy grading requirements. (Source: [cppreference: std::string_view](https://en.cppreference.com/w/cpp/string/basic_string_view))
   How: run `cmake --build build_learner > learner/artifacts/build.log 2>&1` and `ctest --test-dir build_learner --output-on-failure > learner/artifacts/ctest.log 2>&1`.
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
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/04_architecture/exercises/ex01_topic_contract`
- Solution check:
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/04_architecture/exercises/ex01_topic_contract --use-solution`
- High-level scoring:
  - Configure/build: 40 points
  - Tests: 40 points
  - Artifacts present: 20 points

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- If build fails: ensure you removed `#error` and included `<string_view>`.
- If tests fail: check delimiter parsing and ensure rate is parsed as a positive integer.

## 13) Stretch goals
- Allow optional whitespace around delimiters and trim it before validation.
- Add a `to_string()` helper that serializes a `TopicContract` back to text.
