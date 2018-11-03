#include "PowerMonitor.h"

void Relay::begin() {
    pinMode(RELAY_PIN, OUTPUT);
    off();
}

void Relay::loop() {
}

void Relay::on() {
    digitalWrite(RELAY_PIN, HIGH);
}

void Relay::off() {
    digitalWrite(RELAY_PIN, LOW);
}

Relay relay = Relay();