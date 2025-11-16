#include <libndls.h>
#include <os.h>
#include <cstdint>
#include <cstdio>

#include "components/PlayerInput/PlayerInput.h"
#include "components/GameClock/GameClock.h"
#include "components/Logger/Logger.h"
#include "components/GraphicsSystem/GraphicsSystem.h"

int main(){

    // disable interrupts to prevent timer interference
    int int_state = TCT_Local_Control_Interrupts(-1);

    GameClock gameClock;
    PlayerInput input;
    Logger logger;
    GraphicsSystem graphics;

    constexpr double FPS_REPORT_INTERVAL_MS = 1000.0;
    uint32_t fps_frame_count = 0;
    double fps_timer_ms = 0.0;
    uint32_t last_time = gameClock.get_time_cycles();
    float accumulator = 0.0f;

    gameClock.init_clock();
    logger.init();
    graphics.init();

    while (true) {
        uint32_t delta_cycles = gameClock.get_delta_cycles(last_time);
        double delta_ms = gameClock.cycles_to_ms(delta_cycles);

        accumulator += static_cast<float>(delta_ms) / 1000.0f; // convert ms to seconds

        fps_frame_count++;
        fps_timer_ms += delta_ms;

        if (fps_timer_ms >= FPS_REPORT_INTERVAL_MS) {
            double fps = fps_timer_ms > 0.0 ? (fps_frame_count * 1000.0) / fps_timer_ms : 0.0;
            logger.printf("FPS: %.2f\n", fps);
            fps_frame_count = 0;
            fps_timer_ms = 0.0;
        }

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
        graphics.loop();
    }

    graphics.deinit();
    logger.deinit();

    TCT_Local_Control_Interrupts(int_state);

    return 0;
}