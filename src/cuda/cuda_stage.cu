#include "platform/cuda_stage.hpp"

#include <cuda_runtime.h>

#include <iostream>

#include "platform/logging.hpp"

namespace platform {

namespace {
__global__ void vec_add_kernel(const float* a, const float* b, float* out, int n) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < n) {
        out[idx] = a[idx] + b[idx];
    }
}

bool check_cuda(const char* where, cudaError_t err) {
    if (err != cudaSuccess) {
        LOG_ERROR(std::string("CUDA error at ") + where + ": " + cudaGetErrorString(err));
        return false;
    }
    return true;
}
}  // namespace

CudaBuffer::CudaBuffer(CudaBuffer&& other) noexcept {
    device_ptr_ = other.device_ptr_;
    bytes_ = other.bytes_;
    other.device_ptr_ = nullptr;
    other.bytes_ = 0;
}

CudaBuffer& CudaBuffer::operator=(CudaBuffer&& other) noexcept {
    if (this != &other) {
        reset();
        device_ptr_ = other.device_ptr_;
        bytes_ = other.bytes_;
        other.device_ptr_ = nullptr;
        other.bytes_ = 0;
    }
    return *this;
}

CudaBuffer::~CudaBuffer() { reset(); }

bool CudaBuffer::allocate(std::size_t bytes) {
    reset();
    if (bytes == 0) return true;
    bytes_ = bytes;
    if (!check_cuda("cudaMalloc", cudaMalloc(&device_ptr_, bytes_))) {
        device_ptr_ = nullptr;
        bytes_ = 0;
        return false;
    }
    return true;
}

void CudaBuffer::reset() {
    if (device_ptr_) {
        cudaFree(device_ptr_);
        device_ptr_ = nullptr;
        bytes_ = 0;
    }
}

bool check_cuda_available() {
    int count = 0;
    if (cudaGetDeviceCount(&count) != cudaSuccess) {
        return false;
    }
    return count > 0;
}

bool vector_add_cuda(const std::vector<float>& a, const std::vector<float>& b, std::vector<float>& out) {
#ifndef PLATFORM_ENABLE_CUDA
    (void)a;
    (void)b;
    (void)out;
    return false;
#else
    if (!check_cuda_available()) {
        LOG_WARN("No CUDA device available, falling back to CPU.");
        vector_add_cpu(a, b, out);
        return false;
    }

    const std::size_t n = std::min(a.size(), b.size());
    out.resize(n);
    CudaBuffer d_a, d_b, d_out;
    if (!d_a.allocate(n * sizeof(float)) || !d_b.allocate(n * sizeof(float)) || !d_out.allocate(n * sizeof(float))) {
        return false;
    }

    if (!check_cuda("copy a", cudaMemcpy(d_a.data(), a.data(), n * sizeof(float), cudaMemcpyHostToDevice))) return false;
    if (!check_cuda("copy b", cudaMemcpy(d_b.data(), b.data(), n * sizeof(float), cudaMemcpyHostToDevice))) return false;

    const int threads = 256;
    const int blocks = static_cast<int>((n + threads - 1) / threads);
    vec_add_kernel<<<blocks, threads>>>(static_cast<float*>(d_a.data()), static_cast<float*>(d_b.data()),
                                        static_cast<float*>(d_out.data()), static_cast<int>(n));
    if (!check_cuda("kernel", cudaGetLastError())) return false;
    if (!check_cuda("sync", cudaDeviceSynchronize())) return false;

    if (!check_cuda("copy out", cudaMemcpy(out.data(), d_out.data(), n * sizeof(float), cudaMemcpyDeviceToHost)))
        return false;
    return true;
#endif
}

}  // namespace platform
