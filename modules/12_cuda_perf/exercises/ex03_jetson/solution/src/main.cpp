#include <cassert>
#include "exercise.hpp"

int exercise_cpu(){ return 42; }
#ifdef ENABLE_CUDA
int exercise_gpu(){ return 42; }
#endif

int exercise(){
#ifdef ENABLE_CUDA
    return exercise_gpu();
#else
    return exercise_cpu();
#endif
}

int main(){
    assert(exercise()==42);
    return 0;
}
