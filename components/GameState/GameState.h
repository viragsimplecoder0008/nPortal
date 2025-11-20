//
// Created by Satyamedh on 18-11-2025.
//

#ifndef NPORTAL_GAMESTATE_H
#define NPORTAL_GAMESTATE_H

#include <string>

#include "../../nGL/gl.h"
#include "../../nGL/fastmath.h"

struct Transform {
    GLFix x, y, z;
    FFix pitch, yaw, roll;
};

struct PhysicsBody {
    GLFix velocityX, velocityY, velocityZ;
    GLFix accelerationX, accelerationY, accelerationZ;
    bool onGround;
}; // TODO: Update when working on physics engine

struct Entity {
    Transform transform;
    PhysicsBody physics;
    // Additional components can be added here
};

struct Player {
    Entity entity;
    int health;
};

class GameState {
public:
    Player player;
    std::string currentLevel;

    void init();

};


#endif //NPORTAL_GAMESTATE_H
