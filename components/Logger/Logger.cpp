//
// Created by Satyamedh on 16-11-2025.
//

#include "Logger.h"

void Logger::init() {
    this->printf("=========== nPortal Logs begin ===========\n");
}

void Logger::printf(const char* format, ...) {
#if DEBUGGING_MODE
    volatile char* uart_base = reinterpret_cast<volatile char*>(UART_ADDR);
    volatile char* uart_dr = uart_base + 0x00;   // Data Register
    volatile char* uart_fr = uart_base + 0x18;   // Flag Register

    // Print the tag first
    const char* tag_ptr = TAG;
    while (*tag_ptr) {
        // Wait until UART is ready to transmit
        while (*(uart_fr) & (1 << 5)); // Wait while TXFF (Transmit FIFO Full) is set
        *(uart_dr) = *tag_ptr++;
    }

    char buffer[256]; // Adjust size as needed
    va_list args;
    va_start(args, format);
    int len = vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    // Transmit the formatted string
    for (int i = 0; i < len; ++i) {
        // Wait until UART is ready to transmit
        while (*(uart_fr) & (1 << 5)); // Wait while TXFF (
        *(uart_dr) = buffer[i];
    }
#endif
}

void Logger::deinit() {
    this->printf("=========== nPortal Logs end ===========\n");
}

