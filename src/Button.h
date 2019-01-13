#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "PowerMonitor.h"

class Button {
    public:
        void begin();
        void loop();
    private:
        static void onClick();
        static unsigned long _lastClick;
        static unsigned short _clickCount;
};

extern Button button;

#endif
