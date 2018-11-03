# Power monitor
## Summary

Custom firmware for the Sonoff Pow R2 with CSE7789B.

## Over-the-air programming

The firmware supports OTA update. Below curl command executed from the project root will perform the update:
> curl -F "image=@.pioenvs/d1_mini/firmware.bin" br-aq-monitor1/update
