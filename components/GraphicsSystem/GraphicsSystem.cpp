//
// Created by Satyamedh on 16-11-2025.
//

#include "GraphicsSystem.h"

void GraphicsSystem::init(GameState* GameState) {
    nglInit();
    this->screen = newTexture(SCREEN_WIDTH, SCREEN_HEIGHT, 0, false);
    nglSetBuffer(screen->bitmap);

    this->processed = nullptr;
    this->processed_size = 0;

    this->gameState = GameState;
}

void GraphicsSystem::deinit() {
    if (processed) delete[] processed;
    deleteTexture(screen);
    nglUninit();
}

void GraphicsSystem::EnsureBufferSize(unsigned int count_positions) {
    if (count_positions > processed_size) {
        if (processed) delete[] processed;
        processed = new ProcessedPosition[count_positions];
        processed_size = count_positions;
    }
}

void GraphicsSystem::setupCamera(bool inputChanged) {
    if (!gameState) {
        return;
    }

    glLoadIdentity();

    const Transform &cameraTransform = gameState->player->transform;

    // Apply inverse player orientation so the scene renders from the player view.
    nglRotateZ((GLFix(359) - cameraTransform.roll).normaliseAngle());
    nglRotateX((GLFix(359) - cameraTransform.pitch).normaliseAngle());
    nglRotateY((GLFix(359) - cameraTransform.yaw).normaliseAngle());

    glTranslatef(-cameraTransform.x, -cameraTransform.y, -cameraTransform.z);

    if (inputChanged) {
        Logger::printf("Camera position: (%f, %f, %f) | Rotation: (Pitch: %f, Yaw: %f, Roll: %f)\n",
                       cameraTransform.x.toFloat(),
                       cameraTransform.y.toFloat(),
                       cameraTransform.z.toFloat(),
                       cameraTransform.pitch.toFloat(),
                       cameraTransform.yaw.toFloat(),
                       cameraTransform.roll.toFloat());
    }
}

void GraphicsSystem::BeginFrame(bool inputChanged) {
    glPushMatrix();
    glColor3f(0.4f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    this->setupCamera(inputChanged);
}

void GraphicsSystem::EndFrame() {
    glPopMatrix();
    nglDisplay();
}

void GraphicsSystem::DrawMesh(const ngl_object* obj, bool transformed) {
    EnsureBufferSize(obj->count_positions);
    if (obj->texture) glBindTexture(obj->texture);
    nglDrawArray(obj->vertices, obj->count_vertices, obj->positions, obj->count_positions, processed, obj->draw_mode, !transformed);
}
