#ifndef _WEBSERVER_H_
#define _WEBSERVER_H_

#include "PowerMonitor.h"
#include "WebServerBase.h"
#include "WebPages.h"

class WebServer: public WebServerBase {
    public:
        WebServer(NetworkSettings* networkSettings, Logger* logger, SystemCheck* systemCheck);
        void registerHandlers();
        void handle_root();
        void handle_get();
        void handle_on();
        void handle_off();
        void handle_settings();
        void handle_reset();
};

#endif
