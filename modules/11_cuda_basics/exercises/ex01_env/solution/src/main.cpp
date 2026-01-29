#include <cassert>

constexpr bool cuda_available() {
#if defined(__CUDACC__)
    return true;
#else
    return false;
#endif
}

int exercise() {
    constexpr bool expected = cuda_available();
    if (cuda_available() != expected) {
        return 1;
    }
    return 0;
}

int main(){
    assert(exercise()==0);
    return 0;
}
