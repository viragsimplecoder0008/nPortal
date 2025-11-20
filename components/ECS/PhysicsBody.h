#pragma once

#include "../ECS/Component.h"
#include "../../nGL/gl.h"

struct PhysicsBody : public Component {
    GLFix velocityX, velocityY, velocityZ;
    GLFix accelerationX, accelerationY, accelerationZ;
    bool onGround;

    PhysicsBody() : velocityX(0), velocityY(0), velocityZ(0), 
                    accelerationX(0), accelerationY(0), accelerationZ(0), 
                    onGround(false) {}

    void Update(float) override {
        // Basic physics integration could go here
    }
};
