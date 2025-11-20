//
// Created by Satyamedh on 18-11-2025.
//

#include "GameState.h"

void GameState::init() {
    // Initialize player
    player.entity.transform.x = GLFix(0);
    player.entity.transform.y = GLFix(0);
    player.entity.transform.z = GLFix(0);
    player.entity.transform.pitch = FFix(0);
    player.entity.transform.yaw = FFix(0);
    player.entity.transform.roll = FFix(0);

    player.entity.physics.velocityX = GLFix(0);
    player.entity.physics.velocityY = GLFix(0);
    player.entity.physics.velocityZ = GLFix(0);
    player.entity.physics.accelerationX = GLFix(0);
    player.entity.physics.accelerationY = GLFix(0);
    player.entity.physics.accelerationZ = GLFix(0);
    player.entity.physics.onGround = true;

    player.health = 100;

    // Set initial level
    currentLevel = "Testlvl";
}