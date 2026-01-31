#pragma once

// Shared stubs for later MCU exercises.
// These are placeholders so the exercise compiles on desktop.
struct SensorSample {
    int value;
};

SensorSample read_sensor_fake();
SensorSample read_sensor_hw();

// Runs the MCU race exercise self-check.
// Return 0 on success; non-zero codes map to specific failures.
// The check simulates ISR/task contention via shared counters.
int exercise();
