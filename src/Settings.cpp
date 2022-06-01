#include "Settings.h"
#include "PowerMonitor.h"

Settings::Settings()
    :SettingsBase(&logger) {
}

void Settings::initializeSettings() {
    strcpy(settingsData.network.hostname, HOSTNAME);
    settingsData.sensor.currentCoef = 1.0f;
    settingsData.sensor.powerCoef = 1.0f;
    settingsData.sensor.voltageCoef = 1.0f;
}

SettingsData* Settings::getSettings() {
    return &settingsData;
}

Empty* Settings::getRTCSettings() {
    return NULL;
}
