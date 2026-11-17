#include "dw4/support/reflected.h"
#include "dw4/core/igTDataList.h"
#include "dw4/scenegraph/igCommonTraversalDispatchView.h"
#include "dw4/attrs/igModelViewMatrixAttrDispatchView.h"
#include "dw4/game/beResetNode.h"
#include "dw4/game/beMessenger.h"
#include "dw4/game/beSeCtl.h"
#include "dw4/game/beSeInfo.h"
#include "dw4/game/beSound.h"
#include "dw4/scenegraph/igAttrStackManager.h"
#include "dw4/insight/igInsightCore.h"
#include "dw4/maths/igMatrix44f.h"
#include "dw4/attrs/igModelViewMatrixAttr.h"
#include "dw4/scenegraph/igObjectPool.h"
#include "dw4/attrs/igTimeAttr.h"
#include "dw4/scenegraph/igTraversal.h"
#include <string.h>
/* kept local: its home, dw4/scenegraph/igCommonTraversal.h, is included by SceneGraph, whose load-bearing TravFunctionTable view of this symbol would conflict with a home declaration. */
extern "C" int g_igCommonTraversal_travProcs[4];
#include "dw4/support/emptyString.h"

extern "C" int beResetNode_TraverseCallback(void *node, void *traversal);
extern "C" igMetaObject *beSeCtl_GetInfoMeta(void);
extern "C" void beSeCtl_UpdateRam(void);
extern "C" igMetaObject *beSeCtl_GetMeta(void);
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
extern "C" void beSeCtl_Prepare(beSeCtl *self);
extern "C" char ACTION_BROADCAST_3[];
extern "C" void beSeCtl_OnAddRam(beSeCtl * p0, int p1, char * p2, int p3, int p4);
extern "C" char MODELCTRL_13[];
extern "C" char SETSOUND[];
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
    igObjectList *mvStack = (igObjectList *)AttrStackOps::stackFor(mgr, g_igModelViewMatrixAttr_metaObject->_id);
    igMatrix44f_SetIdentity(m);
    matAttr = 0;
    if (node->_isResetRotAndScale) {
        igMatrix44f_Copy(m, trav->_viewMat);
        int lastIdx = mvStack->_count - 1;
        igMatrix44f_GetTranslation((float *)((int *)mvStack->_data)[lastIdx] + 3, t);
        igMatrix44f_SetTranslation(m, t);
        igObjectPool *pool = (igObjectPool *)trav->_matrixPool;
        if (pool->_freeIndex >= pool->_count)
            igObjectPool_Grow(pool, (igObject *(*)(int))igModelViewMatrixAttr_CreateInstance);
        matAttr = ((igModelViewMatrixAttr **)pool->_data)[pool->_freeIndex++];
        ((igModelViewMatrixAttrDispatchView *)matAttr)->setMatrix(m);
    }
    time = 0;
    timeAttr = 0;
    if (node->_isResetTime) {
        igObjectPool *pool = (igObjectPool *)trav->_timePool;
        time = ((long long *)((igLongList *)trav->_timeStack)->_data)[0];
        if (pool->_freeIndex >= pool->_count)
            igObjectPool_Grow(pool, (igObject *(*)(int))igTimeAttr_CreateInstance);
        timeAttr = ((igTimeAttr **)pool->_data)[pool->_freeIndex++];
        timeAttr->_time = time;
    }
    if (node->_isResetTime)
        ((igCommonTraversalDispatchView *)trav)->pushTime(time);
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
    int r = igTraversal_TraverseChildren((igTraversal *)trav, (igNode *)node);
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
        ((igCommonTraversalDispatchView *)trav)->popTime();
    if (r == 2)
        return 2;
    return 0;
}

void beResetNode_RegisterTraversal(void) {
    igTraversal_RegisterFunction((igTraversalFunctionList *)g_igCommonTraversal_travProcs[0], beResetNode_GetMetaObject(), (void *)beResetNode_TraverseCallback);
}

void beSeCtl_Prepare(beSeCtl *self) {
    if (self->_sndMng == 0) {
        self->_sndMng = (int)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beSound_metaObject);
    }
}

void beSeCtl_OnAddRam(beSeCtl * p0, int p1, char * p2, int p3, int p4)
{
    beMessenger_RegisterReceiver((beMessenger *)p0->_messenger, (beBaseInfoRam *)p1, ACTION_BROADCAST_3, 0, -1);
}

igMetaObject *beSeCtl_GetInfoMeta(void)
{
    return g_beSeInfo_metaObject;
}

void beSeCtl_UpdateRam(void)
{
}

int beSeCtl_OnMessage(beSeCtl *self, beBaseInfoRam *ram, beMessengerWork *work) {
    int modelIndex;
    int modelName;
    beSeDataList *actions;
    int j;
    long long delay;
    beBaseInfoDataList *models;
    beSeInfo *info;
    beSeInfoData *model;
    int i;
    int off;
    int actionName;
    int ramNo;
    beSeData *action;
    const char *p;

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
            p = (const char *)model->_name;
            if (strcmp(p != 0 ? p : emptyString, (const char *)modelName) == 0) {
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
            p = (const char *)action->_name;
            if (strcmp(p != 0 ? p : emptyString, (const char *)actionName) == 0) {
                delay = action->_delay;
                beMessenger_SelectReceivers((beMessenger *)self->_messenger, (const char *)MODELCTRL_13, (const char *)modelName, ramNo);
                beMessenger_AppendString((beMessenger *)self->_messenger, (const char *)action->_sound);
                beMessenger_AppendFloat((beMessenger *)self->_messenger, (float)delay);
                beMessenger_DispatchSelected((beMessenger *)self->_messenger, (const char *)SETSOUND);
            }
            j += 1;
            off += 4;
        } while (j < actions->_count);
    }
    return 1;
}

igMetaObject *beSeCtl_GetMeta(void)
{
    return g_beSeCtl_metaObject;
}
