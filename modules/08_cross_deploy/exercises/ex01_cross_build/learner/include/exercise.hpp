#pragma once

// This header is shared by the exercise and keeps simple interfaces visible.
// SensorSample exists for later hardware-related modules; keep it unchanged.
struct SensorSample {
    int value;
};

// Fake and hardware sensor stubs (used in later exercises).
// These functions let you compile on Windows/WSL without real hardware.
SensorSample read_sensor_fake();
SensorSample read_sensor_hw();

// Runs the cross-build probe exercise self-check.
// Return 0 on success; non-zero codes map to specific failures.
// The check is string-based to avoid platform-specific headers.
int exercise();
