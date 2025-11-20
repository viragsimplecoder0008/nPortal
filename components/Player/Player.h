#pragma once

#include "../ECS/GameObject.h"
#include "../ECS/PhysicsBody.h"
#include "PlayerControllerComponent.h"

class Player : public GameObject {
public:
    int health;

    Player() : health(100) {
        AddComponent<PhysicsBody>();
        AddComponent<PlayerControllerComponent>();
    }
};
