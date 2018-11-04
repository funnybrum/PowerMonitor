#ifndef _POWERSENSOR_H_
#define _POWERSENSOR_H_

#include "PowerMonitor.h"

/*
 * Driver and user-friendly interface for the CSE7789B sensor. Both the CSE7766
 * and the CSE7789B seems to have identical serial communicaton protocol.
 * 
 * The Sonoff Pow R2 has the CS7789B TI (the UART TX) pin connected to the
 * ESP8266EX U0RXD (the hardware UART RX) pin. Because of that the
 * implementation is based on the hardware serial support.
 * 
 * Based on the CSE7766.pdf that can be found in the docs folder.
 */
class PowerSensor {
    public:
        void begin();
        void loop();
        float getPower();
        float getVoltage();
        float getCurrent();

    private:
        char data[24];
};

extern PowerSensor powerSensor;

#endif
