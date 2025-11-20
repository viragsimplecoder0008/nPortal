namespace SimpleWorld {
    //Generated from Plane.obj by obj2ngl.py
    #include "../nGL/gldrawarray.h"

    static const VECTOR3 positions_Plane[] = {
    {25.0f, 0.0f, 25.0f},
    {-25.0f, 0.0f, -25.0f},
    {-25.0f, 0.0f, 25.0f},
    {25.0f, 0.0f, -25.0f}
};

const IndexedVertex vertices_Plane[6] = {
    {0, 0.000f, 0.000f, 0xc993},
    {1, 0.000f, 0.000f, 0xc993},
    {2, 0.000f, 0.000f, 0xc993},
    {0, 0.000f, 0.000f, 0xc993},
    {3, 0.000f, 0.000f, 0xc993},
    {1, 0.000f, 0.000f, 0xc993}
};

const ngl_object obj_Plane = {
    4 - 0,
    positions_Plane + 0,
    GL_TRIANGLES,
    6,
    vertices_Plane,
    nullptr
};

    static const ngl_object *objs_Plane_h[] __attribute__((unused)) = {
        &obj_Plane
    };
}
