# ex03_heaptrack – Heap profiling

What you are building: Heap profile of steady-state pipeline run and reduction of top allocator.
Why it matters: Bounded memory keeps robots predictable under load.

Prerequisites check
- Tool: `heaptrack --version` (install: `sudo apt install -y heaptrack`)

Files you will touch
- No code changes required; optional tweaks in `src/platform/pipeline.cpp` if needed.

Steps
1. Build release app: `cmake --build --preset release --target platform_core_app`
2. Run under heaptrack for 30s:
```
heaptrack ./build/release/platform_core_app --duration 30
mv heaptrack.* modules/02_memory/artifacts/ex03_heaptrack.gz
```
Expected: heaptrack output file created.
3. Inspect top allocation site using CLI:
```
heaptrack_print modules/02_memory/artifacts/ex03_heaptrack.gz | head -n 20 > modules/02_memory/artifacts/ex03_heaptrack_summary.txt
```
4. Reduce allocations (e.g., reserve strings, reuse buffers) and rerun to show drop.

Verification
- Summary shows decreased allocation count vs first run (aim >50% reduction in top site).
- App still runs without regression.

Stop here and commit
- Message: "Module02: heaptrack profile and optimizations"

If it fails
- heaptrack missing: install package.
- Output file not created: ensure app runs long enough; check permissions.

Stretch goals
- Automate heaptrack run via script in `scripts/`.
