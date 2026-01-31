#pragma once

// Runs the perf regression exercise self-check.
// Return 0 on success; non-zero codes map to specific failures.
// The string concatenation logic should avoid unnecessary allocations.
int exercise();
