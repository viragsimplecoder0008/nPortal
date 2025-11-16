//
// Created by Satyamedh on 16-11-2025.
//

#include "GraphicsSystem.h"

void GraphicsSystem::init() {
    nglInit();
    framebuffer = new COLOR[SCREEN_WIDTH * SCREEN_HEIGHT];
    nglSetBuffer(framebuffer);
}

void GraphicsSystem::deinit() {
    delete[] framebuffer;
    nglUninit();
}

void GraphicsSystem::loop() {
    // render one frame. This function is called within the main loop

    glColor3f(0.4f, 0.7f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    nglDisplay();
}


