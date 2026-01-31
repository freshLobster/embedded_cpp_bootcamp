#pragma once

// Shared stubs for later hardware exercises.
// These are placeholders so the exercise compiles on any host.
struct SensorSample {
    int value;
};

SensorSample read_sensor_fake();
SensorSample read_sensor_hw();

// Runs the deployment command exercise self-check.
// Return 0 on success; non-zero codes map to specific failures.
// The exercise validates command string formatting only.
int exercise();
