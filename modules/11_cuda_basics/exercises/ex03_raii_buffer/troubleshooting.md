# Troubleshooting - 11_cuda_basics ex03_raii_buffer

1) **Build fails due to TODO placeholder**
   - Fix: remove the `#error` line after you implement a RAII buffer wrapper that is move-only and owns its memory.

2) **Tests fail with assertion**
   - Fix: inspect `exercise()` and ensure it enforces the required behavior.
