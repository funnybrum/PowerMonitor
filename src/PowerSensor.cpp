#include "PowerMonitor.h"

void PowerSensorBase::begin() {
}

float PowerSensorBase::getPower_W() {
    return (float)power * settings.getSettings()->sensor.powerCoef;
}

float PowerSensorBase::getVoltage_V() {
    return (float)voltage * settings.getSettings()->sensor.voltageCoef;
}

float PowerSensorBase::getCurrent_A() {
    return ((float)current) * settings.getSettings()->sensor.currentCoef / 1000.0;
}

float PowerSensorBase::getPowerFactor() {
    float apperantPower = getVoltage_V() * getCurrent_A();
    float powerFactor = getPower_W() / apperantPower;
    if (powerFactor > 1.0f) {
        powerFactor = 1.0f;
    }

    if (isnan(powerFactor)) {
        return 0.0f;
    }

    return powerFactor;
}

void PowerSensorBase::get_config_page(char* buffer) {
    sprintf_P(
        buffer,
        POWER_SENSOR_CONFIG_PAGE,
        settings.getSettings()->sensor.powerCoef,
        settings.getSettings()->sensor.voltageCoef,
        settings.getSettings()->sensor.currentCoef);
}

void PowerSensorBase::parse_config_params(WebServerBase* webServer) {
    webServer->process_setting("pcoef", settings.getSettings()->sensor.powerCoef);
    webServer->process_setting("vcoef", settings.getSettings()->sensor.voltageCoef);
    webServer->process_setting("ccoef", settings.getSettings()->sensor.currentCoef);
}