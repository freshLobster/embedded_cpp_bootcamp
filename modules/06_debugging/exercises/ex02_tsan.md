# ex02_tsan – TSan race log

What you are building: ThreadSanitizer capture of intentional race and clean rerun.
Why it matters: Confidently use TSan on concurrency issues.

Prerequisites check
- `cmake --preset dev -DPLATFORM_ENABLE_TSAN=ON`

Files you will touch
- None unless fixing race.

Steps
1. Configure with race flag: `cmake --preset dev -DPLATFORM_FAILURE_RACE=ON -DPLATFORM_ENABLE_TSAN=ON`
2. Build + run filtered tests: `TSAN_OPTIONS="halt_on_error=1" ctest --preset dev -R BoundedQueue > modules/06_debugging/artifacts/ex02_tsan.txt`
3. Disable flag and rerun append to log showing clean run.

Verification
- Log shows race stack then clean pass.

Stop here and commit
- Message: "Module06: TSan capture"

If it fails
- TSan unsupported on platform: note in log and skip.
