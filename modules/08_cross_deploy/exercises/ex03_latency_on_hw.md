# ex03_latency_on_hw – Measure latency on SBC

What you are building: Latency CSV from real sensor/loop on SBC.
Why it matters: Hardware validation.

Prerequisites check
- Sensor wired per docs/hardware/sbc.md; clock synced (`timedatectl`).

Files you will touch
- `modules/08_cross_deploy/artifacts/ex03_latency_pi.csv`

Steps
1. Run app on SBC with latency logging enabled (reuse Module05 logging) and redirect to CSV.
2. Copy CSV back: `scp pi@raspberrypi.local:/home/pi/latency.csv modules/08_cross_deploy/artifacts/ex03_latency_pi.csv`
3. Compute percentiles (same script as Module05) and note results.

Verification
- p95 <15ms on SBC target.

Stop here and commit
- Message: "Module08: SBC latency capture"

If it fails
- Missing CSV: ensure logging path exists and permissions ok.
