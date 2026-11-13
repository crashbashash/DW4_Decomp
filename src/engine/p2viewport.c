#include "dw4/p2core.h"

/* The viewport: the rectangle and depth range the VU1 programs map clip space to. p2SetViewport
 * keeps it and derives the VU1 scale and offset constants that p2UploadViewport sends. */

typedef struct p2ViewportRect {
    float x;
    float y;
    float width;
    float height;
    float nearZ;
    float farZ;
} p2ViewportRect;

void p2SetViewport(int x, int y, int width, int height, float nearZ, float farZ);

extern p2ViewportRect p2Viewport;
extern float p2ViewportScale;
extern int p2DepthBias;

void p2SetViewportScale(float scale) {
    p2ViewportScale = scale;
}

/* Re-derives the viewport with the new bias. Drawing fields of an interlaced display keeps the
 * viewport at half height, so it is restored to the frame's size first. */
void p2SetDepthBias(int bias) {
    p2DepthBias = bias;
    if (p2Display.frameMode == 0 && p2Display.interlaced > 0 && p2Display.renderTarget == -1) {
        p2Viewport.y = p2Viewport.y * 2.0f;
        p2Viewport.height = p2Viewport.height * 2.0f;
    }
    p2SetViewport((int)p2Viewport.x, (int)p2Viewport.y, (int)p2Viewport.width, (int)p2Viewport.height,
                  p2Viewport.nearZ, p2Viewport.farZ);
}
