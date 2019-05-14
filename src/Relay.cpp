#include "PowerMonitor.h"

void Relay::begin() {
    pinMode(RELAY_PIN, OUTPUT);
    DEFAULT_RELAY_STATE();
}

void Relay::loop() {
}

void Relay::on() {
    relayIsOn = true;
    digitalWrite(RELAY_PIN, HIGH);
}

void Relay::off() {
    relayIsOn = false;
    digitalWrite(RELAY_PIN, LOW);
}

bool Relay::isOn() {
    return relayIsOn;
}

Relay relay = Relay();