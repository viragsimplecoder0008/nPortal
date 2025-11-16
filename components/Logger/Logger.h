//
// Created by Satyamedh on 16-11-2025.
//

#ifndef NPORTAL_LOGGER_H
#define NPORTAL_LOGGER_H

#include <stdint.h>
#include <cstdarg>
#include <cstdio>

#define UART_ADDR 0x90020000

#define DEBUGGING_MODE 1

class Logger {
public:
    void init();
    void printf(const char* format, ...);
    void deinit();

private:
    // tag
    const char* TAG = "(nPortal) ";

};


#endif //NPORTAL_LOGGER_H
