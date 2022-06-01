#include "PowerMonitor.h"

char buffer[4096];

WebServer::WebServer(Logger* logger, NetworkSettings* networkSettings)
    :WebServerBase(networkSettings, logger) {
}

void WebServer::registerHandlers() {
    server->on("/", std::bind(&WebServer::handle_root, this));
    server->on("/settings", std::bind(&WebServer::handle_settings, this));
    server->on("/get", std::bind(&WebServer::handle_get, this));

    server->on("/on", std::bind(&WebServer::handle_on, this));
    server->on("/off", std::bind(&WebServer::handle_off, this));
    server->on("/blink", std::bind(&WebServer::handle_blink, this));
}

void WebServer::handle_root() {
    server->sendHeader("Location","/settings");
    server->send(303);
}

void WebServer::handle_get() {
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
    wifi.parse_config_params(this);
    telemetryCollector.parse_config_params(this);
    powerSensor.parse_config_params(this);

    char network_settings[strlen_P(NETWORK_CONFIG_PAGE) + 32];
    wifi.get_config_page(network_settings);

    char influxdb_settings[strlen_P(INFLUXDB_CONFIG_PAGE) + 96];
    telemetryCollector.get_config_page(influxdb_settings);

    char power_sensor_settings[strlen_P(POWER_SENSOR_CONFIG_PAGE) + 32];
    powerSensor.get_config_page(power_sensor_settings);

    sprintf_P(
        buffer,
        CONFIG_PAGE,
        MODEL_NAME,
        network_settings,
        influxdb_settings,
        power_sensor_settings);
    server->send(200, "text/html", buffer);
}

void WebServer::handle_on() {
    logger->log("/on");
    server->send(200);
    relay.on();
}

void WebServer::handle_off() {
    logger->log("/off");
    server->send(200);
    relay.off();
}

void WebServer::handle_blink() {
    server->send(200);
    led.blink();
}
