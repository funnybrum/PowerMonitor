#include "PowerMonitor.h"

char buffer[4096];

WebServer::WebServer(NetworkSettings* networkSettings, Logger* logger, SystemCheck* systemCheck)
    :WebServerBase(networkSettings, logger, systemCheck) {
}

void WebServer::registerHandlers() {
    server->on("/", std::bind(&WebServer::handle_root, this));
    server->on("/get", std::bind(&WebServer::handle_get, this));
    server->on("/on", std::bind(&WebServer::handle_on, this));
    server->on("/off", std::bind(&WebServer::handle_off, this));
    server->on("/settings", std::bind(&WebServer::handle_settings, this));
    server->on("/reset", std::bind(&WebServer::handle_reset, this));
    server->on("/blink", std::bind(&WebServer::handle_blink, this));
}

void WebServer::handle_root() {
    systemCheck->registerWebCall();
    server->sendHeader("Location","/settings");
    server->send(303);
}

void WebServer::handle_get() {
    systemCheck->registerWebCall();

    char resp[strlen_P(GET_JSON) + 32];
    sprintf_P(resp,
              GET_JSON,
              powerSensor.getVoltage_V(),
              powerSensor.getCurrent_A(),
              powerSensor.getPower_W(),
              powerSensor.getPowerFactor());
    server->send(200, "application/json", resp);
}

void WebServer::handle_settings() {
    systemCheck->registerWebCall();

    bool save = false;

    wifi.parse_config_params(this, save);
    telemetryCollector.parse_config_params(this, save);

    process_setting("pcoef", settingsData.sensor.powerCoef, save);
    process_setting("vcoef", settingsData.sensor.voltageCoef, save);
    process_setting("ccoef", settingsData.sensor.currentCoef, save);

    if (save) {
        logger->log("Settings updated.");
        settings.save();
        powerSensor.loadSettings();
    }

    char network_settings[strlen_P(NETWORK_CONFIG_PAGE) + 32];
    wifi.get_config_page(network_settings);

    char influxdb_settings[strlen_P(INFLUXDB_CONFIG_PAGE) + 96];
    telemetryCollector.get_config_page(influxdb_settings);

    sprintf_P(
        buffer,
        CONFIG_PAGE,
        MODEL_NAME,
        network_settings,
        influxdb_settings,
        settingsData.sensor.powerCoef,
        settingsData.sensor.voltageCoef,
        settingsData.sensor.currentCoef);
    server->send(200, "text/html", buffer);
}

void WebServer::handle_reset() {
    logger->log("/hard_reset");
    systemCheck->registerWebCall();
    settings.erase();
    server->send(200, "text/plain", "Settings erased.");
}

void WebServer::handle_on() {
    logger->log("/on");
    systemCheck->registerWebCall();
    server->send(200);
    relay.on();
}

void WebServer::handle_off() {
    logger->log("/off");
    systemCheck->registerWebCall();
    server->send(200);
    relay.off();
}

void WebServer::handle_blink() {
    systemCheck->registerWebCall();
    server->send(200);
    led.blink();
}
