# Troubleshooting - 04_architecture ex03_backpressure

1) **Build fails due to TODO placeholder**
   - Fix: remove the `#error` line after you implement a bounded queue that enforces backpressure by rejecting pushes when full.

2) **Tests fail with assertion**
   - Fix: inspect `exercise()` and ensure it enforces the required behavior.
