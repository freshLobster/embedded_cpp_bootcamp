# ex02_race – ISR/task race reproduction

What you are building: Intentional shared variable race between timer ISR and task; then fix.
Why it matters: MCU concurrency correctness.

Prerequisites check
- Firmware from ex01 running.

Files you will touch
- `firmware/main/app.c`
- `modules/09_mcu/artifacts/ex02_race.log`

Steps
1. Add global volatile counter updated in ISR and read in task without protection; log mismatch counts.
2. Build/flash; capture monitor output to log.
3. Fix with critical section or atomic; rebuild/flash; append clean output to log.

Verification
- Before: log shows occasional mismatches.
- After: stable counts.

Stop here and commit
- Message: "Module09: fix ISR/task race"

If it fails
- ISR not firing: ensure timer created and enabled.
