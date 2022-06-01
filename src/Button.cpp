#include "PowerMonitor.h"

unsigned short Button::_clickCount = 0;
unsigned long Button::_lastClick = 0;

void Button::begin() {
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), onClick, FALLING);
}

void Button::loop() {
    if (_clickCount > 0 && millis() - _lastClick > 500) {
        if (_clickCount == 1) {
            led.blink();
        } else {
            led.blink2();
        }
        // Custom actions can be taken based on the number of clicks. For now - just one action.
        wifi.connect();
        _clickCount = 0;
    }
}

void ICACHE_RAM_ATTR Button::onClick() {
    _clickCount++;
    _lastClick = millis();
}
