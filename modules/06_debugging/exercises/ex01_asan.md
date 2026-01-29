# ex01_asan – ASan repro and fix log

What you are building: ASan run log before/after fix of UAF (reuse Module02 fix or reintroduce temporarily).
Why it matters: Skill in reading sanitizer output.

Prerequisites check
- `cmake --preset asan`

Files you will touch
- None (code optional); artifacts only.

Steps
1. Build with UAF enabled: `cmake --preset asan -DPLATFORM_FAILURE_UAF=ON && cmake --build --preset asan`
2. Run tests: `ctest --preset asan --output-on-failure > modules/06_debugging/artifacts/ex01_asan.txt`
Expected: ASan failure logged.
3. Disable flag, rebuild, rerun and append results to same log showing PASS.

Verification
- Log contains both fail and pass sections.

Stop here and commit
- Message: "Module06: ASan repro log"

If it fails
- No ASan output: ensure preset uses Clang/GCC not MSVC.
