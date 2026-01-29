# ex01_latency_budget – Measure publish→actuator latency

What you are building: CSV of latency percentiles over 2 minutes.
Why it matters: Real-time-ish guarantees for control loops.

Prerequisites check
- `python3 --version`

Files you will touch
- `src/platform/pipeline.cpp` (to capture timestamps if needed)
- `modules/05_scheduling/artifacts/ex01_latency.csv`

Steps
1. Add timestamp capture at publish and actuator log; write CSV line "start_ns,end_ns,delta_ns" to stdout or file.
2. Build release app and run 120s:
```
cmake --build --preset release --target platform_core_app
./build/release/platform_core_app > modules/05_scheduling/artifacts/ex01_latency.csv 2>&1 & sleep 120; pkill platform_core_app
```
3. Compute percentiles:
```
python3 - <<'EOF'
import numpy as np, pandas as pd
import sys
import pathlib
p=pathlib.Path('modules/05_scheduling/artifacts/ex01_latency.csv')
d=pd.read_csv(p, names=['start','end','delta'])
for q in [50,95,99]:
    print(f"p{q}={d.delta.quantile(q/100)/1e6:.3f} ms")
EOF
```
Expected: p50 <5ms, p95 <10ms on dev box.

Verification
- Percentiles within budget.
- `ctest --preset release` passes.

Stop here and commit
- Message: "Module05: latency budget capture"

If it fails
- CSV empty: ensure logging writes CSV and not filtered by log level.

Stretch goals
- Add rolling window metrics to log every 10s.
