#ifndef DW4_IGPSX2RENDERLIST_H
#define DW4_IGPSX2RENDERLIST_H

#include "dw4/gfx/igPsx2HandlePool.h"

namespace Gap {
namespace Core {
class igIntList;
}
namespace Gfx {
class igPsx2VertexArray1_1;
}
}

/* One render list of igPsx2VisualContext (its _pDLists pool holds a pointer to each): the p2 display lists recorded
 * between beginRenderListDraw and endRenderListDraw, and the vertex array they were compiled against, which
 * executeRenderList's validation compares with the current one. */
struct igPsx2RenderList {
    Gap::Core::igIntList *displayLists;            /* counted reference; each element a p2DisplayList */
    Gap::Gfx::igPsx2VertexArray1_1 *vertexArray;

    igPsx2RenderList() {
        displayLists = 0;
        vertexArray = 0;
    }
    static void *operator new(unsigned size, igMemoryPoolView *pool) { return Memory_AllocateBufferDirect(size, pool); }
};

typedef igPsx2HandlePool<igPsx2RenderList *> igPsx2RenderListPool;

#endif
