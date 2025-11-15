// Auto-created glconfig.h based on glconfig_example.h
#ifndef __GLCONFIG_H__
#define __GLCONFIG_H__

#include <stdint.h>

// Colored triangles can still be used with glBindTexture(nullptr)
// #define TEXTURE_SUPPORT

// Warning, this is slower than textured rendering!
// #define INTERPOLATE_COLORS

// #define WIREFRAME_MODE

// If disabled, triangles partially behind the CLIP_PLANE will be discarded
#define Z_CLIPPING

// If some geometry inaccuracies annoy you, enable this.
// It's a bit slower though.
// #define BETTER_PERSPECTIVE

// Print "FPS: <fps>\n" to stdout every second
// #define FPS_COUNTER

#if defined(TEXTURE_SUPPORT) && defined(INTERPOLATE_COLORS)
#error "Colors and textures cannot be used simultaneously!"
#endif

#define CLIP_PLANE 25

#define MATRIX_STACK_SIZE 10

// Typical TI-Nspire screen resolution for nGL (defaults if not provided by build)
#ifndef SCREEN_WIDTH
#define SCREEN_WIDTH 320
#endif
#ifndef SCREEN_HEIGHT
#define SCREEN_HEIGHT 240
#endif

// 16-bit color (RGB565)
typedef uint16_t COLOR;

#endif // __GLCONFIG_H__

