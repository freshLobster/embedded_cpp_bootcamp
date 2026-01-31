#pragma once

// Runs the TSan log exercise self-check.
// Return 0 on success; non-zero codes map to specific failures.
// The test intentionally exercises concurrent logging to surface data races.
int exercise();
