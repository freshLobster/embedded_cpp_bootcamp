# Troubleshooting - 02_memory ex02_uaf_fix

## Common failures

1) **Build fails due to TODO placeholder**
   - Symptom: compiler error referencing `#error TODO_implement_exercise`.
   - Fix: remove the `#error` line after you implement a safe factory that returns owned data without use-after-free.
   - Verify: `cmake --build build_learner` succeeds.

2) **Tests fail with assertion**
   - Symptom: `Assertion 'exercise() == 0' failed` or similar.
   - Fix: inspect `exercise()` and ensure it enforces the required behavior for a safe factory that returns owned data without use-after-free.
   - Verify: `ctest --test-dir build_learner --output-on-failure` reports 100% passed.
