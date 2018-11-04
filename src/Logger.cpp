#include "PowerMonitor.h"

void Logger::begin(unsigned long maxSize) {
    this->maxSize = maxSize;
}

void Logger::loop() {
}

void Logger::log(String str) {
    // Create the new log entry.
    LogEntry* entry = new LogEntry;
    entry->msg = new char[str.length() + 1];
    entry->next = NULL;
    // The .toCharArray provides the null termination.
    str.toCharArray(entry->msg, str.length() + 1);

    // Update the fist/last pointers.
    if (firstLog == NULL) {
        firstLog = entry;
    } else {
        lastLog->next = entry;
    }
    lastLog = entry;

    // Update the log buffer size to include the new log message.
    size += str.length();

    // Check if we are not over the maximum specified log buffer length. If we
    // are - start deleting log entries.
    while (size > maxSize && firstLog != NULL) {
        LogEntry* entryToDelete = firstLog;

        // Correct the first/last log entries.
        firstLog = firstLog->next;
        if (firstLog == NULL) {
            lastLog = NULL;
        }

        // Update the size by removing the deleted entry length.
        size -= strlen(entryToDelete->msg);

        // Delete the entry.
        delete[] entryToDelete->msg;
        delete entryToDelete;
    }
}

void Logger::log(char* str) {
    // Cause I'm a bit lazy... :) .
    this->log(String(str));
}

void Logger::log(const char *format, ...) {
    va_list arg;
    va_start(arg, format);
    char buffer[128];
    unsigned int len = vsnprintf(buffer, sizeof(buffer), format, arg);
    va_end(arg);
    if (len > sizeof(buffer)) {
        log("Trimming log!");
    }
    log(buffer);
}

void Logger::getLogs(char* buffer, unsigned long size) {
    LogEntry* entry = firstLog;
    unsigned long pos = 0;

    // Iterate over the log entries. Append each log entry msg to the buffer.
    // Use new line as log entry separator.
    while (entry != NULL && pos < size - 1) {
        unsigned int len = strlen(entry->msg);

        if (pos + len + 1 > size) {
            len = size - pos - 1;
        }
        memcpy(buffer + pos, entry->msg, len);
        pos += len;
        buffer[pos] = '\n';
        pos++;
        entry = entry->next;
    }

    // Update the last new line to the null terminating character.
    buffer[pos-1] = 0;
}

Logger logger = Logger();