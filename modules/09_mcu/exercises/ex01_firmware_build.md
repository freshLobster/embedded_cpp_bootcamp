# ex01_firmware_build – ESP32-C3 firmware skeleton

What you are building: Minimal firmware loop reading sensor stub and blinking LED.
Why it matters: MCU path for autonomy peripherals.

Prerequisites check
- ESP-IDF installed; `idf.py --version`

Files you will touch
- `firmware/main/app.c` (create stub)
- `modules/09_mcu/artifacts/ex01_flash.log`

Steps
1. Create firmware skeleton:
```
mkdir -p firmware/main
cat > firmware/main/app.c <<'EOF'
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
void app_main(void){ while(1){ printf("tick
"); vTaskDelay(pdMS_TO_TICKS(20)); } }
EOF
```
2. Build/flash: `idf.py set-target esp32c3 && idf.py build` then `idf.py -p /dev/ttyUSB0 flash monitor | tee modules/09_mcu/artifacts/ex01_flash.log`
Expected: board prints "tick".

Verification
- Log shows ticks at ~20ms.

Stop here and commit
- Message: "Module09: ESP32 skeleton"

If it fails
- Port wrong: adjust tty path.
