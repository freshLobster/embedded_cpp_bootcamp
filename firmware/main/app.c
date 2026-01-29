// app.c - minimal MCU firmware entry stub (ESP-IDF style).
#include <stdint.h>

void app_main(void) {
    // TODO: replace with sensor read + actuator drive in Module 09.
    volatile uint32_t heartbeat = 0;
    heartbeat++;
}
