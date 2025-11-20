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

    void BeginFrame(bool inputChanged);
    void EndFrame();
    void DrawMesh(const struct ngl_object* obj, bool transformed);
    void EnsureBufferSize(unsigned int count_positions);

private:
    TEXTURE* screen;

    ProcessedPosition* processed;
    unsigned int processed_size;

    GameState* gameState;

    void setupCamera(bool inputChanged);

};


#endif //NPORTAL_GRAPHICSSYSTEM_H
