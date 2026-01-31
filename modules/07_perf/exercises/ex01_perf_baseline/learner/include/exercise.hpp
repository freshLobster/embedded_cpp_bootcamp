#pragma once

// Runs the perf baseline exercise self-check.
// Return 0 on success; non-zero codes map to specific failures.
// The workload is intentionally small so perf measurements are repeatable.
int exercise();
