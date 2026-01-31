#pragma once

// Runs the flamegraph call-chain exercise self-check.
// Return 0 on success; non-zero codes map to specific failures.
// The call chain is structured to produce visible flamegraph stacks.
int exercise();
