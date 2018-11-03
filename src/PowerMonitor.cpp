#include "PowerMonitor.h"

void setup()
{ 
    Serial.begin(115200);
    while (! Serial) {
        delay(1);
    }
    settings.begin();

    ScanAndConnect();

    webServer.begin();
    systemCheck.begin();
    led.begin();
    relay.begin();
}

void loop() {
    webServer.loop();
    settings.loop();
    systemCheck.loop();
    led.loop();
    relay.loop();
    delay(100);
}
