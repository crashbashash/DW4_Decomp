#ifndef DW4_IGPOINTSPRITEEXT_H
#define DW4_IGPOINTSPRITEEXT_H

/* igPointSpriteExt: the point-sprite extension of a vertex array (C++: it takes an igVec2f by value). */
#include "dw4/igMath.h"

struct igPointSpriteExt;

extern "C" void igPointSpriteExt_SetSize(struct igPointSpriteExt *self, int index, igVec2f size);

#endif
