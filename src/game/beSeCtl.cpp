#include "dw4/reflected.h"
#include "dw4/igTDataList.h"

extern "C" int beResetNode_TraverseCallback(void *node, void *traversal);
extern "C" void igMatrix44f_SetIdentity(float *);
extern "C" void igMatrix44f_Copy(float *, float *);
extern "C" void igMatrix44f_GetTranslation(float *, float *);
extern "C" void igMatrix44f_SetTranslation(float *, float *);
extern "C" void igModelViewMatrixAttr_CreateInstance(void);
extern "C" void igTimeAttr_CreateInstance(void);
extern "C" int igTraversal_RegisterFunction(int, int, void (*)(void));
extern "C" int beResetNode_GetMetaObject(...);
extern "C" void beResetNode_RegisterTraversal(void);
extern "C" int igInsightCore_FindManager(int, int);
extern "C" void beMessenger_RegisterReceiver(int, int, char *, int, int);
extern "C" int beSeCtl_GetInfoMeta(void);
extern "C" void beSeCtl_UpdateRam(void);
extern "C" int beSeCtl_GetMeta(void);
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
extern "C" int beResetNode_Traverse(beResetNode *node, igCommonTraversal *trav);
extern "C" int g_igCommonTraversal_travProcs[4];
extern "C" int g_beSound_metaObject[4];
extern "C" void beSeCtl_Prepare(beSeCtl *self);
extern "C" char ACTION_BROADCAST_3[];
extern "C" void beSeCtl_OnAddRam(beSeCtl * p0, int p1, char * p2, int p3, int p4);
extern "C" int g_beSeInfo_metaObject[4];
extern "C" int g_beSeCtl_metaObject[4];
extern "C" int emptyString[4];
extern "C" int MODELCTRL_13[4];
extern "C" int SETSOUND[4];
extern "C" int beSeCtl_OnMessage(beSeCtl *self, beBaseInfoRam *ram, beMessengerWork *work);

int beResetNode_TraverseCallback(void *node, void *traversal) {
    return beResetNode_Traverse((beResetNode *)traversal, (igCommonTraversal *)node);
}

int beResetNode_Traverse(beResetNode *node, igCommonTraversal *trav) {
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
        igMatrix44f_Copy(m, trav->_viewMat);
        int lastIdx = mvStack->_count - 1;
        igMatrix44f_GetTranslation((float *)((int *)mvStack->_data)[lastIdx] + 3, t);
        igMatrix44f_SetTranslation(m, t);
        igObjectPool *pool = (igObjectPool *)trav->_matrixPool;
        if (pool->_freeIndex >= pool->_count)
            igObjectPool_Grow(pool, igModelViewMatrixAttr_CreateInstance);
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

void beResetNode_RegisterTraversal(void) {
    igTraversal_RegisterFunction(g_igCommonTraversal_travProcs[0], beResetNode_GetMetaObject(), (void (*)())beResetNode_TraverseCallback);
}

void beSeCtl_Prepare(beSeCtl *self) {
    if (self->_sndMng == 0) {
        self->_sndMng = igInsightCore_FindManager(self->_insight, g_beSound_metaObject[0]);
    }
}

void beSeCtl_OnAddRam(beSeCtl * p0, int p1, char * p2, int p3, int p4)
{
    beMessenger_RegisterReceiver(p0->_messenger, p1, ACTION_BROADCAST_3, 0, -1);
}

int beSeCtl_GetInfoMeta(void)
{
    return g_beSeInfo_metaObject[0];
}

void beSeCtl_UpdateRam(void)
{
}

int beSeCtl_OnMessage(beSeCtl *self, beBaseInfoRam *ram, beMessengerWork *work) {
    int modelIndex;
    int modelName;
    beSeDataList *actions;
    int j;
    int delay;
    beBaseInfoDataList *models;
    beSeInfo *info;
    beSeInfoData *model;
    int i;
    int off;
    int actionName;
    int ramNo;
    beSeData *action;
    int *p;

    modelIndex = -1;
    actionName = work->_message;
    modelName = work->_infoName;
    ramNo = work->_ramNo;
    info = (beSeInfo *)ram->_parentInfo;
    models = (beBaseInfoDataList *)info->_dataList;
    i = 0;
    if (0 < models->_count) {
        off = 0;
        do {
            model = (beSeInfoData *)*(int *)((char *)models->_data + off);
            p = (int *)model->_name;
            if (strcmp(p != 0 ? p : &emptyString[0], modelName) == 0) {
                modelIndex = i;
            }
            i += 1;
            off += 4;
        } while (i < models->_count);
    }
    if (modelIndex == -1) {
        return 1;
    }
    model = ((beSeInfoData **)models->_data)[modelIndex];
    actions = (beSeDataList *)model->_actionList;
    j = 0;
    if (0 < actions->_count) {
        off = 0;
        do {
            action = *(beSeData **)((char *)actions->_data + off);
            p = (int *)action->_name;
            if (strcmp(p != 0 ? p : &emptyString[0], actionName) == 0) {
                delay = action->_delay;
                beMessenger_SelectReceivers(self->_messenger, &MODELCTRL_13[0], modelName, ramNo);
                beMessenger_AppendString(self->_messenger, action->_sound);
                beMessenger_AppendFloat(self->_messenger, __floatdisf(delay));
                beMessenger_DispatchSelected(self->_messenger, &SETSOUND[0]);
            }
            j += 1;
            off += 4;
        } while (j < actions->_count);
    }
    return 1;
}

int beSeCtl_GetMeta(void)
{
    return g_beSeCtl_metaObject[0];
}
