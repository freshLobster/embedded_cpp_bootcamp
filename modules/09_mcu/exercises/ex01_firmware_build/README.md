# 09_mcu - ex01_firmware_build

## 1) Title + Mission
Mission: implement a UART-friendly sample frame encoder/decoder for MCU-to-host communication. (Source: [ESP-IDF UART documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32c3/api-reference/peripherals/uart.html))

## 2) What you are building (plain English)
You are building a simple framing protocol that encodes a sensor sample into a string and decodes it back. This mirrors how MCU telemetry is sent over UART. (Source: [ESP-IDF UART documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32c3/api-reference/peripherals/uart.html))

## 3) Why it matters (embedded/robotics/defense relevance)
UART remains a common MCU communication channel. A deterministic frame format prevents log corruption and makes host parsing reliable during bring-up and validation. (Source: [ESP-IDF UART documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32c3/api-reference/peripherals/uart.html))

## 4) Concepts (short lecture)
UART transports raw bytes without inherent framing; you must define your own framing format. A simple prefix and newline terminator is a practical pattern for small telemetry messages. (Source: [ESP-IDF UART documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32c3/api-reference/peripherals/uart.html))

String parsing and formatting should be deterministic. Using fixed prefixes like "S:" makes it easy to validate and debug both ends of the UART link. (Source: [cppreference: std::string](https://en.cppreference.com/w/cpp/string/basic_string))

Example (not your solution): encode and decode a sample frame.
```cpp
std::string encode_sample(int value) {
    // Prefix and newline to delimit a frame.
    return "S:" + std::to_string(value) + "\n";
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
1) Read `learner/src/main.cpp` and identify the frame format.
   The exercise requires a simple format like `"S:<value>\\n"`. This prefix makes it easy for the host to recognize valid frames and ignore noise. (Source: [ESP-IDF UART documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32c3/api-reference/peripherals/uart.html))
   How: write the expected frame for a known value (e.g., 42) so you can compare your encoder output exactly.
   - **Expected result:** you can write the exact frame format in one line.

2) Implement `encode_sample(int value)`.
   Construct a string that starts with `"S:"`, appends the integer as text, and ends with a newline. Use `std::to_string` and keep the format deterministic. (Source: [cppreference: std::to_string](https://en.cppreference.com/w/cpp/string/basic_string/to_string))
   How: build the string in order: prefix, value string, newline. Avoid extra spaces or formatting so the host parser stays simple.
   - **Expected result:** `encode_sample(42)` returns `"S:42\\n"`.

3) Implement `decode_sample(std::string_view text)`.
   Validate the prefix `"S:"`, then parse the remainder as an integer. Return -1 for invalid frames so the caller can detect corruption. Convert the substring to `std::string` if you use `std::stoi`. (Source: [cppreference: std::string_view](https://en.cppreference.com/w/cpp/string/basic_string_view))
   How: check `text.size()` first, ensure it starts with `"S:"`, then strip the prefix and parse. If any check fails, return -1 immediately.
   - **Expected result:** decoding `"S:42\\n"` yields 42, invalid frames yield -1.

4) Implement `exercise()` to validate the encode/decode pair.
   Encode a known sample, compare against the expected string, then decode and compare against the expected integer. This ensures the two functions are consistent. (Source: [cppreference: assert](https://en.cppreference.com/w/cpp/error/assert))
   How: use explicit comparisons (`!=`) and return distinct error codes so you can see which direction failed.
   - **Expected result:** `exercise()` returns 0 when both directions are correct.

5) Remove `#error TODO_implement_exercise`, rebuild, and run tests.
   If tests fail, verify your prefix logic and ensure you did not accidentally include extra whitespace. (Source: [cppreference: std::string](https://en.cppreference.com/w/cpp/string/basic_string))
   How: remove the `#error`, rebuild, and run `ctest`. If the output is close but not exact, print the encoded string temporarily to compare with the expected literal.
   - **Expected result:** `ctest` reports `100% tests passed`.

6) Capture artifacts.
   Save build output to `learner/artifacts/build.log` and test output to `learner/artifacts/ctest.log`. (Source: [ESP-IDF UART documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32c3/api-reference/peripherals/uart.html))
   How: redirect output with `> file 2>&1` so you capture any error messages as well.
   - **Expected result:** artifacts exist and contain your outputs.

## 9) Verification
- `ctest --test-dir build_learner --output-on-failure` must report `100% tests passed`.

## 10) Artifacts to save
- `build.log` and `ctest.log` in `learner/artifacts/`.

## 11) Grade this exercise
- Learner attempt: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/09_mcu/exercises/ex01_firmware_build`
- Solution check: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/09_mcu/exercises/ex01_firmware_build --use-solution`

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- Build fails: ensure `<string>` and `<string_view>` are included.
- Test fails: verify the prefix and newline format exactly.

## 13) Stretch goals
- Add a checksum field and validate it on decode.
- Add support for negative sample values.
