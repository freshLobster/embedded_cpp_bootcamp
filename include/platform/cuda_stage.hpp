// cuda_stage.hpp - CPU/GPU dual implementation demo.
#pragma once

#ifdef PLATFORM_ENABLE_CUDA
#include <cuda_runtime.h>
#endif

#include <vector>

namespace platform {

    struct CudaBuffer {
        CudaBuffer()                              = default;
        CudaBuffer(const CudaBuffer &)            = delete;
        CudaBuffer &operator=(const CudaBuffer &) = delete;
        CudaBuffer(CudaBuffer &&other) noexcept;
        CudaBuffer &operator=(CudaBuffer &&other) noexcept;
        ~CudaBuffer();

        bool allocate(std::size_t bytes);
        void reset();

        void *data() {
            return device_ptr_;
        }
        const void *data() const {
            return device_ptr_;
        }
        std::size_t size_bytes() const {
            return bytes_;
        }

      private:
        void *device_ptr_{nullptr};
        std::size_t bytes_{0};
    };

    // CPU reference implementation.
    void vector_add_cpu(const std::vector<float> &a, const std::vector<float> &b, std::vector<float> &out);

#ifdef PLATFORM_ENABLE_CUDA
    // GPU implementation. Returns false on CUDA error.
    bool vector_add_cuda(const std::vector<float> &a, const std::vector<float> &b, std::vector<float> &out);
    bool check_cuda_available();
#endif

} // namespace platform
