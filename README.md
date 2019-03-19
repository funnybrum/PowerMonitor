# Power monitor
## Summary

Custom firmware for the following smart plugs:
 * Sonoff Pow R2 (with CSE7789B)
 * Koogeek P1EU (same as BlitzWolf BW-SHP2)

## Compiling

The project requires additional lib that should be retrieved from another github repo. Execute the following commands to get this done (from the root project folder).

```
cd lib
git clone https://github.com/funnybrum/esp8266-base.git
```

After that choose the proper hardware to be flashed - KOOGEEK_P1EU or SONOFF_POW_R2. Apply changes for the following two files:
 * PowerMonitor.h - define the hardware.
 * platformio.ini - choose the proper plaform.

The Sonoff Pow R2 uses ESP8266 with 4MB flash and the Koogeek P1EU uses ESP8258 with 1MB flash.

Initial flashing should be done with USB to 3.3V serial adapter. Check the following pages for details for flashing the devices:
 * [Sonoff POW R2](https://github.com/xoseperez/espurna/wiki/Hardware-Itead-Sonoff-POW-R2)
 * [Koogeek P1EU](https://github.com/xoseperez/espurna/wiki/Hardware-BLITZWOLF-BW-SHP2)
 * [Koogeek P1EU v2.3](https://github.com/arendst/Sonoff-Tasmota/issues/4303)


## Over-the-air programming

The firmware supports OTA update. Below curl command executed from the project root will perform the update:
> curl -F "image=@.pioenvs/.../firmware.bin" http://power-monitor/update

## Network configuring

After the firmware is successfully flashed and the microcontroler restarted it will enter in access point mode and open a network named power-monitor. Join that network, set an IP address of 192.168.0.2 and network mask 255.255.255.0 to the computer. Go to http://192.168.0.1/ and you'll see the settings page.

Configure the desired network preferences. If the controller fail to join the specified WiFi network - it will enter AP mode again and can be accessed for reconfiguration as noted above.

## InfluxDB integration

On the settings page there is a section with InfluxDB parameters. Most of them are self-explaining. The DB must not be password protected. After proper configuration the controller will push the telemetry data to the InfluxDB on regular intervals (specified by push interval). While data is being collected there is no need for the WiFi to be working and it will be turned off. As result - the controller will power on the WiFi network just for a short period (~5 seconds) on each push interval. This will however render the /on and the /off HTTP endpoints useless. If these are needed - feel free to fork and modify the source code in order to keep the WiFi working while the InfluxDB integration is enabled.

With the WiFi turned off you'll loose access to the microcontroller. If the controller needs to be reconfigured - restartign it will help doing that. Until the first push interval has come - the WiFi will stay in on state and allow reconfiguration of the power monitor settings.

As guide for configuring the push and collect intervals - I use 30 seconds for collection interval and 1800 seconds for push interval. If the internal buffer used for telemetry data gets full before the next push cycle - the microcontroller will power on the WiFi and flush the buffer to the configured InfluxDB database.

## Debugging

There are several log messages produced by the firmware. In order to access them - go to the http://ip_addr/logs and you'll see the last 1024 bytes of log messages.

## HTTP API endpoints
Once flashed the microcontroller will start a web server with the following endpoints 
 * http://{ip_addr}/ -> redirect to http://{ip_addr}/settings
 * http://{ip_addr}/settings -> Configuration page.
 * http://{ip_addr}/get -> A GET request will return JSON document with power, current, voltage and power factor.
 * http://{ip_addr}/on -> Turn on the power to the connected device.
 * http://{ip_addr}/off -> Turn of the power to the connected device.
 * http://{ip_addr}/reboot -> Reboots the microcontroller.
 * http://{ip_addr}/reset -> Erase the settings and return the microcontroller to the initial state.
 * http://{ip_addr}/logs -> Return the logs from the microcontroller.
 * http://{ip_addr}/update -> ESP8266 OTA firmware update endpoint.  
