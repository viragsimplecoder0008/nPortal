//
// Created by Satyamedh on 16-11-2025.
//

#include "GraphicsSystem.h"

void GraphicsSystem::init(GameState* GameState) {
    nglInit();
    framebuffer = new COLOR[SCREEN_WIDTH * SCREEN_HEIGHT];
    nglSetBuffer(framebuffer);

    this->gameState = GameState;
}

void GraphicsSystem::deinit() {
    delete[] framebuffer;
    nglUninit();
}

void GraphicsSystem::setupCamera(bool inputChanged) {
    if (inputChanged) {
        if (!gameState) {
            return;
        }

        glLoadIdentity();

        const Transform &cameraTransform = gameState->player.entity.transform;

        // Apply inverse player orientation so the scene renders from the player view.
        nglRotateZ(-cameraTransform.roll);
        nglRotateX(-cameraTransform.pitch);
        nglRotateY(-cameraTransform.yaw);

        glTranslatef(-cameraTransform.x, -cameraTransform.y, -cameraTransform.z);

        Logger::printf("Camera position: (%f, %f, %f) | Rotation: (Pitch: %f, Yaw: %f, Roll: %f)\n",
                       cameraTransform.x.toFloat(),
                       cameraTransform.y.toFloat(),
                       cameraTransform.z.toFloat(),
                       cameraTransform.pitch.toFloat(),
                       cameraTransform.yaw.toFloat(),
                       cameraTransform.roll.toFloat());
    }
}

void GraphicsSystem::update(bool inputChanged) {
    // render one frame. This function is called within the main loop

    glColor3f(0.4f, 0.7f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->setupCamera(inputChanged);

    nglDisplay();
}
