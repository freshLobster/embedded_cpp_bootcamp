# ex02_renode – MCU simulation script

What you are building: Renode script that boots ESP32-like platform and logs I2C transactions.
Why it matters: Deterministic MCU regression tests.

Prerequisites check
- `renode --version`

Files you will touch
- `modules/10_sim/starter/esp.resc`
- `modules/10_sim/artifacts/ex02_renode.log`

Steps
1. Create script:
```
cat > modules/10_sim/starter/esp.resc <<'EOF'
emulation CreateMachine "esp"
using sysbus
mach create "esp"
# Placeholder: add CPU/peripheral models when available.
EOF
```
2. Run renode headless:
```
renode-cli modules/10_sim/starter/esp.resc > modules/10_sim/artifacts/ex02_renode.log
```
Expected: Renode runs script without errors (stub).

Verification
- Log contains no errors; exit code 0.

Stop here and commit
- Message: "Module10: renode stub"

If it fails
- Renode missing: install per upstream instructions.
