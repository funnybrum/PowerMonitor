#include "PowerMonitor.h"

void PowerSensorBase::begin() {
    loadSettings();
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