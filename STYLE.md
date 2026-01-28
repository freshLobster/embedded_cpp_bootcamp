# Platform Core Style Guide

- C++20, no exceptions disabled; RTTI allowed.
- Prefer value semantics; pass by value then move; use `std::span`/`std::string_view` for non-owning.
- RAII everywhere: no raw `new`/`delete`, wrap resources in types.
- Header hygiene: minimal includes in headers; use forward declarations when possible.
- Concurrency: prefer `std::jthread`/`std::stop_token`; no detached threads; every thread joins.
- Logging: `LOG_*` macros only inside `src/platform/logging.*`; avoid `std::cout` elsewhere.
- Errors: functions returning status use `expected`-style return (TODO in code) or `std::optional` for absent values.
- No globals except explicitly tagged `constexpr` config and metrics.
- Tests mirror headers: for `foo.hpp` have `test_foo.cpp`.
- Clang-format/clang-tidy must pass before PR/review; warnings are errors in CI.
