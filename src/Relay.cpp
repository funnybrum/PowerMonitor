#include "PowerMonitor.h"

void Relay::begin() {
    pinMode(RELAY_PIN, OUTPUT);
    DEFAULT_RELAY_STATE(0);
}

void Relay::loop() {
    if (turnOffAt) {
        if (millis() > turnOffAt) {
            off();
            turnOffAt = 0;
        }
    }
}

void Relay::on(uint16_t durationSeconds) {
    if (durationSeconds != 0) {
        turnOffAt = millis() + durationSeconds * 1000;
    } else {
        durationSeconds = 0;
    }
    digitalWrite(RELAY_PIN, HIGH);
}

void Relay::off() {
    digitalWrite(RELAY_PIN, LOW);
}
