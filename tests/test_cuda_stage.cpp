#include <gtest/gtest.h>

#include "platform/cuda_stage.hpp"

TEST(CudaStage, CpuReference) {
    std::vector<float> a{1, 2, 3};
    std::vector<float> b{4, 5, 6};
    std::vector<float> out;
    platform::vector_add_cpu(a, b, out);
    ASSERT_EQ(out.size(), 3u);
    EXPECT_FLOAT_EQ(out[0], 5.0f);
    EXPECT_FLOAT_EQ(out[2], 9.0f);
}

#ifdef PLATFORM_ENABLE_CUDA
TEST(CudaStage, GpuMatchesCpu) {
    std::vector<float> a(1024, 1.0f);
    std::vector<float> b(1024, 2.0f);
    std::vector<float> cpu, gpu;
    platform::vector_add_cpu(a, b, cpu);
    if (!platform::check_cuda_available()) {
        GTEST_SKIP() << "No CUDA device available";
    }
    ASSERT_TRUE(platform::vector_add_cuda(a, b, gpu));
    ASSERT_EQ(cpu.size(), gpu.size());
    for (std::size_t i = 0; i < cpu.size(); ++i) {
        EXPECT_FLOAT_EQ(cpu[i], gpu[i]);
    }
}
#endif

