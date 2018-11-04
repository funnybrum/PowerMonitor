#include "PowerMonitor.h"

void PowerSensor::begin() {
    Serial.begin(4800);
    while (! Serial) {
        delay(1);
    }
    logger.log("HW Serial started.");
}

void PowerSensor::loop() {
}

PowerSensor powerSensor = PowerSensor();