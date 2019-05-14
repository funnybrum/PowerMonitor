#include "PowerMonitor.h"

void PowerSensorBase::begin() {
    loadSettings();
    memset(avg_power_value, 0, sizeof(avg_power_value));
    memset(avg_power_readings, 0, sizeof(avg_power_readings));
    avg_power_index = 0;
}

void PowerSensorBase::loop() {
    uint8_t index = (millis() % 60000) / 1000;
    if (avg_power_index != index) {
        avg_power_readings[index] = 0;
        avg_power_value[index] = 0;
        avg_power_index = index; 
    }

    avg_power_readings[avg_power_index]++;
    avg_power_value[avg_power_index] += getPower_W();
}

void PowerSensorBase::loadSettings() {
    cCoef = settingsData.sensor.currentCoef;
    pCoef = settingsData.sensor.powerCoef;
    vCoef = settingsData.sensor.voltageCoef;
}

float PowerSensorBase::getPower_W() {
    return (float)power * pCoef;
}

float PowerSensorBase::getVoltage_V() {
    return (float)voltage * vCoef;
}

float PowerSensorBase::getCurrent_A() {
    return ((float)current) * cCoef / 1000.0;
}

float PowerSensorBase::getAveragePower60s() {
    float sum = 0.0f;
    int count = 0;
    for (int i = 0; i < 60; i++) {
        if (avg_power_readings[i] > 0) {
            float avg = ((float)avg_power_value[i]) / avg_power_readings[i];
            sum += avg;
            count++;
        }
    }

    if (count == 0) {
        return -1.0f;
    }

    return sum / count;
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

void PowerSensorBase::setCurrentCorrection(float coef) {
    cCoef = coef;
}

void PowerSensorBase::setVoltageCorrection(float coef) {
    vCoef = coef;
}

void PowerSensorBase::setPowerCorrection(float coef) {
    pCoef = coef;
}