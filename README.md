# Power monitor
## Summary

Custom firmware for the following smart plugs:
 * Sonoff Pow R2 with CSE7789B
 * Koogeek P1EU

## Compiling
Choose the proper hardware to be flashed - KOOGEEK_P1EU or SONOFF_POW_R2. Apply changes for the following two files:
 * PowerMonitor.h - define the hardware.
 * platformio.ini - choose the proper plaform.

## Over-the-air programming

The firmware supports OTA update. Below curl command executed from the project root will perform the update:
> curl -F "image=@.pioenvs/.../firmware.bin" http://power-monitor/update
