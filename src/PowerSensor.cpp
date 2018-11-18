#include "PowerMonitor.h"

float PowerSensorBase::getPower_W() {
    return (float)power * pCoef;
}

float PowerSensorBase::getVoltage_V() {
    return (float)voltage * vCoef;
}

float PowerSensorBase::getCurrent_mA() {
    return ((float)current) * cCoef / 1000.0;
}

float PowerSensorBase::getPowerFactor() {
    long apperantPowermW = voltage * current;
    float powerFactor = 1000.0f * power / apperantPowermW;
    if (powerFactor > 1.0f) {
        powerFactor = 1.0f;
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