//
// Created by Satyamedh on 19-11-2025.
//

#ifndef NPORTAL_CUBE_H
#define NPORTAL_CUBE_H


//Generated from cube.obj by obj2ngl.py
#include "../../nGL/gldrawarray.h"

struct ngl_object {
    unsigned int count_positions;
    const VECTOR3 *positions;
    GLDrawMode draw_mode;
    unsigned int count_vertices;
    const IndexedVertex *vertices;
    const TEXTURE *texture;
};

static const VECTOR3 positions_cube_h[] = {
        {1.0f, -1.0f, -1.0f},
        {1.0f, -1.0f, 1.0f},
        {-1.0f, -1.0f, 1.0f},
        {-1.0f, -1.0f, -1.0f},
        {1.0f, 1.0f, -0.999999f},
        {0.999999f, 1.0f, 1.000001f},
        {-1.0f, 1.0f, 1.0f},
        {-1.0f, 1.0f, -1.0f}
};

static const IndexedVertex vertices_Cube[24] = {
        {0, 0.000f, 0.000f, 0xa514},
        {1, 0.000f, 0.000f, 0xa514},
        {2, 0.000f, 0.000f, 0xa514},
        {3, 0.000f, 0.000f, 0xa514},
        {4, 0.000f, 0.000f, 0xa514},
        {7, 0.000f, 0.000f, 0xa514},
        {6, 0.000f, 0.000f, 0xa514},
        {5, 0.000f, 0.000f, 0xa514},
        {0, 0.000f, 0.000f, 0xa514},
        {4, 0.000f, 0.000f, 0xa514},
        {5, 0.000f, 0.000f, 0xa514},
        {1, 0.000f, 0.000f, 0xa514},
        {1, 0.000f, 0.000f, 0xa514},
        {5, 0.000f, 0.000f, 0xa514},
        {6, 0.000f, 0.000f, 0xa514},
        {2, 0.000f, 0.000f, 0xa514},
        {2, 0.000f, 0.000f, 0xa514},
        {6, 0.000f, 0.000f, 0xa514},
        {7, 0.000f, 0.000f, 0xa514},
        {3, 0.000f, 0.000f, 0xa514},
        {4, 0.000f, 0.000f, 0xa514},
        {0, 0.000f, 0.000f, 0xa514},
        {3, 0.000f, 0.000f, 0xa514},
        {7, 0.000f, 0.000f, 0xa514}
};

static const ngl_object obj_Cube = {
        9 - 0,
        positions_cube_h + 0,
        GL_QUADS,
        24,
        vertices_Cube,
        nullptr
};

static const ngl_object *objs_cube_h[] = {
        &obj_Cube
};

#endif //NPORTAL_CUBE_H
