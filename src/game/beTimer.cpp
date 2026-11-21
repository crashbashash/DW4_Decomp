#include "dw4/support/reflected.h"
#include "dw4/game/beLua.h"
#include "dw4/game/bePadManager.h"
#include "dw4/game/beSystem.h"
#include "dw4/game/beTimer.h"
#include "dw4/core/igDataLists.h"
#include "dw4/insight/igInsightCore.h"
#include "dw4/core/igObject.h"
#include <string.h>

extern "C" void beTimer_Activate(void);
extern "C" void beTimer_Deactivate(void);
extern "C" void beTimer_Stop(void);
extern "C" int beTimer_AddInfo(void);
extern "C" igMetaObject *beTimer_GetMeta(void);
extern "C" void beTimer_Start(beTimer *self);
extern "C" void beTimer_RemoveAllInfo(beTimer *self);
extern "C" int beTimer_HasPadInput(beTimer *self);
extern "C" int NOPADDATA[4];
extern "C" void beTimer_Update(beTimer *self);

void beTimer_Activate(void)
{
}

void beTimer_Deactivate(void)
{
}

void beTimer_Start(beTimer *self) {
    self->_system = (int)(igInsightCore_FindManager((igInsightCore *)self->_insight, g_beSystem_metaObject));
    self->_padManager = (int)(igInsightCore_FindManager((igInsightCore *)self->_insight, g_bePadManager_metaObject));
    self->_luaManager = (int)(igInsightCore_FindManager((igInsightCore *)self->_insight, g_beLua_metaObject));
}

void beTimer_Stop(void)
{
}

int beTimer_AddInfo(void) {
    return 0;
}

void beTimer_RemoveAllInfo(beTimer *self) {
    igObjectList *l = (igObjectList *)self->_dataList;
    int n = l->_count;
    int i;
    igObject *o;
    for (i = 0; i < n; i++) {
        o = ((igObject **)l->_data)[i];
        igObject::release(o);
    }
    {
        /* matching construct: block-local zero loop */
        int m = l->_count;
        int j;
        for (j = 0; j < m; j++) {
            ((igObject **)l->_data)[j] = 0;
        }
    }
    l->_count = 0;
}

int beTimer_HasPadInput(beTimer *self) {
    int i = 0;
    bePadData *pad;
    do {
        pad = bePadManager_GetPadForPlayer((bePadManager *)self->_padManager, i);
        /* matching construct: the double negation keeps the retail sltu/xori normalisation of the first test
         * without the bool truncation the C++ front end adds to a `!= 0` comparison */
        if (!!pad->_lStk) { return 1; }
        if (pad->_button != 0) { return 1; }
        i++;
    } while (i < 4);
    return 0;
}

void beTimer_Update(beTimer *self) {
    long long old, now, delta, nv;
    int n, i, off;
    beTimerData *it;
    beTimerDataList *l;
    bool b;
    igObject *o;
    if (((beTimerDataList *)self->_dataList)->_count != 0) {
        old = self->_oldWorldTime;
        now = ((igInsightCore *)self->_insight)->_worldTime;
        delta = now - old;
        self->_oldWorldTime = now;
        if (beSystem_IsRunning((beSystem *)self->_system) != 0) {
            n = ((beTimerDataList *)self->_dataList)->_count;
            i = 0;
            if (n > 0) {
                do {
                    off = i * 4;
                    it = ((beTimerData **)((beTimerDataList *)self->_dataList)->_data)[i];
                    if (it->_resetCondition != 0) {
                        b = strcmp((const char *)it->_resetCondition, (const char *)&NOPADDATA[0]) == 0 && beTimer_HasPadInput(self) != 0;
                        if (b) {
                            it->_downTimer = it->_startTime;
                        }
                    }
                    nv = it->_downTimer - delta;
                    it->_downTimer = nv;
                    if (nv < 0) {
                        beLua__RunNamedChunk((beLua *)self->_luaManager, (const char *)it->_callLuaFile, 0);
                        l = (beTimerDataList *)self->_dataList;
                        o = ((igObject **)l->_data)[i];
                        igObject::release(o);
                        List_RemoveWordAt((igDataList *)l, i);
                        n--;
                        i--;
                        ((int *)l->_data)[l->_count] = 0;
                    }
                    i++;
                } while (i < n);
            }
        }
    }
}

igMetaObject *beTimer_GetMeta(void)
{
    return g_beTimer_metaObject;
}
