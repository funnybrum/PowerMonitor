#include "PowerMonitor.h"


void initSettings() {
    strcpy(settingsData.network.hostname, HOSTNAME);
    settingsData.sensor.currentCoef = 1.0f;
    settingsData.sensor.powerCoef = 1.0f;
    settingsData.sensor.voltageCoef = 1.0f;
}

void collectData(InfluxDBCollector* collector) {
    collector->append("power", powerSensor.getPower_W(), 1);
    collector->append("current", powerSensor.getCurrent_A(), 2);
    collector->append("voltage", powerSensor.getVoltage_V(), 1);
    collector->append("power_factor", powerSensor.getPowerFactor(), 2);
    collector->append("state", relay.isOn()?1:0);
}

Logger logger = Logger(false);
SettingsData settingsData = SettingsData();
Settings settings = Settings(&logger, (void*)(&settingsData), sizeof(SettingsData), initSettings);
SystemCheck systemCheck = SystemCheck(&logger);
WiFiManager wifi = WiFiManager(&logger, &settingsData.network);
InfluxDBCollector telemetryCollector = InfluxDBCollector(
    &logger, &wifi, &settingsData.influxDB, &settingsData.network, collectData);

WebServer webServer = WebServer(&settingsData.network, &logger, &systemCheck);

void setup()
{
    logger.begin();
    settings.begin();
    systemCheck.begin();
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
    logger.loop();
    settings.loop();
    systemCheck.loop();
    wifi.loop();
    telemetryCollector.loop();
    webServer.loop();

    powerSensor.loop();
    led.loop();
    relay.loop();
    button.loop();

    if (settingsData.influxDB.enable) {
        systemCheck.stop();
        telemetryCollector.start();
    } else {
        telemetryCollector.stop();
        systemCheck.start();
    }

    if (telemetryCollector.getTimestamp() > 1556169000) {
        uint32_t secondsAfterMidnight = telemetryCollector.getTimestamp() % (60 * 60 * 24);
        uint16_t hour = secondsAfterMidnight / 3600;
        // Do the check every 15 minutes.
        if (secondsAfterMidnight % 900 < 10) {
            // GMT + 3, so the below one is ON from 9:00 to 16:00
            if (hour >= 5 && hour <= 15) {
                if (relay.isOn() == false) {
                    relay.on();
                }
            } else {
                if (relay.isOn()) {
                    relay.off();
                }
            }
        }
    }

    delay(100);
}
