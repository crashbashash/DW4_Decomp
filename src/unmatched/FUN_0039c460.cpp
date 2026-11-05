/* 0x0039c460 - FUN_0039c460. Traversal procedure of beResetNode (registered for the node class by FUN_0039c8c0 through the
 * thunk FUN_0039c430, which swaps the two arguments). While its children are traversed it temporarily replaces the
 * traversal's model-view rotation/scale and/or time:
 *   _isResetRotAndScale: a pooled igModelViewMatrixAttr receives the traversal's view matrix with the translation of the
 *     current model-view attribute, and is pushed on the model-view attribute stack;
 *   _isResetTime: a pooled igTimeAttr takes the root time (first entry of the time stack), the traversal's time is set to it
 *     and the attribute is pushed on the time attribute stack.
 * After the children (FUN_001e07a0) both attributes are popped again and the time is restored; the result is 2 only when the
 * children asked for it.  The code has no object with a destructor, so the retail exception record is the 8-byte header only.
 * Unit profile: combat -O3,p -Iinclude (config/SLUS-20836/units.tsv row 0x0039c430).  Formerly an asm body; reproduces only under the combat -O3,p unit profile (finding #3885).*/
#include "dw4/reflected.h"
extern "C" {
void igMatrix44f_SetIdentity(float *);
void Matrix44_Copy(float *, float *);
void Matrix44_GetTranslation(float *, float *);
void Matrix44_SetTranslation(float *, float *);
void FUN_001dca40(igObjectPool *, void (*)(void));         /* pool growth, takes the instance factory */
void List_Resize(void *, int, int);
void FUN_001b1490(igAttrStackManager *, igAttrStack *, int); /* marks the attribute stack changed */
int FUN_001e07a0(igCommonTraversal *, beResetNode *);         /* traverse the children, 2 = stop */
void FUN_001356b0(void);                                      /* igModelViewMatrixAttr factory (class handle 0x55efe8) */
void FUN_00130f20(void);                                      /* igTimeAttr factory (class handle 0x55ec80) */
extern igMetaObject *DAT_0055efe8[4];                         /* igModelViewMatrixAttr meta object */
int FUN_0039c460(beResetNode *node, igCommonTraversal *trav);
}
/* virtual slots 32/33 (offsets 128/132): the matrix attribute takes the matrix; the traversal sets/ends the time */
class MatrixAttrVT { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void setMatrix(float *m); };
class TraversalVT { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void setTime(long long t); virtual void endTime(); };
struct AttrStackOps {
    static inline igAttrStack *stackFor(igAttrStackManager *mgr, int index) {
        return ((igAttrStack **)((igAttrStackList *)mgr->_attrStacks)->_data)[((int *)mgr->_attrStackIndexTable)[index]];
    }
};
int FUN_0039c460(beResetNode *node, igCommonTraversal *trav) {
    /* matching construct: the pushed attribute is written through a volatile slot (the retail code spills it to the frame and
     * reloads it for the store into the stack); the declaration order of the locals sets the frame layout */
    igAttr *volatile timeItem;
    igAttr *volatile matItem;
    float t[3];
    long long time;
    float m[16];
    igModelViewMatrixAttr *matAttr;
    igTimeAttr *timeAttr;
    igAttrStackManager *mgr = (igAttrStackManager *)trav->_attrStack;
    igObjectList *mvStack = (igObjectList *)AttrStackOps::stackFor(mgr, DAT_0055efe8[0]->_id);
    igMatrix44f_SetIdentity(m);
    matAttr = 0;
    if (node->_isResetRotAndScale) {
        Matrix44_Copy(m, trav->_viewMat);
        int lastIdx = mvStack->_count - 1;
        Matrix44_GetTranslation((float *)((int *)mvStack->_data)[lastIdx] + 3, t);
        Matrix44_SetTranslation(m, t);
        igObjectPool *pool = (igObjectPool *)trav->_matrixPool;
        if (pool->_freeIndex >= pool->_count)
            FUN_001dca40(pool, FUN_001356b0);
        matAttr = ((igModelViewMatrixAttr **)pool->_data)[pool->_freeIndex++];
        ((MatrixAttrVT *)matAttr)->setMatrix(m);
    }
    time = 0;
    timeAttr = 0;
    if (node->_isResetTime) {
        igObjectPool *pool = (igObjectPool *)trav->_timePool;
        time = ((long long *)((igLongList *)trav->_timeStack)->_data)[0];
        if (pool->_freeIndex >= pool->_count)
            FUN_001dca40(pool, FUN_00130f20);
        timeAttr = ((igTimeAttr **)pool->_data)[pool->_freeIndex++];
        timeAttr->_time = time;
    }
    if (node->_isResetTime)
        ((TraversalVT *)trav)->setTime(time);
    if (node->_isResetTime) {
        /* push timeAttr on the attribute stack of its class (stack = index table[attr id] + attr unit) */
        int idx = timeAttr->_cachedUnitID + ((int *)mgr->_attrStackIndexTable)[timeAttr->_cachedAttrIndex];
        igAttrStack *st = ((igAttrStack **)((igAttrStackList *)mgr->_attrStacks)->_data)[idx];
        timeItem = (igAttr *)timeAttr;
        int n = st->_count;
        if (n < st->_capacity)
            st->_count = *(volatile int *)&st->_count + 1; /* count is re-read: the list header is volatile-read in retail */
        else
            List_Resize(st, n + 1, 4);
        ((igAttr **)st->_data)[n] = timeItem;
        FUN_001b1490(mgr, st, idx);
    }
    if (node->_isResetRotAndScale) {
        int idx = matAttr->_cachedUnitID + ((int *)mgr->_attrStackIndexTable)[matAttr->_cachedAttrIndex];
        igAttrStack *st = ((igAttrStack **)((igAttrStackList *)mgr->_attrStacks)->_data)[idx];
        matItem = (igAttr *)matAttr;
        int n = st->_count;
        if (n < st->_capacity)
            st->_count = *(volatile int *)&st->_count + 1;
        else
            List_Resize(st, n + 1, 4);
        ((igAttr **)st->_data)[n] = matItem;
        FUN_001b1490(mgr, st, idx);
    }
    int r = FUN_001e07a0(trav, node);
    if (node->_isResetRotAndScale) {
        /* pop matAttr: run the stack's pop procedure on the top attribute, then shrink */
        int idx = matAttr->_cachedUnitID + ((int *)mgr->_attrStackIndexTable)[matAttr->_cachedAttrIndex];
        igAttrStack *st = ((igAttrStack **)((igAttrStackList *)mgr->_attrStacks)->_data)[idx];
        int last = st->_count - 1;
        igAttr *top = ((igAttr **)st->_data)[last];
        void (*popProc)(igAttr *, int) = (void (*)(igAttr *, int))st->_popProc;
        if (popProc)
            popProc(top, mgr->_popProcData);
        st->_count = st->_count - 1;
        FUN_001b1490(mgr, st, idx);
    }
    if (node->_isResetTime) {
        int idx = timeAttr->_cachedUnitID + ((int *)mgr->_attrStackIndexTable)[timeAttr->_cachedAttrIndex];
        igAttrStack *st = ((igAttrStack **)((igAttrStackList *)mgr->_attrStacks)->_data)[idx];
        int last = st->_count - 1;
        igAttr *top = ((igAttr **)st->_data)[last];
        void (*popProc)(igAttr *, int) = (void (*)(igAttr *, int))st->_popProc;
        if (popProc)
            popProc(top, mgr->_popProcData);
        st->_count = st->_count - 1;
        FUN_001b1490(mgr, st, idx);
    }
    if (node->_isResetTime)
        ((TraversalVT *)trav)->endTime();
    if (r == 2)
        return 2;
    return 0;
}
