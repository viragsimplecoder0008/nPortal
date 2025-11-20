#include <libndls.h>
#include <os.h>
#include <cstdint>
#include <cstdio>

#include "components/InputController/InputController.h"
#include "components/GameClock/GameClock.h"
#include "components/Logger/Logger.h"
#include "components/GraphicsSystem/GraphicsSystem.h"
#include "components/GameState/GameState.h"
#include "components/World/WorldFactory.h"
#include "components/World/IWorld.h"
#include "components/ResourceManager/ResourceManager.h"

int main(){

    // disable interrupts to prevent timer interference
    int int_state = TCT_Local_Control_Interrupts(-1);

    GameClock gameClock;
    InputController input;
    Logger logger;
    GraphicsSystem graphics;
    GameState gameState;

    constexpr double FPS_REPORT_INTERVAL_MS = 1000.0;
    uint32_t fps_frame_count = 0;
    double fps_timer_ms = 0.0;
    uint32_t last_time = gameClock.get_time_cycles();
    GLFix accumulator = 0.0f;

    GLFix ROUNDED_FIXED_TIMESTEP = GLFix(FIXED_TIMESTEP); // for use in physics calculations. Stick to this same <24>8 fixed-point representation throughout the codebase

    gameClock.init_clock();
    logger.init();
    ResourceManager::Instance().LoadAllAssets();
    gameState.init();
    graphics.init(&gameState);
    
    // Initialize player controller component
    if (auto* pc = gameState.player->GetComponent<PlayerControllerComponent>()) {
        pc->Init(&input);
    }

    auto world = WorldFactory::Instance().CreateWorld("TestLevel");
    std::string currentWorldName = "TestLevel";
    if (world) {
        world->Load();
    } else {
        // Fallback or error handling
    }

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

        bool inputChanged = input.pollInput();

        if (InputController::isDown(InputController::Key::Escape)) {
            break; // Exit the loop if Escape key is pressed
        }

        if (InputController::isDown(InputController::Key::SwitchWorld)) {
            // Simple toggle for now
            std::string nextWorld = (currentWorldName == "TestLevel") ? "SimpleWorld" : "TestLevel";
            
            if (world) world->Unload();
            world = WorldFactory::Instance().CreateWorld(nextWorld);
            if (world) {
                world->Load();
                currentWorldName = nextWorld;
                Logger::printf("Switched to world: %s\n", currentWorldName.c_str());
            }
            
            // Debounce or wait for key release would be better, but for now rely on quick press or flag
            // Since isDown is true every frame, we might switch back and forth rapidly.
            // Ideally we need 'isPressed' (just went down).
            // InputController doesn't seem to have that exposed easily yet, relying on pollInput returning changed.
            // Let's add a simple debounce hack or check if it was NOT down last frame.
            // Actually InputController::pollInput returns true if ANY key changed.
            // But isDown just checks current state.
            
            // For this task, I'll assume the user taps it quickly or I should implement 'JustPressed'.
            // Let's implement a simple 'JustPressed' logic here or in InputController.
            // But I can't easily change InputController header right now without recompiling everything.
            // I'll just add a static bool to debounce in main loop.
             while(InputController::isDown(InputController::Key::SwitchWorld)) {
                 input.pollInput(); // Wait for release
             }
        }

        gameClock.steps_run = 0;

        while (accumulator >= ROUNDED_FIXED_TIMESTEP && gameClock.steps_run < MAX_STEPS_PER_FRAME) {

            // game update logic here (physics especially) using ROUNDED_FIXED_TIMESTEP
            gameState.player->Update(ROUNDED_FIXED_TIMESTEP.toFloat());
            if (world) world->Update(ROUNDED_FIXED_TIMESTEP.toFloat());

            accumulator -= ROUNDED_FIXED_TIMESTEP;
            gameClock.steps_run++;
        }

        // render here
        graphics.BeginFrame(inputChanged);
        if (world) world->Draw(&graphics);
        graphics.EndFrame();
    }

    if (world) world->Unload();

    graphics.deinit();
    logger.deinit();

    TCT_Local_Control_Interrupts(int_state);

    return 0;
}