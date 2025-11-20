//
// Created by Satyamedh on 18-11-2025.
//

#include "PlayerControllerComponent.h"
#include "../ECS/GameObject.h"

void PlayerControllerComponent::Update(float deltaTime) {
    if (!input || !gameObject) return;

    // assume input is already polled before this function is called

    // TODO: implement acceleration for more accurate touchpad movement

    if (tp_had_contact && input->touchpad.contact) {
        int16_t delta_x = ((input->touchpad.x) - (tp_last_x)) / 50;
        int16_t delta_y = ((input->touchpad.y) - (tp_last_y)) / 50;

        gameObject->transform.yaw += FFix(static_cast<float>(delta_x) * TOUCHPAD_SENSITIVITY_X);
        gameObject->transform.pitch -= FFix(static_cast<float>(delta_y) * TOUCHPAD_SENSITIVITY_Y);
    }

    tp_had_contact = input->touchpad.contact;
    tp_last_x = input->touchpad.x;
    tp_last_y = input->touchpad.y;

    if (gameObject->transform.yaw > FFix(360.0f)) {
        gameObject->transform.yaw -= FFix(360.0f);
    } else if (gameObject->transform.yaw < FFix(0.0f)) {
        gameObject->transform.yaw += FFix(360.0f);
    }

    gameObject->transform.pitch = std::clamp(
            gameObject->transform.pitch,
            GLFix(-89.9f),
            GLFix(89.9f)
    );

    // Simple movement logic
    GLFix moveSpeed = GLFix(MAX_MOVEMENT_SPEED) * GLFix(deltaTime); // 5 units per second

    // use functions from fastmath.h to compute forward vector based on yaw and pitch. FLTs ftw
    VECTOR3 forward = {
            fast_cos(gameObject->transform.pitch) * fast_sin(gameObject->transform.yaw),
            0, // no flying
            fast_cos(gameObject->transform.pitch) * fast_cos(gameObject->transform.yaw)
    };
    VECTOR3 right = {
            fast_sin(gameObject->transform.yaw + FFix(90)),
            FFix(0),
            fast_cos(gameObject->transform.yaw + FFix(90))
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
    if (InputController::isDown(InputController::Key::Up)) // TODO: Remove flying later
        velocity.y += moveSpeed;
    if (InputController::isDown(InputController::Key::Down))
        velocity.y -= moveSpeed;

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
    gameObject->transform.x += velocity.x;
    gameObject->transform.y += velocity.y;
    gameObject->transform.z += velocity.z;

    // TODO: for now, directly modify position. Later, use physics engine and velocity
}



