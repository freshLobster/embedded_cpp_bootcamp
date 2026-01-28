#include <benchmark/benchmark.h>

#include "platform/bounded_queue.hpp"

static void BM_BoundedQueue_PushPop(benchmark::State& state) {
    platform::BoundedQueue<int> q(static_cast<std::size_t>(state.range(0)));
    for (auto _ : state) {
        q.push(1);
        auto v = q.pop();
        benchmark::DoNotOptimize(v);
    }
}
BENCHMARK(BM_BoundedQueue_PushPop)->Arg(64)->Arg(256)->Arg(1024);

BENCHMARK_MAIN();

