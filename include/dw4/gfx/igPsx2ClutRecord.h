#ifndef DW4_IGPSX2CLUTRECORD_H
#define DW4_IGPSX2CLUTRECORD_H

#include "dw4/gfx/igPsx2HandlePool.h"

namespace Gap {
namespace Gfx {
class igClut;
}
}

/* One colour table of igPsx2VisualContext (an element of its _pClutList pool): the igClut it was made from, the
 * GS image the palette is uploaded as, and the palette in memory laid out the way the GS reads it. */
struct igPsx2ClutRecord {
    int entryCount;               /* colours in the table, at most 256 */
    Gap::Gfx::igClut *clut;       /* counted reference */
    int image;                    /* p2Image of the uploaded palette, 0 before the first upload */
    int layout;                   /* 0: 16 colours copied as they are, 1: 256 colours in the GS's swizzled order */
    void *palette;                /* the GS-ordered colours, allocated from the image memory pool */
    int state;                    /* 4 once uploaded, 5 once the palette texture is resident */
};

typedef igPsx2HandlePool<igPsx2ClutRecord> igPsx2ClutPool;

#endif
