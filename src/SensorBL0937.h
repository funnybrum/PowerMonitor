#ifndef _POWERSENSOR_H_
#define _POWERSENSOR_H_

#include "PowerMonitor.h"
#include "HLW8012.h"

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
        float getPower_W();
        float getVoltage_V();
        float getCurrent_mA();
        float getPowerFactor();
    private:
        long voltage;
        long current;
        long power;
        unsigned long lastSwitch;

        static HLW8012 bl0937;
        static void cfInterrupt();
        static void cf1Interrupt();
};

extern PowerSensor powerSensor;

#endif
