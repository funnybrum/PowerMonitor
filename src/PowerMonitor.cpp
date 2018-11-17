#include "PowerMonitor.h"

void setup()
{
    logger.begin();

    settings.begin();

    ScanAndConnect();

    powerSensor.begin();
    led.begin();
    relay.begin();
    webServer.begin();
    systemCheck.begin();
}

void loop() {
    webServer.loop();
    settings.loop();
    systemCheck.loop();
    led.loop();
    relay.loop();
    logger.loop();
    powerSensor.loop();
    delay(1000);
}
