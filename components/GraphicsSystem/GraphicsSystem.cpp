//
// Created by Satyamedh on 16-11-2025.
//

#include "GraphicsSystem.h"
#include "cube.h"

void GraphicsSystem::init(GameState* GameState) {
    nglInit();
    this->screen = newTexture(SCREEN_WIDTH, SCREEN_HEIGHT, 0, false);
    nglSetBuffer(screen->bitmap);

    size_t max_pos = 0;
    for(auto &&obj : objs_cube_h)
        if(obj->count_positions > max_pos)
            max_pos = obj->count_positions;

    this->processed = new ProcessedPosition[max_pos];

    this->angle = 0;

    this->gameState = GameState;
}

void GraphicsSystem::deinit() {
    deleteTexture(screen);
    nglUninit();
}

void GraphicsSystem::setupCamera(bool inputChanged) {
    if (!gameState) {
        return;
    }

    glLoadIdentity();

    const Transform &cameraTransform = gameState->player.entity.transform;

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

void GraphicsSystem::update(bool inputChanged) {
    // render one frame. This function is called within the main loop
    glPushMatrix();
        glColor3f(0.4f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        this->setupCamera(inputChanged);
        glTranslatef(0, 0, 400);
        angle += 1;
        nglRotateY(angle.normaliseAngle());

    glScale3f(100, 100, 100);

    bool transformed = false;
    for (auto &&obj : objs_cube_h) {
        glBindTexture(obj->texture);
        nglDrawArray(obj->vertices, obj->count_vertices, obj->positions, obj->count_positions, processed, obj->draw_mode, !transformed);
        transformed = true;
    }

    glPopMatrix();

    nglDisplay();
}
