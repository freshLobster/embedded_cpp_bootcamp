# Module 02_memory - Memory

**Mission:** Allocators, bounded memory, UAF fix.

**Estimated time:** 2-4 hours.

## Setup checklist (WSL2 primary, Windows notes)
- WSL2 Ubuntu: `sudo apt-get update && sudo apt-get install -y build-essential cmake ninja-build git python3 python3-venv clang clang-format clang-tidy gdb`
- Optional (heap profiling): `sudo apt-get install -y heaptrack valgrind`
- Verify compiler: `clang++ --version` (expect version output). On Windows native: open "x64 Native Tools" and run `cl /?`.
- Repo root contains `CMakePresets.json` and `tools/grader/grade.py`.

## Lecture

### Memory resources and polymorphic allocators
The C++ PMR (polymorphic memory resource) facility separates allocation *behavior* from allocation *sites*. `std::pmr::memory_resource` is an abstract interface for memory resources, and `std::pmr::polymorphic_allocator` uses a `memory_resource` to define how allocations happen at runtime. This lets you keep container types stable while swapping the backing allocator policy without changing template parameters-valuable in embedded systems where the same code must run on a workstation, SBC, and MCU-class target with different memory constraints.  ([cppreference: memory_resource](https://en.cppreference.com/w/cpp/memory/memory_resource), [cppreference: polymorphic_allocator](https://en.cppreference.com/w/cpp/memory/polymorphic_allocator))

The `polymorphic_allocator` also propagates allocator awareness to elements constructed by containers (the "uses-allocator" mechanism), so nested PMR containers share the same resource automatically. That matters in autonomy code where a pipeline stage might carry vectors of strings or messages; allocator propagation ensures the whole object graph draws from the same arena and gives you predictable deallocation behavior.  ([cppreference: polymorphic_allocator](https://en.cppreference.com/w/cpp/memory/polymorphic_allocator))

### Bounded arenas with monotonic_buffer_resource
`std::pmr::monotonic_buffer_resource` is a special-purpose resource designed for very fast allocation when many objects are created and then released all at once. It can be constructed with an initial buffer, and if that buffer is exhausted it can request more memory from an upstream resource; when the resource is destroyed it releases all allocated memory in bulk. This "bump-pointer" style is ideal for deterministic phases like "build a frame's data, then discard it," which shows up constantly in robotics perception pipelines.  ([cppreference: monotonic_buffer_resource](https://en.cppreference.com/w/cpp/memory/monotonic_buffer_resource))

Because the resource releases everything together and is not thread-safe, it encourages a clear ownership model: one thread or stage owns the arena and explicitly bounds its lifetime. This makes memory consumption and fragmentation far more predictable than unconstrained `new`/`delete` patterns, especially when you pre-allocate a buffer sized to your worst-case frame. In embedded deployment, that predictability is a reliability feature, not just an optimization.  ([cppreference: monotonic_buffer_resource](https://en.cppreference.com/w/cpp/memory/monotonic_buffer_resource))

### Lifetime rules, use-after-free, and ownership vocabulary
C++ defines object lifetime precisely: an object's lifetime begins when storage is obtained and initialization completes, and ends when the destructor starts or the storage is released. Accessing an object after its lifetime ends is undefined behavior, which is the formal basis for "use-after-free" bugs that manifest as flaky crashes or silent corruption. For safety-critical systems, understanding this rule is essential because the bug might only appear under load or in rare timing windows.  ([cppreference: object lifetime](https://en.cppreference.com/w/cpp/language/lifetime))

AddressSanitizer is a practical tool for catching these errors-it instruments code and detects use-after-free and other memory violations, and it is enabled by compiling with `-fsanitize=address`. In addition, the C++ Core Guidelines recommend expressing ownership with `unique_ptr` or `shared_ptr` and preferring `unique_ptr` unless shared ownership is required, which reduces the surface area for lifetime mistakes. In robotics software where components are composed dynamically and tested under time pressure, combining ownership-explicit APIs with sanitizer runs is one of the most effective defenses against memory regressions.  ([AddressSanitizer](https://clang.llvm.org/docs/AddressSanitizer.html), [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines))

## Start here
1) Pick one exercise folder below and `cd` into it.
2) Follow the exercise README exactly; it includes build/test commands and grading steps.
3) Save outputs in that exercise's `learner/artifacts/`.

## Exercises (per-folder)
| Exercise | Link |
|---|---|
| ex01_pmr_queue | [ex01_pmr_queue](exercises/ex01_pmr_queue/README.md) |
| ex02_uaf_fix | [ex02_uaf_fix](exercises/ex02_uaf_fix/README.md) |
| ex03_heaptrack | [ex03_heaptrack](exercises/ex03_heaptrack/README.md) |

## Done definition
- Each exercise you attempt has passing tests and saved artifacts.
- The per-exercise grader reports a numeric score.
- Module-level artifacts (if any) are stored in `modules/02_memory/artifacts/`.

## Checklists and evidence
Use these files in `modules/02_memory/checklists/`:
- `mastery.md`: confirm you can explain the module goal, list failure modes you found, and map skills to autonomy/defense use cases.
- `validation.md`: run the validation commands and record results. At minimum:
  - `cmake --preset dev`
  - `ctest --preset dev -R Module02_memory` (if the module test filter exists)
- `review.md`: perform a quick self-review against `STYLE.md` and confirm no warnings or unsafe patterns remain.

Save any required artifacts in `modules/02_memory/artifacts/` and in each exercise's `learner/artifacts/` folder.

## Grade this module
- Module-level grader: `python3 tools/grader/grade.py --module modules/02_memory`
- JSON: `python3 tools/grader/grade.py --module 02 --json`
- Per-exercise grading is done inside each exercise folder README.
