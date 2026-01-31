#pragma once

// Runs the CI manifest exercise self-check.
// Return 0 on success; non-zero codes map to specific failures.
// The manifest is text-only to keep CI deterministic.
int exercise();
