#pragma once

// Shared stubs for later MCU exercises.
// These stubs allow desktop testing without hardware.
struct SensorSample {
    int value;
};

SensorSample read_sensor_fake();
SensorSample read_sensor_hw();

// Runs the UART bridge checksum exercise self-check.
// Return 0 on success; non-zero codes map to specific failures.
// The checksum is intentionally lightweight for MCU use.
int exercise();
