#pragma once

// Runs the GDB remote checksum exercise self-check.
// Return 0 on success; non-zero codes map to specific failures.
// The checksum is intentionally simple to keep debugging deterministic.
int exercise();
