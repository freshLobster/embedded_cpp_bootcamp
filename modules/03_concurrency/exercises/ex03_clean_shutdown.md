# ex03_clean_shutdown – Stop tokens in ThreadPool

What you are building: Ensure enqueues reject during shutdown and threads exit cleanly.
Why it matters: Reliable shutdown prevents partial actuator commands.

Prerequisites check
- Inspect current ThreadPool implementation: `sed -n '1,200p' src/platform/thread_pool.cpp`

Files you will touch
- `include/platform/thread_pool.hpp`
- `src/platform/thread_pool.cpp`
- `tests/test_thread_pool.cpp` (create)

Steps
1. Modify `enqueue` to check `shutting_down_` and return false without blocking.
2. Ensure worker loop exits when stop requested.
3. Add test:
```
cat > tests/test_thread_pool.cpp <<'EOF'
#include <gtest/gtest.h>
#include "platform/thread_pool.hpp"
TEST(Module03, ThreadPoolRejectsAfterShutdown){ platform::ThreadPool tp(2,8); EXPECT_TRUE(tp.enqueue([]{})); tp.shutdown(); EXPECT_FALSE(tp.enqueue([]{})); }
EOF
```
4. Build + run:
```
cmake --build --preset dev --target platform_core_tests
ctest --preset dev -R Module03
```
Expected: new test passes.

Verification
- All Module03 tests pass.

Stop here and commit
- Message: "Module03: stop-safe thread pool"

If it fails
- Link error: ensure file added to CMake if needed (already globbed by target). If not, add to `CMakeLists.txt` test list.

Stretch goals
- Add timeout on enqueue using condition_variable_any + stop_token.
