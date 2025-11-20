#pragma once

#include "../../nGL/gl.h"
#include "../../nGL/fastmath.h"

struct Transform {
    GLFix x, y, z;
    FFix pitch, yaw, roll;

    Transform() : x(0), y(0), z(0), pitch(0), yaw(0), roll(0) {}
};
