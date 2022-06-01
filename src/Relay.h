#ifndef _RELAY_H_
#define _RELAY_H_

#include "PowerMonitor.h"

class Relay {
    public:
        void begin();
        void loop();
        void off();
        void on();
};

#endif
