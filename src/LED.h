#ifndef _LED_H_
#define _LED_H_

#include "PowerMonitor.h"

class LED {
    public:
        void begin();
        void loop();
        void blink();
        void blink2();
    private:
        unsigned long _lastBlink = 0;
        unsigned long _lastUpdate = 0;
};

extern LED led;

#endif
