#pragma once

// Shared stubs for later MCU exercises.
// These make the exercise compile on desktop targets.
struct SensorSample {
    int value;
};

SensorSample read_sensor_fake();
SensorSample read_sensor_hw();

// Runs the UART framing exercise self-check.
// Return 0 on success; non-zero codes map to specific failures.
// The payload format is intentionally tiny and fixed-width.
int exercise();
