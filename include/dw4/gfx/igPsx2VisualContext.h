#ifndef DW4_IGPSX2VISUALCONTEXT_H
#define DW4_IGPSX2VISUALCONTEXT_H

#include "dw4/gfx/GfxMetaEnums.h"

struct igMetaObject;
struct igPsx2VisualContext;
struct igVec4f;
struct igVertexArray;
struct igIndexArray;
struct igPrimLengthArray;

/* What vfunc_46 copies into a new render destination; the render-destination attribute leaves the last
 * word unset. */
typedef struct RenderDestinationDesc {
    int type;
    int sizeX;
    int sizeY;
    int colorBitCount;
    int alphaBitCount;
    int depthBitCount;
    int stencilBitCount;
    float f28;
} RenderDestinationDesc;

#ifdef __cplusplus
extern "C" {
#endif

/* setRenderDestination (slot 46) and its texture form (slot 47): igSetRenderDestinationAttr::apply passes a
 * trailing 0 the PS2 overrides ignore. */
void FUN_00174510(struct igPsx2VisualContext *self, IG_GFX_BLENDING_FUNCTION source, IG_GFX_BLENDING_FUNCTION destination, unsigned char blendConstant, int stage);
/* The kit's setBlendingMatrices(igUnsignedInt, igMatrix44f *): the attrs pass their count and matrix cache. */

#ifdef __cplusplus
}
#endif

#endif
