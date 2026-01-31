# 08_cross_deploy - ex02_deploy

## 1) Title + Mission
Mission: construct a deterministic `scp` deployment command string to support repeatable SBC deployment. (Source: [OpenSSH scp manual](https://man.openbsd.org/scp))

## 2) What you are building (plain English)
You are building a small helper that assembles an `scp` command from user, host, local path, and remote path. This turns deployment into a repeatable, scriptable step. (Source: [OpenSSH scp manual](https://man.openbsd.org/scp))

## 3) Why it matters (embedded/robotics/defense relevance)
Deployment must be deterministic in mission systems. A simple, explicit command builder reduces human error and makes CI/CD scripts easier to audit. (Source: [OpenSSH scp manual](https://man.openbsd.org/scp))

## 4) Concepts (short lecture)
`scp` copies files over SSH. It is widely used to deploy binaries and configuration files to SBCs and embedded targets. (Source: [OpenSSH scp manual](https://man.openbsd.org/scp))

Constructing command strings should be deterministic and explicit. For teaching and testing, we build the command as a string so it can be validated with unit tests. (Source: [OpenSSH scp manual](https://man.openbsd.org/scp))

Example (not your solution): building an scp command.
```cpp
// Assemble the command in a single, deterministic string.
std::string cmd = "scp " + local + " " + user + "@" + host + ":" + remote;
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
sudo apt-get install -y build-essential cmake ninja-build git python3 python3-venv clang clang-format clang-tidy gdb openssh-client
```

Verify scp:
```
scp -V
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
1) Read `learner/src/main.cpp` and identify the required output format.
   The function must return a string in the exact `scp` format: `scp <local> <user>@<host>:<remote>`. The test checks for this substring, so spacing and separators must be correct. (Source: [OpenSSH scp manual](https://man.openbsd.org/scp))
   How: write the expected command using the example values from `exercise()` so you can compare your output character-by-character.
   - **Expected result:** you can write the target format without looking it up.

2) Implement `make_scp_cmd` using string concatenation.
   Start with `"scp "`, append the local path, a space, then `user@host:remote`. Keep it simple and deterministic. Do not introduce extra whitespace or quotes unless required by your inputs. (Source: [OpenSSH scp manual](https://man.openbsd.org/scp))
   How: build the string in order and avoid any conditional logic. This exercise is about precise formatting, not input validation.
   - **Expected result:** calling the function with test inputs returns the expected command string.

3) Implement `exercise()` to validate the command.
   Call `make_scp_cmd` with known values and check that the command contains the expected string. Return 0 on success and non-zero on failure. (Source: [OpenSSH scp manual](https://man.openbsd.org/scp))
   How: store the command in a local variable, then use `find()` to check for the exact substring. This is a robust way to detect extra spaces or missing separators.
   - **Expected result:** `exercise()` returns 0 when the command format is correct.

4) Remove `#error TODO_implement_exercise`, rebuild, and run tests.
   If tests fail, compare your output string against the expected format and check for missing spaces. (Source: [OpenSSH scp manual](https://man.openbsd.org/scp))
   How: remove the `#error`, rebuild, and run `ctest`. If the test fails, print the string locally (temporarily) or compare with the expected literal in `exercise()`.
   - **Expected result:** `ctest` reports `100% tests passed`.

5) Capture artifacts.
   Redirect build output to `learner/artifacts/build.log` and test output to `learner/artifacts/ctest.log`. (Source: [OpenSSH scp manual](https://man.openbsd.org/scp))
   How: use `> file 2>&1` so stderr is captured alongside stdout.
   - **Expected result:** logs exist and contain your command output.

## 9) Verification
- `ctest --test-dir build_learner --output-on-failure` must report `100% tests passed`.

## 10) Artifacts to save
- `build.log` and `ctest.log` in `learner/artifacts/`.

## 11) Grade this exercise
- Learner attempt: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/08_cross_deploy/exercises/ex02_deploy`
- Solution check: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/08_cross_deploy/exercises/ex02_deploy --use-solution`

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- Build fails: ensure `<string>` is included.
- Test fails: verify the exact spacing and separators in the command string.

## 13) Stretch goals
- Add optional `-P` port support to the command builder.
- Add path escaping for spaces and special characters.
