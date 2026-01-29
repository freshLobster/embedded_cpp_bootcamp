# ex01_pmr_queue – PMR-backed bounded queue

What you are building: Optional polymorphic allocator support for `BoundedQueue<T>`.
Why it matters: Bounded allocations reduce jitter and fragmentation in embedded systems.

Prerequisites check
- `grep -n "class BoundedQueue" include/platform/bounded_queue.hpp`
- `ctest --preset dev -N | grep BoundedQueue`

Files you will touch
- `include/platform/bounded_queue.hpp`
- `benchmarks/bench_queue.cpp`

Steps
1. Add template allocator parameter (pmr deque) behind a preprocessor guard to keep default behavior. Example: switch `std::deque` to `std::pmr::deque` when allocator provided.
2. Add constructor overload taking `std::pmr::memory_resource*`.
3. Update benchmark to construct queue with a monotonic buffer resource for one case.
Command snippets:
```
# edit header accordingly (manual)
# update bench
apply_patch <<'EOF'
*** Begin Patch
*** Update File: benchmarks/bench_queue.cpp
@@
 static void BM_BoundedQueue_PushPop(benchmark::State& state) {
-    platform::BoundedQueue<int> q(static_cast<std::size_t>(state.range(0)));
+    std::pmr::monotonic_buffer_resource pool(1024*64);
+    platform::BoundedQueue<int> q(static_cast<std::size_t>(state.range(0)), &pool);
*** End Patch
EOF
```
Expected: benchmark builds using pmr queue.

4. Build + run benchmark (WSL):
```
cmake --build --preset release --target platform_core_bench
./build/release/platform_core_bench --benchmark_filter=BoundedQueue > modules/02_memory/artifacts/ex01_bench.txt
```
Expected results: benchmark output saved; no runtime errors.

Verification
- Benchmark runs and reports iterations; latency not worse than baseline (<2x default).
- Unit tests still pass: `ctest --preset dev`.

Stop here and commit
- Message: "Module02: add PMR option to BoundedQueue"

If it fails
- Missing <memory_resource>: include it.
- Allocation errors: ensure pool size covers benchmark; increase buffer if needed.

Stretch goals
- Allow allocator parameter on push to reuse arenas per-producer.
