#include "PowerMonitor.h"

Logger logger = Logger(false);
Settings settings = Settings();
WiFiManager wifi = WiFiManager(&logger, &settings.getSettings()->network);
DataCollector telemetryCollector = DataCollector();
WebServer webServer = WebServer(&logger, &settings.getSettings()->network);

PowerSensor powerSensor = PowerSensor();
Relay relay = Relay();
LED led = LED();
Button button = Button();

void setup()
{
    logger.begin();
    settings.begin();
    wifi.begin();
    telemetryCollector.begin();
    webServer.begin();

    powerSensor.begin();
    led.begin();
    relay.begin();
    button.begin();

    wifi.connect();
}

void loop() {
    settings.loop();
    wifi.loop();
    telemetryCollector.loop();
    webServer.loop();

    powerSensor.loop();
    led.loop();
    relay.loop();
    button.loop();

    delay(100);
}
