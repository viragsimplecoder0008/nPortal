#include <libndls.h>
#include <os.h>
#include <cstdint>

#include "components/PlayerInput/PlayerInput.h"
#include "components/GameClock/GameClock.h"

int main(){
    GameClock gameClock;
    PlayerInput input;

    gameClock.init_clock();

    uint32_t last_time = gameClock.get_time_cycles();

    // disable interrupts to prevent timer interference
    int int_state = TCT_Local_Control_Interrupts(-1);

    float accumulator = 0.0f;

    while (true) {
        uint32_t delta_cycles = gameClock.get_delta_cycles(last_time);
        double delta_ms = gameClock.cycles_to_ms(delta_cycles);

        accumulator += static_cast<float>(delta_ms) / 1000.0f; // convert ms to seconds

        input.pollInput();

        if (PlayerInput::isDown(PlayerInput::Key::Escape)) {
            break; // Exit the loop if Escape key is pressed
        }

        gameClock.steps_run = 0;

        while (accumulator >= FIXED_TIMESTEP && gameClock.steps_run < MAX_STEPS_PER_FRAME) {

            // game update logic here

            accumulator -= FIXED_TIMESTEP;
            gameClock.steps_run++;
        }

        // render here

    }

    TCT_Local_Control_Interrupts(int_state);

    return 0;
}