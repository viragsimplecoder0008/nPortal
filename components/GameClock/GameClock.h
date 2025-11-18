//
// Created by Satyamedh on 16-11-2025.
//

#ifndef NPORTAL_GAMECLOCK_H
#define NPORTAL_GAMECLOCK_H

#include <cstdint>

// Base address for the SP804 dual-timer
#define SP804_BASE (0x900D0000)
#define CLOCK_FREQ 32768 // 32 kHz

#define TARGET_FPS 30
#define FIXED_TIMESTEP 1.0f / 30.0f

#define TIMER_ENABLE  (1 << 7)
#define TIMER_PERIODIC (1 << 6)
#define TIMER_32BIT   (1 << 1)
#define TIMER_ONESHOT (1 << 0)

#define CLOCK_32KHZ    (1 << 1)

#define MAX_STEPS_PER_FRAME 4

class GameClock {
public:

    // Pointers to the registers for Timer 2 (using standard offsets)
    volatile uint32_t* TMR1_LOAD    = (uint32_t*)(SP804_BASE + 0x020);
    volatile uint32_t* TMR1_VALUE   = (uint32_t*)(SP804_BASE + 0x024);
    volatile uint32_t* TMR1_CONTROL = (uint32_t*)(SP804_BASE + 0x028);
    volatile uint32_t* TMR1_INTCLR  = (uint32_t*)(SP804_BASE + 0x02C);
    volatile uint32_t* TMR1_CLKSEL  = (uint32_t*)(SP804_BASE + 0x080);

    void init_clock();
    uint32_t get_time_cycles();
    uint32_t get_delta_cycles(uint32_t &last_cycles);
    double   cycles_to_ms(uint32_t cycles) const;

    int steps_run = 0;

};

#endif //NPORTAL_GAMECLOCK_H
