//
// Created by Satyamedh on 18-11-2025.
//

#include "PlayerController.h"
#include "../../nGL/fastmath.h"
#include <algorithm>

void PlayerController::init(GameState* gs, InputController* inp) {
    this->gameState = gs;
    this->input = inp;
}

void PlayerController::update(float deltaTime) {

    // assume input is already polled before this function is called

    // TODO: implement acceleration for more accurate touchpad movement

    if (tp_had_contact && input->touchpad.contact) {
        int16_t delta_x = ((input->touchpad.x) - (tp_last_x)) / 50;
        int16_t delta_y = ((input->touchpad.y) - (tp_last_y)) / 50;

        gameState->player.entity.transform.yaw += FFix(static_cast<float>(delta_x) * TOUCHPAD_SENSITIVITY_X);
        gameState->player.entity.transform.pitch -= FFix(static_cast<float>(delta_y) * TOUCHPAD_SENSITIVITY_Y);
    }

    tp_had_contact = input->touchpad.contact;
    tp_last_x = input->touchpad.x;
    tp_last_y = input->touchpad.y;

    if (gameState->player.entity.transform.yaw > FFix(360.0f)) {
        gameState->player.entity.transform.yaw -= FFix(360.0f);
    } else if (gameState->player.entity.transform.yaw < FFix(0.0f)) {
        gameState->player.entity.transform.yaw += FFix(360.0f);
    }

    gameState->player.entity.transform.pitch = std::clamp(
            gameState->player.entity.transform.pitch,
            GLFix(-89.9f),
            GLFix(89.9f)
    );

    // Simple movement logic
    GLFix moveSpeed = GLFix(MAX_MOVEMENT_SPEED) * GLFix(deltaTime); // 5 units per second

    // use functions from fastmath.h to compute forward vector based on yaw and pitch. FLTs ftw
    VECTOR3 forward = {
            fast_cos(gameState->player.entity.transform.pitch) * fast_sin(gameState->player.entity.transform.yaw),
            fast_sin(gameState->player.entity.transform.pitch),
            fast_cos(gameState->player.entity.transform.pitch) * fast_cos(gameState->player.entity.transform.yaw)
    };
    VECTOR3 right = {
            fast_sin(gameState->player.entity.transform.yaw + FFix(90)),
            FFix(0),
            fast_cos(gameState->player.entity.transform.yaw + FFix(90))
    };

    VECTOR3 velocity = {0, 0, 0}; // TODO: Find a cleaner way to add and subtract these
    if (InputController::isDown(InputController::Key::Forward))
        velocity += forward;
    if (InputController::isDown(InputController::Key::Backward))
        velocity -= forward;
    if (InputController::isDown(InputController::Key::Right))
        velocity += right;
    if (InputController::isDown(InputController::Key::Left))
        velocity -= right;

    // Normalize the velocity vector to prevent faster diagonal movement. There is no fast normalize, so use the builtin method
    float length = sqrt(velocity.x.toFloat() * velocity.x.toFloat() +
                              velocity.y.toFloat() * velocity.y.toFloat() +
                              velocity.z.toFloat() * velocity.z.toFloat());
    if (length > 0.0f) {
        velocity.x = GLFix(velocity.x.toFloat() / length);
        velocity.y = GLFix(velocity.y.toFloat() / length);
        velocity.z = GLFix(velocity.z.toFloat() / length);
    }

    velocity *= moveSpeed;
    gameState->player.entity.transform.x += velocity.x;
    gameState->player.entity.transform.y += velocity.y;
    gameState->player.entity.transform.z += velocity.z;

    // TODO: for now, directly modify position. Later, use physics engine and velocity


}



