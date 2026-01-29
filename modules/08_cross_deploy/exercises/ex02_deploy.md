# ex02_deploy – Push binary to SBC and run

What you are building: Deployed platform_core_app on SBC with systemd.
Why it matters: Real hardware validation loop.

Hardware required
- Raspberry Pi/Orange Pi reachable via SSH; sensor optional for this step.

Prerequisites check
- `ssh pi@raspberrypi.local 'echo ok'`

Files you will touch
- `modules/08_cross_deploy/artifacts/ex02_run.log`

Steps
1. Deploy: `./scripts/deploy_to_sbc.sh pi@raspberrypi.local /home/pi/bin`
2. Run remotely:
```
ssh pi@raspberrypi.local '/home/pi/bin/platform_core_app --help' > modules/08_cross_deploy/artifacts/ex02_run.log
```
Expected: help text printed.
3. (Optional) Install systemd unit from docs/hardware/sbc.md

Verification
- Log contains usage/help output.

Stop here and commit
- Message: "Module08: deploy to SBC"

If it fails
- Permission denied: ensure ssh keys or password auth.
