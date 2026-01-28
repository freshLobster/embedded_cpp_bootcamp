add_library(platform_core_cuda STATIC cuda_stage.cu)
target_include_directories(platform_core_cuda PUBLIC ${PROJECT_SOURCE_DIR}/include)
set_target_properties(platform_core_cuda PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
target_compile_options(platform_core_cuda PRIVATE $<$<COMPILE_LANGUAGE:CUDA>:--expt-relaxed-constexpr>)

target_compile_definitions(platform_core_cuda PUBLIC PLATFORM_ENABLE_CUDA)
target_link_libraries(platform_core_cuda PRIVATE platform_core)
