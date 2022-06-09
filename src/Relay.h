#ifndef _RELAY_H_
#define _RELAY_H_

#include "PowerMonitor.h"

class Relay {
    public:
        void begin();
        void loop();
        void off();
        // durationSeconds = 0 - indefinite, != 0 - keep the relay ON only for the specified seconds
        void on(uint16_t durationSeconds);
    private:
        uint32_t turnOffAt = 0;
};

#endif
