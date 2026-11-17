#ifndef DW4_IGTRAVERSALVIEW_H
#define DW4_IGTRAVERSALVIEW_H

#include "dw4/reflected.h"
#include "dw4/igAttrStackManager.h"
#include "dw4/igCommonTraversalDispatchView.h"
#include "dw4/igModelViewMatrixAttr.h"
#include "dw4/igModelViewMatrixAttrDispatchView.h"
#include "dw4/igObjectPool.h"
#include "dw4/igTimeAttr.h"

/* The scene-graph traversal calls the game's node callbacks make (beCopyModelCtrl2, beCopyTransform,
 * beMeterCtrlNode, beModelCtrlNode2): the pool and attribute-stack helpers, and the two steps every
 * callback shares, taking a pooled attribute and popping the one it pushed. */

typedef void (*AttrPopProc)(void *attr, int data);

/* The next free object of a traversal's pool, which `create` grows when it is used up. */
static inline void *TakePooled(igObjectPool *pool, igObject *(*create)(int allocator)) {
    if (pool->_freeIndex >= pool->_count) {
        igObjectPool_Grow(pool, create);
    }
    int slot = pool->_freeIndex;
    pool->_freeIndex = slot + 1;
    return ((void **)pool->_data)[slot];
}

/* Pops the top attribute of the attribute stack at `index`, through the stack's pop procedure. */
static inline void PopAttr(igAttrStackManager *attrs, int index) {
    igAttrStack *top = ((igAttrStack **)((igObjectList *)attrs->_attrStacks)->_data)[index];
    int last = top->_count - 1;
    AttrPopProc pop = (AttrPopProc)top->_popProc;
    void *popped = ((void **)top->_data)[last];
    if (pop != 0) {
        pop(popped, attrs->_popProcData);
    }
    top->_count = top->_count - 1;
    igAttrStackManager_MarkStackChanged(attrs, top, index);
}

#endif
