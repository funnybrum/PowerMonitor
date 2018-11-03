#include "PowerMonitor.h"

void LED::begin() {
    pinMode(BLUE_LED_PIN, OUTPUT);
    analogWrite(BLUE_LED_PIN, 1023);
}

void LED::loop() {
    if ((millis()/1000)%2 == 0) {
        analogWrite(BLUE_LED_PIN, 1023);
    } else {
        analogWrite(BLUE_LED_PIN, 0);
    }

}

void LED::blink() {
}

LED led = LED();