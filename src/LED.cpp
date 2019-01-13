#include "PowerMonitor.h"

void LED::begin() {
    pinMode(LED_PIN, OUTPUT);
    analogWrite(LED_PIN, 1023);

#ifdef LED2_PIN
    pinMode(LED2_PIN, OUTPUT);
    analogWrite(LED2_PIN, 1023);
#endif
}

void LED::loop() {
    if (wifi.isInAPMode()) {
        analogWrite(LED_PIN, 0);
    } else {
        analogWrite(LED_PIN, 1023);
    }
}

void LED::blink() {
    analogWrite(LED_PIN, 0);
    delay(200);
    analogWrite(LED_PIN, 1023);
}

void LED::blink2() {
#ifdef LED2_PIN
    analogWrite(LED2_PIN, 0);
    delay(200);
    analogWrite(LED2_PIN, 1023);
#endif
}

LED led = LED();