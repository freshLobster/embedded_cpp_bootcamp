#pragma once

// Simple sensor sample used by stubbed sensors.
struct SensorSample {
    int value;
};

// Fake and hardware sensor stubs (used to validate cross-build paths).
SensorSample read_sensor_fake();
SensorSample read_sensor_hw();

// Reference solution entry point. Return 0 on success.
int exercise();
