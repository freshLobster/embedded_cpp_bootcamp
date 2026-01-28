# MCU Track (ESP32-C3)

## Firmware goals
- Read I2C sensor (e.g., MPU6050) or simulated sine wave.
- Drive LED or servo (PWM) based on control command.
- UART link to host: stream sensor + actuator status at 50 Hz.
- Cooperative scheduler or FreeRTOS tasks; demonstrate ISR vs task race.

## Toolchain
- Install: `pip install esptool` and ESP-IDF (v5.x).
- Build: `idf.py set-target esp32c3 && idf.py build`.
- Flash: `idf.py -p /dev/ttyUSB0 flash monitor`.

## Wiring (ESP32-C3 DevKitM-1)
```
3V3 ---- VCC sensor
GND ---- GND
GPIO6 -- SDA
GPIO7 -- SCL
GPIO4 -- LED/servo signal (PWM)
```

## OpenOCD + GDB
- Start: `openocd -f board/esp32c3-builtin.cfg`
- Debug: `xtensa-esp32s3-elf-gdb build/firmware.elf -ex "target remote :3333"`
- Inspect: `monitor reset halt`, `info reg`, `x/16wx 0x3fc8xxxx`.

## Validation
- Timing: measure loop jitter with GPIO toggle + logic analyzer; target <200 µs.
- Race lab: intentionally update shared struct in ISR and task without lock; observe via `esp_system_dump` or watchpoints. Fix with atomic/critical section.
- UART contract: host script checks 50 Hz messages, CRC optional.

## Deliverables
- Minimal firmware template with TODOs (see `firmware/` TODO when you build it).
- Bring-up log: flash success, sensor address, first sample, actuator response.
