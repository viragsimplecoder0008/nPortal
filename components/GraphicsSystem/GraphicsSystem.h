//
// Created by Satyamedh on 16-11-2025.
//

#ifndef NPORTAL_GRAPHICSSYSTEM_H
#define NPORTAL_GRAPHICSSYSTEM_H

#include "../../nGL/gl.h"
#include <libndls.h>

class GraphicsSystem {
public:
    void init();
    void deinit();

    void update();


private:
    COLOR *framebuffer;

};


#endif //NPORTAL_GRAPHICSSYSTEM_H
