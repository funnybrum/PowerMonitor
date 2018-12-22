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
    collector->append("free_heap", ESP.getFreeHeap());
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

    if (settingsData.influxDB.enable) {
        systemCheck.stop();
        telemetryCollector.start();
    } else {
        telemetryCollector.stop();
        systemCheck.start();
    }

    delay(100);
}
