# 02_memory - ex01_pmr_queue

## 1) Title + Mission
Mission: implement a queue that allocates from a caller-provided polymorphic memory resource so memory usage is bounded and deterministic. (Source: [cppreference: std::pmr::memory_resource](https://en.cppreference.com/w/cpp/memory/memory_resource))

## 2) What you are building (plain English)
You are building a small queue where the memory allocation strategy is provided at runtime. Instead of using the global heap, the queue pulls memory from a supplied buffer or arena. (Source: [cppreference: std::pmr::polymorphic_allocator](https://en.cppreference.com/w/cpp/memory/polymorphic_allocator))

## 3) Why it matters (embedded/robotics/defense relevance)
Real-time systems cannot tolerate unbounded heap growth or unpredictable allocation costs. Polymorphic memory resources let you control allocation behavior while still using standard containers, which is essential for deterministic latency and memory usage in embedded platforms. (Source: [cppreference: std::pmr::monotonic_buffer_resource](https://en.cppreference.com/w/cpp/memory/monotonic_buffer_resource))

## 4) Concepts (short lecture)
`std::pmr::memory_resource` is the abstract interface for allocation and deallocation. Containers that use `std::pmr::polymorphic_allocator` forward allocations to whatever resource you provide at runtime. This decouples container types from allocation strategies. (Source: [cppreference: std::pmr::memory_resource](https://en.cppreference.com/w/cpp/memory/memory_resource))

`std::pmr::monotonic_buffer_resource` is a fast arena that allocates from a fixed buffer and never frees individual allocations. It is ideal for fixed-size, phase-based workloads, which are common in robotics pipelines where you can discard all allocations at once. (Source: [cppreference: std::pmr::monotonic_buffer_resource](https://en.cppreference.com/w/cpp/memory/monotonic_buffer_resource))

Example (not your solution): a `pmr::vector` bound to a specific resource. Comments call out where the resource is used.
```cpp
std::byte buffer[256];
std::pmr::monotonic_buffer_resource res(buffer, sizeof(buffer));

// The vector uses the supplied resource, not the global heap.
std::pmr::vector<int> v(&res);
v.push_back(42); // allocation is served by `res`
```

## 5) Repo context (this folder only)
- `learner/`: incomplete code you must finish. Contains its own `CMakeLists.txt`, `include/`, `src/`, `tests/`, and `artifacts/`.
- `solution/`: working reference that compiles and passes tests immediately.
- `grading/`: rubric.json used by the grader.
- `tools/`: optional helper scripts (if any).
- `troubleshooting.md`: common failure modes.
- `references.md`: links to repo-level conventions.

## 6) Prerequisites checks
Install tools (Ubuntu/WSL2, run once):
```
sudo apt-get update
sudo apt-get install -y build-essential cmake ninja-build git python3 python3-venv clang clang-format clang-tidy gdb
```

Run these in **this exercise folder**:
```
cmake --version
```
Expected output (example): `cmake version 3.22.1`.

```
c++ --version
```
Expected output (example): `g++ (Ubuntu 11.4.0)` or `clang version 14.x`.

If you will use Ninja:
```
ninja --version
```
Expected output: a version number (e.g., `1.10.1`). If Ninja is missing, use the Visual Studio generator on Windows.

## 7) Build instructions (learner + solution)
### Learner path (fails initially until you implement)
```
cmake -S learner -B build_learner -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build_learner
ctest --test-dir build_learner --output-on-failure
```
Expected initial failure: compilation error due to `#error TODO_implement_exercise`.

Windows (no Ninja):
```
cmake -S learner -B build_learner -G "Visual Studio 17 2022"
cmake --build build_learner --config Debug
ctest --test-dir build_learner -C Debug --output-on-failure
```

### Solution path (must pass immediately)
```
cmake -S solution -B build_solution -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build_solution
ctest --test-dir build_solution --output-on-failure
```
Expected output: `100% tests passed`.

Windows (no Ninja):
```
cmake -S solution -B build_solution -G "Visual Studio 17 2022"
cmake --build build_solution --config Debug
ctest --test-dir build_solution -C Debug --output-on-failure
```

## 8) Step-by-step implementation instructions
1) Read `learner/src/main.cpp` and locate the allocator injection point.
   The `PmrQueue` constructor takes a `std::pmr::memory_resource*` and passes it into `storage_`. This is the key: all allocations performed by `storage_` must come from that resource. Identify exactly where `storage_` is constructed and how the resource is passed in. (Source: [cppreference: std::pmr::polymorphic_allocator](https://en.cppreference.com/w/cpp/memory/polymorphic_allocator))
   - **Expected result:** you can explain how the queue is bound to the memory resource at construction.

2) Implement `PmrQueue::resource()` to expose the allocator.
   `std::pmr::vector` uses a `polymorphic_allocator` internally. Call `storage_.get_allocator().resource()` and return it. This is how you prove, at runtime, which resource the queue is using. (Source: [cppreference: std::pmr::polymorphic_allocator](https://en.cppreference.com/w/cpp/memory/polymorphic_allocator))
   - **Expected result:** the test sees the exact same pointer that was passed into the constructor.

3) Implement `push()` with a clear FIFO policy.
   Append values to `storage_` with `push_back`. This maintains order. Because `storage_` is a PMR container, any growth allocations must come from the provided memory resource. Do not allocate any additional containers in `push()`. (Source: [cppreference: std::vector::push_back](https://en.cppreference.com/w/cpp/container/vector/push_back))
   - **Expected result:** after three pushes, `storage_` holds {1,2,3} in that order.

4) Implement `pop()` using the `head_` index.
   If `head_` is already at or beyond `storage_.size()`, the queue is empty and you should return false. Otherwise, read `storage_[head_]`, store it in `out`, then increment `head_`. This gives FIFO semantics without erasing elements (a simple, deterministic queue model for the exercise). (Source: [cppreference: std::vector::size](https://en.cppreference.com/w/cpp/container/vector/size))
   - **Expected result:** the first pop returns 1, the second returns 2.

5) Implement `size()` as remaining elements.
   The queue size is `storage_.size() - head_`. This is the number of elements not yet popped. If you return `storage_.size()` directly, your size will be wrong after pops. (Source: [cppreference: std::vector::size](https://en.cppreference.com/w/cpp/container/vector/size))
   - **Expected result:** after two pops from three pushes, `size()` returns 1.

6) Remove `#error TODO_implement_exercise`, rebuild, and run tests.
   If compilation fails, ensure `<memory_resource>` is included and that you didn't accidentally shadow `head_`. (Source: [cppreference: std::pmr::memory_resource](https://en.cppreference.com/w/cpp/memory/memory_resource))
   - **Expected result:** `ctest` reports `100% tests passed`.

7) Capture artifacts.
   Redirect build output to `learner/artifacts/build.log` and test output to `learner/artifacts/ctest.log` so the grader can verify your run. (Source: [cppreference: std::pmr::memory_resource](https://en.cppreference.com/w/cpp/memory/memory_resource))
   - **Expected result:** both log files exist and contain the command output.

## 9) Verification
- `ctest --test-dir build_learner --output-on-failure` must report `100% tests passed`.
- If it fails, stop and read `troubleshooting.md`.

## 10) Artifacts to save
Place these in `learner/artifacts/`:
- `build.log` - stdout/stderr from the build step.
- `ctest.log` - stdout/stderr from the test step.
Example snippet for `ctest.log`:
```
1/1 Test #1: ...   Passed
100% tests passed, 0 tests failed out of 1
```

## 11) Grade this exercise
- Learner attempt:
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/02_memory/exercises/ex01_pmr_queue`
- Solution check:
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/02_memory/exercises/ex01_pmr_queue --use-solution`
- High-level scoring:
  - Configure/build: 40 points
  - Tests: 40 points
  - Artifacts present: 20 points

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- If build fails: verify you removed `#error` and included `<memory_resource>`.
- If tests fail: confirm `resource()` returns the allocator's resource and `size()` accounts for `head_`.

## 13) Stretch goals
- Add wrap-around behavior using a ring buffer to avoid unbounded growth.
- Add a `clear()` method that resets `head_` and shrinks storage if needed.
