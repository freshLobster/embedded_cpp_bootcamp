cmake_minimum_required(VERSION 3.21)

project(platform_core_training LANGUAGES CXX C)

include(cmake/PreventInSourceBuild.cmake OPTIONAL)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(PLATFORM_ENABLE_CUDA "Build CUDA integrations" OFF)
option(PLATFORM_ENABLE_SANITIZERS "Enable ASan/UBSan for supported compilers" OFF)
option(PLATFORM_ENABLE_TSAN "Enable TSan for supported compilers" OFF)
option(PLATFORM_FAILURE_RACE "Inject data race bug" OFF)
option(PLATFORM_FAILURE_DEADLOCK "Inject deadlock bug" OFF)
option(PLATFORM_FAILURE_UAF "Inject use-after-free bug" OFF)
option(PLATFORM_FAILURE_PERF "Inject perf regression from copies/allocations" OFF)

include(FetchContent)

if(PLATFORM_ENABLE_CUDA)
  enable_language(CUDA)
  set(CMAKE_CUDA_STANDARD 17)
  set(CMAKE_CUDA_STANDARD_REQUIRED ON)
endif()

add_library(platform_core
    src/platform/thread_pool.cpp
    src/platform/scheduler.cpp
    src/platform/message_bus.cpp
    src/platform/pipeline.cpp
    src/platform/logging.cpp
    src/platform/cuda_stage_cpu.cpp
)

target_include_directories(platform_core
    PUBLIC
      ${PROJECT_SOURCE_DIR}/include
)

target_compile_definitions(platform_core
    PUBLIC
      $<$<BOOL:${PLATFORM_FAILURE_RACE}>:PLATFORM_FAILURE_RACE>
      $<$<BOOL:${PLATFORM_FAILURE_DEADLOCK}>:PLATFORM_FAILURE_DEADLOCK>
      $<$<BOOL:${PLATFORM_FAILURE_UAF}>:PLATFORM_FAILURE_UAF>
      $<$<BOOL:${PLATFORM_FAILURE_PERF}>:PLATFORM_FAILURE_PERF>
      $<$<BOOL:${PLATFORM_ENABLE_CUDA}>:PLATFORM_ENABLE_CUDA>
)

target_compile_options(platform_core
    PRIVATE
      $<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive- /EHsc>
      $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Wconversion>
)

function(platform_apply_sanitizers target)
    if(PLATFORM_ENABLE_SANITIZERS AND NOT MSVC)
        target_compile_options(${target} PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer)
        target_link_options(${target} PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer)
    endif()
    if(PLATFORM_ENABLE_TSAN AND NOT MSVC)
        target_compile_options(${target} PRIVATE -fsanitize=thread -fno-omit-frame-pointer)
        target_link_options(${target} PRIVATE -fsanitize=thread -fno-omit-frame-pointer)
    endif()
endfunction()

platform_apply_sanitizers(platform_core)

add_executable(platform_core_app src/main.cpp)
target_link_libraries(platform_core_app PRIVATE platform_core)
platform_apply_sanitizers(platform_core_app)

# CUDA optional stage
if(PLATFORM_ENABLE_CUDA)
    add_subdirectory(src/cuda)
    target_link_libraries(platform_core_app PRIVATE platform_core_cuda)
    target_link_libraries(platform_core_tests PRIVATE platform_core_cuda)
endif()

# Tests
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(platform_core_tests
    tests/test_bounded_queue.cpp
    tests/test_scope_guard.cpp
    tests/test_message_bus.cpp
    tests/test_scheduler.cpp
    tests/test_cuda_stage.cpp
)
target_link_libraries(platform_core_tests PRIVATE platform_core GTest::gtest_main)
platform_apply_sanitizers(platform_core_tests)

include(GoogleTest)
gtest_discover_tests(platform_core_tests)

# Benchmarks
FetchContent_Declare(
  googlebenchmark
  URL https://github.com/google/benchmark/archive/refs/tags/v1.8.3.zip
)
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Disable benchmark self-tests" FORCE)
FetchContent_MakeAvailable(googlebenchmark)

add_executable(platform_core_bench
    benchmarks/bench_queue.cpp
)
target_link_libraries(platform_core_bench PRIVATE platform_core benchmark::benchmark)
platform_apply_sanitizers(platform_core_bench)

# Install configs for clang-format/clang-tidy convenience
install(FILES .clang-format .clang-tidy DESTINATION share/platform_core_training)
