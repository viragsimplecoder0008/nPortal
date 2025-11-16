//
// Created by Satyamedh on 16-11-2025.
//

#include "GameClock.h"

void GameClock::init_clock() {
    *TMR1_CLKSEL = CLOCK_32KHZ;
    *TMR1_CONTROL = 0; // disable before configuring
    *TMR1_INTCLR = 1;  // clear pending interrupts
    *TMR1_LOAD = 0xFFFFFFFF;
    *TMR1_CONTROL = TIMER_ENABLE | TIMER_32BIT | TIMER_PERIODIC;
}

uint32_t GameClock::get_time_cycles() {
    return *TMR1_VALUE;
}

uint32_t GameClock::get_delta_cycles(uint32_t &last_cycles) {
    uint32_t current = get_time_cycles();
    uint32_t delta = last_cycles >= current ? last_cycles - current : (last_cycles + (0xFFFFFFFF - current));
    last_cycles = current;
    return delta;
}

double GameClock::cycles_to_ms(uint32_t cycles) const {
    return (static_cast<double>(cycles) * 1000.0) / CLOCK_FREQ;
}
