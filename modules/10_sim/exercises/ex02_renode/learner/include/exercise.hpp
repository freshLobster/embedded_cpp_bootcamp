#pragma once

// Runs the Renode peripheral count exercise self-check.
// Return 0 on success; non-zero codes map to specific failures.
// The parsing logic is string-based so it is simulator-agnostic.
int exercise();
