#include "PowerMonitor.h"

void LED::begin() {
    pinMode(LED_PIN, OUTPUT);
    analogWrite(LED_PIN, 1023);
}

void LED::loop() {
    // if ((millis()/1000)%2 == 0) {
    //     analogWrite(LED_PIN, 1023);
    // } else {
    //     analogWrite(LED_PIN, 0);
    // }
}

void LED::blink() {
}

LED led = LED();