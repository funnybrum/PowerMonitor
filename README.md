# Power monitor
## Summary

Custom firmware for the following smart plugs:
 * Sonoff Pow R2 with CSE7789B
 * Koogeek P1EU

## Compiling

The project requires additional lib that can be retrieved from another github repo:

```
cd lib
git clone git@github.com:funnybrum/esp8266-base.git
```

After that choose the proper hardware to be flashed - KOOGEEK_P1EU or SONOFF_POW_R2. Apply changes for the following two files:
 * PowerMonitor.h - define the hardware.
 * platformio.ini - choose the proper plaform.

## Over-the-air programming

The firmware supports OTA update. Below curl command executed from the project root will perform the update:
> curl -F "image=@.pioenvs/.../firmware.bin" http://power-monitor/update
