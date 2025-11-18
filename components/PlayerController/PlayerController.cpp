//
// Created by Satyamedh on 18-11-2025.
//

#include "PlayerController.h"


void PlayerController::init(GameState* gs, InputController* inp) {
    this->gameState = gs;
    this->input = inp;
}

void PlayerController::update(float deltaTime) {

    // assume input is already polled before this function is called

    // Simple movement logic
    GLFix moveSpeed = GLFix(MAX_MOVEMENT_SPEED) * GLFix(deltaTime); // 5 units per second

    // directional movement based on yaw. use C builtin trig functions for now but switch to TODO: lookup tables later
    GLFix forwardX = GLFix(cosf(static_cast<float>(gameState->player.entity.transform.yaw.toFloat() * (3.14159265f / 180.0f))));
    GLFix forwardZ = GLFix(sinf(static_cast<float>(gameState->player.entity.transform.yaw.toFloat() * (3.14159265f / 180.0f))));
    GLFix rightX = GLFix(cosf(static_cast<float>((gameState->player.entity.transform.yaw + GLFix(90)).toFloat() * (3.14159265f / 180.0f))));
    GLFix rightZ = GLFix(sinf(static_cast<float>((gameState->player.entity.transform.yaw + GLFix(90)).toFloat() * (3.14159265f / 180.0f))));
    if (InputController::isDown(InputController::Key::Forward)) {
        gameState->player.entity.transform.x += forwardX * moveSpeed;
        gameState->player.entity.transform.z += forwardZ * moveSpeed;
    }
    else if (InputController::isDown(InputController::Key::Backward)) { // can only go forwards or backwards at once
        gameState->player.entity.transform.x -= forwardX * moveSpeed;
        gameState->player.entity.transform.z -= forwardZ * moveSpeed;
    }

    if (InputController::isDown(InputController::Key::Right)) { // strafing
        gameState->player.entity.transform.x += rightX * moveSpeed;
        gameState->player.entity.transform.z += rightZ * moveSpeed;
    }
    else if (InputController::isDown(InputController::Key::Left)) { // can only go left or right at once
        gameState->player.entity.transform.x -= rightX * moveSpeed;
        gameState->player.entity.transform.z -= rightZ * moveSpeed;
    }

    // handle touchpad input for looking around. Also implement TODO: acceleration for better control
    float touchVelX = static_cast<float>(input->touchpad.x_velocity) * TOUCHPAD_SENSITIVITY; // sensitivity multiplier
    gameState->player.entity.transform.yaw += GLFix(touchVelX * deltaTime);

    float touchVelY = static_cast<float>(input->touchpad.y_velocity) * TOUCHPAD_SENSITIVITY;
    gameState->player.entity.transform.pitch += GLFix(touchVelY * deltaTime); // TODO: Optimize!
}



