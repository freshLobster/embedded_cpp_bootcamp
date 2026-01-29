# Troubleshooting - 01_foundations ex03_interface_review

## Common failures

1) **Build fails due to TODO placeholder**
   - Symptom: compiler error referencing `#error TODO_implement_exercise`.
   - Fix: remove the `#error` line after you implement a move-only buffer type that follows Rule of 5/0 and avoids accidental copying.
   - Verify: `cmake --build build_learner` succeeds.

2) **Tests fail with assertion**
   - Symptom: `Assertion 'exercise() == 0' failed` or similar.
   - Fix: inspect `exercise()` and ensure it enforces the required behavior for a move-only buffer type that follows Rule of 5/0 and avoids accidental copying.
   - Verify: `ctest --test-dir build_learner --output-on-failure` reports 100% passed.

3) **Link errors (undefined symbols)**
   - Symptom: linker errors about missing functions.
   - Fix: ensure all helper functions/classes are defined in the same translation unit or in headers.
   - Verify: rebuild and re-run tests.
