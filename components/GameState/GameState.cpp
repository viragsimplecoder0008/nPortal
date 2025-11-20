//
// Created by Satyamedh on 18-11-2025.
//

#include "GameState.h"

void GameState::init() {
    // Initialize player
    player = std::make_unique<Player>();

    player->transform.x = GLFix(0);
    player->transform.y = GLFix(0);
    player->transform.z = GLFix(0);
    player->transform.pitch = FFix(0);
    player->transform.yaw = FFix(0);
    player->transform.roll = FFix(0);

    auto* physics = player->GetComponent<PhysicsBody>();
    if (physics) {
        physics->velocityX = GLFix(0);
        physics->velocityY = GLFix(0);
        physics->velocityZ = GLFix(0);
        physics->accelerationX = GLFix(0);
        physics->accelerationY = GLFix(0);
        physics->accelerationZ = GLFix(0);
        physics->onGround = true;
    }

    player->health = 100;

    // Set initial level
    currentLevel = "Testlvl";
}