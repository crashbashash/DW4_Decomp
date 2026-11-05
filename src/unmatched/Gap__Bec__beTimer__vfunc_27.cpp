#include "dw4/reflected.h"
extern "C" {
void igObject_Destroy(igObject *);
int beLua__RunNamedChunk(...);
int FUN_003a0540(...);
int FUN_003a54a0(...);
int List_RemoveWordAt(...);
int igStrCmp(...);
extern int DAT_0050ff10[4];
}
extern "C" void Gap__Bec__beTimer__vfunc_27(beTimer *arg0);
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
        if (FUN_003a0540(arg0->_system) & 0xFF) {
            n = ((beTimerDataList *)arg0->_dataList)->_count;
            i = 0;
            if (n > 0) {
                do {
                    off = i * 4;
                    it = ((beTimerData **)((beTimerDataList *)arg0->_dataList)->_data)[i];
                    if (it->_resetCondition != 0) {
                        b = igStrCmp(it->_resetCondition, &DAT_0050ff10[0]) == 0 && FUN_003a54a0(arg0) != 0;
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
