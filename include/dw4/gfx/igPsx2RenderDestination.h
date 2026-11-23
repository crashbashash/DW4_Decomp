#ifndef DW4_IGPSX2RENDERDESTINATION_H
#define DW4_IGPSX2RENDERDESTINATION_H

#include "dw4/gfx/igPsx2HandlePool.h"

/* One render destination of igPsx2VisualContext (an element of its _pBufList pool): the format
 * createRenderDestination was given, and, once the destination is bound as a texture, the texture handle and the
 * GS color and depth targets that back it. */
struct igPsx2RenderDestination {
    int width;
    int height;
    int colorBitsPerPixel;
    int depthBitsPerPixel;
    int alphaBitsPerPixel;
    int stencilBitsPerPixel;
    float pixelAspectRatio;
    int type;                   /* IG_GFX_RENDERDESTINATION_TYPE; 2 renders into a texture */
    int unused32;
    int textureHandle;          /* the context texture bound to this destination, -1 for none */
    int colorTarget;            /* P2Texture of the color buffer, 0 until a texture is bound */
    int depthTarget;            /* P2Texture of the depth buffer */
};

typedef igPsx2HandlePool<igPsx2RenderDestination> igPsx2RenderDestinationPool;

#endif
