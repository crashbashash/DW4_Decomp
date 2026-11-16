#ifndef DW4_IGTRAVERSALVIEW_H
#define DW4_IGTRAVERSALVIEW_H

#include "dw4/reflected.h"

/* The scene-graph traversal calls the game's node callbacks make (beCopyModelCtrl2, beCopyTransform,
 * beMeterCtrlNode, beModelCtrlNode2): the classes seen through the slots those callbacks call, the
 * pool and attribute-stack helpers, and the two steps every callback shares, taking a pooled attribute
 * and popping the one it pushed. The dummies place each named slot at its retail position. */

/* igModelViewMatrixAttr: slot 30 stores the matrix. */
class ModelViewMatrixAttrView {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
    virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void setMatrix(void *matrix);
};

/* igCommonTraversal: slot 24 reads the traversal's time, slot 30 takes the time a subtree runs at,
 * slot 31 drops it again. */
class CommonTraversalView {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual long long getTime();
    virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void pushTime(long long time);
    virtual void popTime();
};

typedef void (*AttrPopProc)(void *attr, int data);

extern "C" int igAttrStackManager_MarkStackChanged(igAttrStackManager *manager, igAttrStack *stack, int index);
extern "C" int igObjectPool_Grow(igObjectPool *pool, void *create);
extern "C" int igModelViewMatrixAttr_CreateInstance(...);
extern "C" int igTimeAttr_CreateInstance(...);

/* The next free object of a traversal's pool, which `create` grows when it is used up. */
static inline void *TakePooled(igObjectPool *pool, void *create) {
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
