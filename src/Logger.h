#ifndef _LOGGER_H_
#define _LOGGER_H_

#include "PowerMonitor.h"

// Single log entry.
struct LogEntry {
    LogEntry* next;
    char* msg;
};

/*
 * Logging tool.
 * 
 * Provide rotating log buffer with configurable maximum log content size.
 */
class Logger {
    public:
        void begin(unsigned long maxSize);
        void loop();
        void log(String msg);
        void log(char* msg);
        void log(const char *format, ...);
        void getLogs(char* buffer, unsigned long size);
    private:
        unsigned long maxSize;
        unsigned long size = 0;
        LogEntry *firstLog = NULL;
        LogEntry *lastLog = NULL;
};

extern Logger logger;

#endif
