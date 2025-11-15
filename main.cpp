#include <libndls.h>
#include "nGL/gl.h"

const VERTEX triangle[] =
        {
                {0, 0, 0, 0, 0, 0xFFFF}, // 1
                {0, 100, 0, 0, 0, 0xFFFF}, // 2
                {100, 0, 0, 0, 0, 0xFFFF}, // 3

                {0, 100, 0, 0, 0, 0xFFFF}, // 2
                {0, 0, 0, 0, 0, 0xFFFF}, // 1
                {100, 0, 0, 0, 0, 0xFFFF}, //3
        };

int main()
{
    // Initialize nGL first
    nglInit();
    // Allocate the framebuffer
    COLOR *framebuffer = new COLOR[SCREEN_WIDTH * SCREEN_HEIGHT];
    nglSetBuffer(framebuffer);

    GLFix angle = 0;
    while(!isKeyPressed(KEY_NSPIRE_ESC))
    {
        glPushMatrix();
        glColor3f(0.4f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glTranslatef(0, 0, 1000);
        angle += 1;
        nglRotateY(angle.normaliseAngle());
        glBegin(GL_TRIANGLES);
        nglAddVertices(angle < GLFix(90) || angle > GLFix(270) ? triangle : (triangle + 3), 3);
        glEnd();
        glPopMatrix();
        nglDisplay();
    }

    // Deinitialize nGL
    nglUninit();
    delete[] framebuffer;
}