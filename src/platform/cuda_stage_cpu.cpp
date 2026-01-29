// cuda_stage_cpu.cpp - CPU reference implementation for CUDA exercises.
#include "platform/cuda_stage.hpp"

#include <algorithm>

namespace platform {

void vector_add_cpu(const std::vector<float>& a, const std::vector<float>& b, std::vector<float>& out) {
    const std::size_t n = std::min(a.size(), b.size());
    out.resize(n);
    for (std::size_t i = 0; i < n; ++i) {
        out[i] = a[i] + b[i];
    }
}

}  // namespace platform
