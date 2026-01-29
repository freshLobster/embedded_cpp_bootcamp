# ex02_flamegraph – Generate flamegraph

What you are building: Flamegraph of platform_core_app.
Why it matters: Visual hotspot identification.

Prerequisites check
- `perf` and Brendan Gregg's scripts available (clone if needed)

Files you will touch
- `modules/07_perf/artifacts/ex02_flame.svg`

Steps
1. Record profile 30s:
```
sudo perf record -g -- ./build/release/platform_core_app
```
2. Generate SVG (assuming FlameGraph scripts in ~/FlameGraph):
```
perf script | ~/FlameGraph/stackcollapse-perf.pl | ~/FlameGraph/flamegraph.pl > modules/07_perf/artifacts/ex02_flame.svg
```
Expected: SVG created.

Verification
- Open SVG (view in browser) and note top 3 functions in a text note.

Stop here and commit
- Message: "Module07: flamegraph"

If it fails
- Missing scripts: git clone https://github.com/brendangregg/FlameGraph
