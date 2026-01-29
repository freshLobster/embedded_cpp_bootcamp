# SBC Track (Raspberry Pi / Orange Pi)

## BOM (generic, swap equivalents freely)
- SBC: Raspberry Pi 4/5 or Orange Pi 5
- IMU (I2C): MPU-6050 or BMI270
- Barometer (I2C): BMP280
- SPI: MAX31855 thermocouple (optional)
- Actuator: SG90 servo (PWM) or LED + resistor (GPIO)
- Level shifter + 3.3V regulators as required
- Misc: breadboard, jumpers, USB-UART cable (FTDI)

## Pinout (Raspberry Pi 40-pin header)
```
3V3 --+-- VCC sensors
GND --+-- sensor ground & servo ground
SCL ---- GPIO3 (pin 5)
SDA ---- GPIO2 (pin 3)
SPI SCK - GPIO11 (pin 23)
SPI MOSI- GPIO10 (pin 19)
SPI MISO- GPIO9  (pin 21)
Servo PWM - GPIO18 (pin 12)
```

Orange Pi: map to I2C0/I2C1 + SPI1 + PWM0 per board manual.

## ASCII wiring (MPU6050 + servo)
```
Pi 3V3 ---- VCC (MPU6050)
Pi GND ---- GND (MPU6050 & Servo GND)
Pi SDA ---- SDA (MPU6050)
Pi SCL ---- SCL (MPU6050)
Pi GPIO18 -|---- Servo signal
Ext 5V ---- Servo V+
```

## Bus configuration
- I2C speed: 400 kHz
- SPI speed: 1-4 MHz for MAX31855
- Servo PWM: 50 Hz, 1-2 ms pulse

## Bring-up checklist
- `i2cdetect -y 1` shows sensor address (0x68 for MPU6050).
- `ls /dev/spidev0.0` exists.
- Servo moves with `pigpio`/`raspi-gpio`.
- NTP synced (`timedatectl status`) to reduce timestamp drift.

## systemd deployment
- Copy binary to `/usr/local/bin/platform_core_app`.
- Create `/etc/systemd/system/platform_core.service`:
```
[Unit]
Description=Platform Core Training
After=network.target

[Service]
ExecStart=/usr/local/bin/platform_core_app
Restart=on-failure
User=pi
Environment=PLATFORM_LOG=info

[Install]
WantedBy=multi-user.target
```
- Enable: `sudo systemctl enable --now platform_core`.

## Remote debugging
- Start gdbserver: `gdbserver :2345 /usr/local/bin/platform_core_app`
- On host: `gdb build/aarch64/platform_core_app -ex "target remote <pi>:2345"`
- Validate with `info threads`, `bt`.

## Validation steps
- Sensor sanity: stream 100 samples, ensure variance <0.1 for stationary device.
- Latency: log publish-to-actuator latency; expect p50 <2 ms, p95 <5 ms at 20 Hz.
- Fault injection: unplug I2C mid-run; verify graceful error, no crash, actuator stops.
