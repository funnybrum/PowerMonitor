#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "PowerMonitor.h"

class Button {
    public:
        void begin();
        void loop();
        static unsigned long _lastClick;
        static unsigned short _clickCount;
    private:
        static void onClick();
};

extern Button button;

#endif
