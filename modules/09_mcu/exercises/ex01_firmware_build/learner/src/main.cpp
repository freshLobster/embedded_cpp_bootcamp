#include <cassert>
#include "exercise.hpp"

SensorSample read_sensor_fake(){ return {1}; }
SensorSample read_sensor_hw(){ return {2}; }

int exercise(){
    #error TODO_implement_exercise
}

int main(){
    assert(exercise()==42);
    return 0;
}
