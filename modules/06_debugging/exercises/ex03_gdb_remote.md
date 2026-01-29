# ex03_gdb_remote – gdbserver on SBC (simulated ok)

What you are building: Remote debugging transcript connecting to gdbserver.
Why it matters: Field debugging on robots uses remote targets.

Prerequisites check
- SBC reachable or simulate with localhost.
- Tools: `gdb --version`, `gdbserver --version`.

Files you will touch
- `modules/06_debugging/artifacts/ex03_gdb_remote.log`

Steps
1. On target (or localhost), run: `gdbserver :2345 ./build/aarch64/platform_core_app`
2. On host: `gdb build/aarch64/platform_core_app -ex "target remote <target>:2345" -ex "b main" -ex run -ex bt -ex detach -ex quit > modules/06_debugging/artifacts/ex03_gdb_remote.log`
Expected: log shows breakpoint hit and backtrace.

Verification
- Log contains "Breakpoint 1, main" and backtrace lines.

Stop here and commit
- Message: "Module06: gdbserver workflow"

If it fails
- Connection refused: check firewall/port; ensure binary exists on target.
