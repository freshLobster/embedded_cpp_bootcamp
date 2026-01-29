# Troubleshooting - 03_concurrency ex01_race_repro

## Common failures

1) **Build fails due to TODO placeholder**
   - Symptom: compiler error referencing `#error TODO_implement_exercise`.
   - Fix: remove the `#error` line after you implement a thread-safe counter that increments correctly under contention.
   - Verify: `cmake --build build_learner` succeeds.

2) **Tests fail with assertion**
   - Symptom: `Assertion 'exercise() == 0' failed` or similar.
   - Fix: inspect `exercise()` and ensure it enforces the required behavior for a thread-safe counter that increments correctly under contention.
   - Verify: `ctest --test-dir build_learner --output-on-failure` reports 100% passed.
