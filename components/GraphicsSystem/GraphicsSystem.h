//
// Created by Satyamedh on 16-11-2025.
//

#ifndef NPORTAL_GRAPHICSSYSTEM_H
#define NPORTAL_GRAPHICSSYSTEM_H

#include "../../nGL/gl.h"
#include "../../nGL/gldrawarray.h"
#include "../../nGL/texturetools.h"
#include "../GameState/GameState.h"
#include "../Logger/Logger.h"

#include <libndls.h>

class GraphicsSystem {
public:
    void init(GameState* gameState);
    void deinit();

    void update(bool inputChanged);

private:
    TEXTURE* screen;

    ProcessedPosition* processed;

    GLFix angle;

    GameState* gameState;

    void setupCamera(bool inputChanged);

};


#endif //NPORTAL_GRAPHICSSYSTEM_H
