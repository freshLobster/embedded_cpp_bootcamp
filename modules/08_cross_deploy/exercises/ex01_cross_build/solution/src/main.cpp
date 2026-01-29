#include <cassert>
#include "exercise.hpp"

SensorSample read_sensor_fake(){ return {1}; }
SensorSample read_sensor_hw(){ return {2}; }

int exercise(){
#ifdef ENABLE_HARDWARE
    SensorSample s = read_sensor_hw();
#else
    SensorSample s = read_sensor_fake();
#endif
    (void)s;
    return 42;
}

int main(){
    assert(exercise()==42);
    return 0;
}
