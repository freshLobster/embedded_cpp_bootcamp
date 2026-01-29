# ex03_uart_bridge – Host UART bridge script

What you are building: Python script to log UART packets for 5 minutes without drops.
Why it matters: Host integration for MCU telemetry.

Prerequisites check
- `python3 -c "import serial"` (install `pip install pyserial` if missing)

Files you will touch
- `tools/uart_bridge.py` (create)
- `modules/09_mcu/artifacts/ex03_uart.log`

Steps
1. Create script:
```
mkdir -p tools
cat > tools/uart_bridge.py <<'EOF'
import serial, time
ser=serial.Serial('/dev/ttyUSB0',115200,timeout=1)
end=time.time()+300
count=0
with open('modules/09_mcu/artifacts/ex03_uart.log','w') as f:
    while time.time()<end:
        line=ser.readline().decode(errors='ignore')
        if line:
            count+=1
            f.write(line)
print('lines',count)
EOF
```
2. Run while firmware emits data: `python3 tools/uart_bridge.py`
Expected: log file filled, final line count printed.

Verification
- Log present; >9000 lines (approx 30 lines/s * 300s) if steady.

Stop here and commit
- Message: "Module09: UART bridge"

If it fails
- Permission denied on tty: add user to dialout or use sudo.
