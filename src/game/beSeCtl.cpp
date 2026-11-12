#include "dw4/reflected.h"
#include "dw4/igTDataList.h"

extern "C" int FUN_0039c430(void *node, void *traversal);
extern "C" void igMatrix44f_SetIdentity(float *);
extern "C" void Matrix44_Copy(float *, float *);
extern "C" void Matrix44_GetTranslation(float *, float *);
extern "C" void Matrix44_SetTranslation(float *, float *);
extern "C" void FUN_001356b0(void);
extern "C" void igTimeAttr_CreateInstance(void);
extern "C" int igTraversal_RegisterFunction(int, int, void (*)(void));
extern "C" int FUN_0034b4a0(...);
extern "C" void FUN_0039c8c0(void);
extern "C" int FUN_00236f80(int, int);
extern "C" void beMessenger_RegisterReceiver(int, int, char *, int, int);
extern "C" int Gap__Bec__beSeCtl__vfunc_30(void);
extern "C" void Gap__Bec__beSeCtl__vfunc_31(void);
extern "C" int Gap__Bec__beSeCtl__vfunc_20(void);
extern "C" float __floatdisf(int);
extern "C" int beMessenger_AppendFloat(int, float);
extern "C" int beMessenger_AppendString(int, int);
extern "C" int beMessenger_DispatchSelected(int, int *);
extern "C" int beMessenger_SelectReceivers(int, int *, int, int);
extern "C" int strcmp(int *, int);
extern "C" void igObjectPool_Grow(igObjectPool *, void (*)(void));
extern "C" void igAttrStackManager_MarkStackChanged(igAttrStackManager *, igAttrStack *, int);
extern "C" int igTraversal_TraverseChildren(igCommonTraversal *, beResetNode *);
extern "C" igMetaObject *g_igModelViewMatrixAttr_metaObject[4];
/* virtual slots 32/33 (offsets 128/132): the matrix attribute takes the matrix; the traversal sets/ends the time */
class MatrixAttrVT { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void setMatrix(float *m); };
class TraversalVT { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void setTime(long long t); virtual void endTime(); };
struct AttrStackOps {
    static inline igAttrStack *stackFor(igAttrStackManager *mgr, int index) {
        return ((igAttrStack **)((igAttrStackList *)mgr->_attrStacks)->_data)[((int *)mgr->_attrStackIndexTable)[index]];
    }
};
struct AttrList : igTDataList<igAttr *> {
    void append(igAttr *value) {
        int n = count();
        if (n < _capacity)
            _count = _count + 1;
        else
            List_Resize(this, n + 1, 4);
        igAttr *const *p = &value;
        _data[n] = *p;
    }
};
extern "C" int FUN_0039c460(beResetNode *node, igCommonTraversal *trav);
extern "C" int DAT_00562640[4];
extern "C" int g_beSound_metaObject[4];
extern "C" void Gap__Bec__beSeCtl__vfunc_32(beSeCtl *arg0);
extern "C" char DAT_0050f760[];
extern "C" void Gap__Bec__beSeCtl__vfunc_29(beSeCtl * p0, int p1, char * p2, int p3, int p4);
extern "C" int g_beSeInfo_metaObject[4];
extern "C" int g_beSeCtl_metaObject[4];
extern "C" int emptyString[4];
extern "C" int DAT_0050f778[4];
extern "C" int DAT_0050f788[4];
/* arg1 context: +12 holds the owning info. */
struct ContextView { char p[12]; int f12; };
/* arg2 message record: +12 model name, +16 slot, +20 action name */
struct SeMessageView { char p[12]; int f12; int f16; int f20; };
extern "C" int Gap__Bec__beSeCtl__vfunc_34(beSeCtl *arg0, struct ContextView *arg1, struct SeMessageView *arg2);

int FUN_0039c430(void *node, void *traversal) {
    return FUN_0039c460((beResetNode *)traversal, (igCommonTraversal *)node);
}

int FUN_0039c460(beResetNode *node, igCommonTraversal *trav) {
    float t[3];
    long long time;
    float m[16];
    igModelViewMatrixAttr *matAttr;
    igTimeAttr *timeAttr;
    igAttrStackManager *mgr = (igAttrStackManager *)trav->_attrStack;
    igObjectList *mvStack = (igObjectList *)AttrStackOps::stackFor(mgr, g_igModelViewMatrixAttr_metaObject[0]->_id);
    igMatrix44f_SetIdentity(m);
    matAttr = 0;
    if (node->_isResetRotAndScale) {
        Matrix44_Copy(m, trav->_viewMat);
        int lastIdx = mvStack->_count - 1;
        Matrix44_GetTranslation((float *)((int *)mvStack->_data)[lastIdx] + 3, t);
        Matrix44_SetTranslation(m, t);
        igObjectPool *pool = (igObjectPool *)trav->_matrixPool;
        if (pool->_freeIndex >= pool->_count)
            igObjectPool_Grow(pool, FUN_001356b0);
        matAttr = ((igModelViewMatrixAttr **)pool->_data)[pool->_freeIndex++];
        ((MatrixAttrVT *)matAttr)->setMatrix(m);
    }
    time = 0;
    timeAttr = 0;
    if (node->_isResetTime) {
        igObjectPool *pool = (igObjectPool *)trav->_timePool;
        time = ((long long *)((igLongList *)trav->_timeStack)->_data)[0];
        if (pool->_freeIndex >= pool->_count)
            igObjectPool_Grow(pool, igTimeAttr_CreateInstance);
        timeAttr = ((igTimeAttr **)pool->_data)[pool->_freeIndex++];
        timeAttr->_time = time;
    }
    if (node->_isResetTime)
        ((TraversalVT *)trav)->setTime(time);
    if (node->_isResetTime) {
        /* push timeAttr on the attribute stack of its class (stack = index table[attr id] + attr unit) */
        int idx = timeAttr->_cachedUnitID + ((int *)mgr->_attrStackIndexTable)[timeAttr->_cachedAttrIndex];
        igAttrStack *st = ((igAttrStack **)((igAttrStackList *)mgr->_attrStacks)->_data)[idx];
        ((AttrList *)st)->append((igAttr *)timeAttr);
        igAttrStackManager_MarkStackChanged(mgr, st, idx);
    }
    if (node->_isResetRotAndScale) {
        int idx = matAttr->_cachedUnitID + ((int *)mgr->_attrStackIndexTable)[matAttr->_cachedAttrIndex];
        igAttrStack *st = ((igAttrStack **)((igAttrStackList *)mgr->_attrStacks)->_data)[idx];
        ((AttrList *)st)->append((igAttr *)matAttr);
        igAttrStackManager_MarkStackChanged(mgr, st, idx);
    }
    int r = igTraversal_TraverseChildren(trav, node);
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
        igAttrStackManager_MarkStackChanged(mgr, st, idx);
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
        igAttrStackManager_MarkStackChanged(mgr, st, idx);
    }
    if (node->_isResetTime)
        ((TraversalVT *)trav)->endTime();
    if (r == 2)
        return 2;
    return 0;
}

void FUN_0039c8c0(void) {
    igTraversal_RegisterFunction(DAT_00562640[0], FUN_0034b4a0(), (void (*)())FUN_0039c430);
}

void Gap__Bec__beSeCtl__vfunc_32(beSeCtl *arg0) {
    if (arg0->_sndMng == 0) {
        arg0->_sndMng = FUN_00236f80(arg0->_insight, g_beSound_metaObject[0]);
    }
}

void Gap__Bec__beSeCtl__vfunc_29(beSeCtl * p0, int p1, char * p2, int p3, int p4)
{
    beMessenger_RegisterReceiver(p0->_messenger, p1, DAT_0050f760, 0, -1);
}

int Gap__Bec__beSeCtl__vfunc_30(void)
{
    return g_beSeInfo_metaObject[0];
}

void Gap__Bec__beSeCtl__vfunc_31(void)
{
}

int Gap__Bec__beSeCtl__vfunc_34(beSeCtl *arg0, struct ContextView *arg1, struct SeMessageView *arg2) {
    int res;
    int s5;
    beSeDataList *l2;
    int j;
    int sh;
    beBaseInfoDataList *l1;
    beSeInfo *info;
    beSeInfoData *row;
    int i;
    int off;
    int s7;
    int s8;
    beSeData *it;
    int *p;

    res = -1;
    s7 = arg2->f20;
    s5 = arg2->f12;
    s8 = arg2->f16;
    info = (beSeInfo *)arg1->f12;
    l1 = (beBaseInfoDataList *)info->_dataList;
    i = 0;
    if (0 < l1->_count) {
        off = 0;
        do {
            row = (beSeInfoData *)*(int *)((char *)l1->_data + off);
            p = (int *)row->_name;
            if (strcmp(p != 0 ? p : &emptyString[0], s5) == 0) {
                res = i;
            }
            i += 1;
            off += 4;
        } while (i < l1->_count);
    }
    if (res == -1) {
        return 1;
    }
    row = ((beSeInfoData **)l1->_data)[res];
    l2 = (beSeDataList *)row->_actionList;
    j = 0;
    if (0 < l2->_count) {
        off = 0;
        do {
            it = *(beSeData **)((char *)l2->_data + off);
            p = (int *)it->_name;
            if (strcmp(p != 0 ? p : &emptyString[0], s7) == 0) {
                sh = it->_delay;
                beMessenger_SelectReceivers(arg0->_messenger, &DAT_0050f778[0], s5, s8);
                beMessenger_AppendString(arg0->_messenger, it->_sound);
                beMessenger_AppendFloat(arg0->_messenger, __floatdisf(sh));
                beMessenger_DispatchSelected(arg0->_messenger, &DAT_0050f788[0]);
            }
            j += 1;
            off += 4;
        } while (j < l2->_count);
    }
    return 1;
}

int Gap__Bec__beSeCtl__vfunc_20(void)
{
    return g_beSeCtl_metaObject[0];
}
