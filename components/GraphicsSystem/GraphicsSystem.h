//
// Created by Satyamedh on 16-11-2025.
//

#ifndef NPORTAL_GRAPHICSSYSTEM_H
#define NPORTAL_GRAPHICSSYSTEM_H

#include "../../nGL/gl.h"
#include "../GameState/GameState.h"
#include "../Logger/Logger.h"

#include <libndls.h>

class GraphicsSystem {
public:
    void init(GameState* gameState);
    void deinit();

    void update(bool inputChanged);

private:
    COLOR *framebuffer;

    GameState* gameState;

    void setupCamera(bool inputChanged);

};


#endif //NPORTAL_GRAPHICSSYSTEM_H
