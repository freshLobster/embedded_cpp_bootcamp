# Troubleshooting - 01_foundations ex02_message_bus_view

## Common failures

1) **Build fails due to TODO placeholder**
   - Symptom: compiler error referencing `#error TODO_implement_exercise`.
   - Fix: remove the `#error` line after you implement a const-correct read-only view over a message bus subscriber list.
   - Verify: `cmake --build build_learner` succeeds.

2) **Tests fail with assertion**
   - Symptom: `Assertion 'exercise() == 0' failed` or similar.
   - Fix: inspect `exercise()` and ensure it enforces the required behavior for a const-correct read-only view over a message bus subscriber list.
   - Verify: `ctest --test-dir build_learner --output-on-failure` reports 100% passed.

3) **Link errors (undefined symbols)**
   - Symptom: linker errors about missing functions.
   - Fix: ensure all helper functions/classes are defined in the same translation unit or in headers.
   - Verify: rebuild and re-run tests.
