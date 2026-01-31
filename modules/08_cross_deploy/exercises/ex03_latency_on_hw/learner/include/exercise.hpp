#pragma once

// Shared stubs for later hardware exercises.
// These definitions keep the exercise buildable without hardware.
struct SensorSample {
    int value;
};

SensorSample read_sensor_fake();
SensorSample read_sensor_hw();

// Runs the latency jitter exercise self-check.
// Return 0 on success; non-zero codes map to specific failures.
// The computation is purely numeric so it works on all platforms.
int exercise();
