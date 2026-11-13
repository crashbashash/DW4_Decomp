#include "dw4/reflected.h"

extern "C" void Gap__Bec__beTimer__vfunc_21(void);
extern "C" void Gap__Bec__beTimer__vfunc_22(void);
extern "C" void Gap__Bec__beTimer__vfunc_24(void);
extern "C" int Gap__Bec__beTimer__vfunc_25(void);
extern "C" int Gap__Bec__beTimer__vfunc_20(void);
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
extern "C" void Gap__Bec__beTimer__vfunc_23(beTimer *arg0);
extern "C" void Gap__Bec__beTimer__vfunc_26(beTimer *arg0);
struct Pad { char pad[36]; int f36; char p2[28]; int f68; };
struct O { char pad[20]; int f20; };
extern "C" struct Pad *bePadManager_GetPadForPlayer(int, int);
extern "C" int FUN_003a54a0(struct O *arg0);
extern "C" int NOPADDATA[4];
extern "C" void Gap__Bec__beTimer__vfunc_27(beTimer *arg0);

void Gap__Bec__beTimer__vfunc_21(void)
{
}

void Gap__Bec__beTimer__vfunc_22(void)
{
}

void Gap__Bec__beTimer__vfunc_23(beTimer *arg0) {
    arg0->_system = igInsightCore_FindManager(arg0->_insight, g_beSystem_metaObject[0]);
    arg0->_padManager = igInsightCore_FindManager(arg0->_insight, g_bePadManager_metaObject[0]);
    arg0->_luaManager = igInsightCore_FindManager(arg0->_insight, g_beLua_metaObject[0]);
}

void Gap__Bec__beTimer__vfunc_24(void)
{
}

int Gap__Bec__beTimer__vfunc_25(void) {
    return 0;
}

void Gap__Bec__beTimer__vfunc_26(beTimer *arg0) {
    igObjectList *l = (igObjectList *)arg0->_dataList;
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

int FUN_003a54a0(struct O *arg0) {
    int i = 0;
    struct Pad *p;
    int z;
    do {
        p = bePadManager_GetPadForPlayer(arg0->f20, i);
        /* matching construct: the double negation keeps the retail sltu/xori normalisation of the first test
         * without the bool truncation the C++ front end adds to a `!= 0` comparison */
        if (!!p->f36) { return 1; }
        if (p->f68 != 0) { return 1; }
        i++;
    } while (i < 4);
    return 0;
}

void Gap__Bec__beTimer__vfunc_27(beTimer *arg0) {
    long long old, now, delta, nv;
    int n, i, off;
    beTimerData *it;
    beTimerDataList *l;
    bool b;
    igObject *o;
    if (((beTimerDataList *)arg0->_dataList)->_count != 0) {
        old = arg0->_oldWorldTime;
        now = ((igInsightCore *)arg0->_insight)->_worldTime;
        delta = now - old;
        arg0->_oldWorldTime = now;
        if (beSystem_IsRunning(arg0->_system) & 0xFF) {
            n = ((beTimerDataList *)arg0->_dataList)->_count;
            i = 0;
            if (n > 0) {
                do {
                    off = i * 4;
                    it = ((beTimerData **)((beTimerDataList *)arg0->_dataList)->_data)[i];
                    if (it->_resetCondition != 0) {
                        b = strcmp(it->_resetCondition, &NOPADDATA[0]) == 0 && FUN_003a54a0((O *)arg0) != 0;
                        if (b) {
                            it->_downTimer = it->_startTime;
                        }
                    }
                    nv = it->_downTimer - delta;
                    it->_downTimer = nv;
                    if (nv < 0) {
                        beLua__RunNamedChunk(arg0->_luaManager, it->_callLuaFile, 0);
                        l = (beTimerDataList *)arg0->_dataList;
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

int Gap__Bec__beTimer__vfunc_20(void)
{
    return g_beTimer_metaObject[0];
}
