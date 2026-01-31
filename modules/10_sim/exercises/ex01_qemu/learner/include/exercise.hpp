#pragma once

// Runs the QEMU boot log exercise self-check.
// Return 0 on success; non-zero codes map to specific failures.
// The exercise is log-parsing only; no QEMU API is required.
int exercise();
