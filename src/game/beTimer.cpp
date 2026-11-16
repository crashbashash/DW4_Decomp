#include "dw4/reflected.h"

extern "C" void beTimer_Activate(void);
extern "C" void beTimer_Deactivate(void);
extern "C" void beTimer_Stop(void);
extern "C" int beTimer_AddInfo(void);
extern "C" int beTimer_GetMeta(void);
extern "C" int igInsightCore_FindManager(int, int);
extern "C" int igObject_Destroy(...);
extern "C" int beLua__RunNamedChunk(...);
extern "C" int beSystem_IsRunning(...);
extern "C" int List_RemoveWordAt(...);
extern "C" int strcmp(...);
extern "C" int g_beTimer_metaObject[4];
extern "C" int g_beSystem_metaObject[4];
extern "C" int g_bePadManager_metaObject[4];
extern "C" int g_beLua_metaObject[4];
extern "C" void beTimer_Start(beTimer *self);
extern "C" void beTimer_RemoveAllInfo(beTimer *self);
extern "C" bePadData *bePadManager_GetPadForPlayer(int padManager, int player);
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
    self->_system = igInsightCore_FindManager(self->_insight, g_beSystem_metaObject[0]);
    self->_padManager = igInsightCore_FindManager(self->_insight, g_bePadManager_metaObject[0]);
    self->_luaManager = igInsightCore_FindManager(self->_insight, g_beLua_metaObject[0]);
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
        if (o != 0) {
            o->_refCount = (int)o->_refCount - 1;
            if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
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
        pad = bePadManager_GetPadForPlayer(self->_padManager, i);
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
        if (beSystem_IsRunning(self->_system) & 0xFF) {
            n = ((beTimerDataList *)self->_dataList)->_count;
            i = 0;
            if (n > 0) {
                do {
                    off = i * 4;
                    it = ((beTimerData **)((beTimerDataList *)self->_dataList)->_data)[i];
                    if (it->_resetCondition != 0) {
                        b = strcmp(it->_resetCondition, &NOPADDATA[0]) == 0 && beTimer_HasPadInput(self) != 0;
                        if (b) {
                            it->_downTimer = it->_startTime;
                        }
                    }
                    nv = it->_downTimer - delta;
                    it->_downTimer = nv;
                    if (nv < 0) {
                        beLua__RunNamedChunk(self->_luaManager, it->_callLuaFile, 0);
                        l = (beTimerDataList *)self->_dataList;
                        o = ((igObject **)l->_data)[i];
                        if (o != 0) {
                            o->_refCount = o->_refCount - 1;
                            if (((unsigned long long)((long long)o->_refCount & 0x7fffffULL)) == 0) {
                                igObject_Destroy(o);
                            }
                        }
                        List_RemoveWordAt(l, i);
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

int beTimer_GetMeta(void)
{
    return g_beTimer_metaObject[0];
}
