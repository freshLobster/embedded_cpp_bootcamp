#pragma once

// Simple sample struct used by stubbed sensor functions.
struct SensorSample {
    int value;
};

SensorSample read_sensor_fake();
SensorSample read_sensor_hw();

// Reference solution entry point. Return 0 on success.
int exercise();
