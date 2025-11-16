//
// Created by Satyamedh on 16-11-2025.
//

#include "GraphicsSystem.h"

void GraphicsSystem::init() {
    nglInit();
    framebuffer = new COLOR[SCREEN_WIDTH * SCREEN_HEIGHT];
}

void GraphicsSystem::deinit() {
    delete[] framebuffer;
    nglUninit();
}

