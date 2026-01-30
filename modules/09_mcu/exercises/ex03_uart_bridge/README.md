# 09_mcu - ex03_uart_bridge

## 1) Title + Mission
Mission: implement a UART frame encoder/decoder with a simple checksum to detect corruption. (Source: [RFC 1071](https://www.rfc-editor.org/rfc/rfc1071))

## 2) What you are building (plain English)
You are building a frame format that appends a checksum to a payload string, and a decoder that verifies the checksum before accepting the payload. This mirrors how MCU-to-host links validate data. (Source: [RFC 1071](https://www.rfc-editor.org/rfc/rfc1071))

## 3) Why it matters (embedded/robotics/defense relevance)
Serial links can be noisy. A checksum lets you detect corrupted frames and reject them instead of acting on bad data. This is a basic safety measure for UART telemetry. (Source: [RFC 1071](https://www.rfc-editor.org/rfc/rfc1071))

## 4) Concepts (short lecture)
Checksums are simple integrity checks that sum bytes and compare against a transmitted value. While not cryptographic, they are sufficient to catch many transmission errors. (Source: [RFC 1071](https://www.rfc-editor.org/rfc/rfc1071))

Encoding and decoding should be deterministic: given the same payload, you must produce the same frame, and decoding must either return the payload or reject the frame. (Source: [cppreference: std::string](https://en.cppreference.com/w/cpp/string/basic_string))

Example (not your solution): append a checksum field.
```cpp
unsigned checksum(std::string_view payload) {
    unsigned sum = 0;
    for (unsigned char c : payload) sum = (sum + c) & 0xFFu;
    return sum;
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
1) Read `learner/src/main.cpp` and define the frame format.
   The frame format is `<payload>|CS=<checksum>`. The checksum is computed over the payload only, not including the checksum field. This is the contract your encoder and decoder must follow. (Source: [RFC 1071](https://www.rfc-editor.org/rfc/rfc1071))
   - **Expected result:** you can write the full frame string for a sample payload.

2) Implement `checksum(std::string_view payload)`.
   Iterate over the payload bytes and compute a simple sum modulo 256. Use `unsigned char` to avoid sign issues. This matches the solution's expected checksum behavior. (Source: [RFC 1071](https://www.rfc-editor.org/rfc/rfc1071))
   - **Expected result:** checksum("HELLO") returns a deterministic integer.

3) Implement `encode_frame(std::string_view payload)`.
   Concatenate the payload, a delimiter (`|CS=`), and the decimal checksum value. This produces the wire frame that the receiver will validate. (Source: [cppreference: std::string](https://en.cppreference.com/w/cpp/string/basic_string))
   - **Expected result:** encode_frame("HELLO") returns something like "HELLO|CS=...".

4) Implement `decode_frame(std::string_view frame, std::string& payload_out)`.
   Find the last occurrence of `|CS=`. If it is missing, return false. Split into payload and checksum text, parse the checksum, and compare it to the computed checksum of the payload. If they match, assign the payload to `payload_out` and return true. (Source: [cppreference: std::string_view::rfind](https://en.cppreference.com/w/cpp/string/basic_string_view/rfind))
   - **Expected result:** valid frames decode successfully; corrupted frames return false.

5) Remove `#error TODO_implement_exercise`, rebuild, and run tests.
   If tests fail, check that you used `rfind` (not `find`) so payloads containing `|CS=` are handled safely. (Source: [cppreference: std::string_view::rfind](https://en.cppreference.com/w/cpp/string/basic_string_view/rfind))
   - **Expected result:** `ctest` reports `100% tests passed`.

6) Capture artifacts.
   Save build output to `learner/artifacts/build.log` and test output to `learner/artifacts/ctest.log`. (Source: [RFC 1071](https://www.rfc-editor.org/rfc/rfc1071))
   - **Expected result:** artifacts exist and contain your outputs.

## 9) Verification
- `ctest --test-dir build_learner --output-on-failure` must report `100% tests passed`.

## 10) Artifacts to save
- `build.log` and `ctest.log` in `learner/artifacts/`.

## 11) Grade this exercise
- Learner attempt: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/09_mcu/exercises/ex03_uart_bridge`
- Solution check: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/09_mcu/exercises/ex03_uart_bridge --use-solution`

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- Build fails: include `<string>` and `<string_view>`.
- Test fails: check delimiter parsing and checksum calculation.

## 13) Stretch goals
- Add a length field to the frame and validate it.
- Add a unit test that intentionally corrupts the checksum.
