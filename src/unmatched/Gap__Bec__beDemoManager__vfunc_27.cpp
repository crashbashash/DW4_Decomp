#include "dw4/reflected.h"
/* Runs the queued demo messages of every active work item (iterating from the back), drops
 * finished work items, then clears _disableRemoveAll and re-issues the deferred RemoveAll (vtable
 * slot 28) if it was requested meanwhile. Matching constructs: `off` is the explicit byte-offset
 * induction of the item list (the case-3 loop continues it, the case-4 loop is written with the
 * index and lets the compiler strength-reduce it; that is what keeps the hoisted `li a0,5`
 * preheader out of line); the item reads happen before the `idx >= end` test; `rn` is a local so
 * that the ramNo compare gets retail's colouring; `flag` is an unsigned char tested as `if
 * (flag)`. */
extern "C" int beMessenger_SelectReceivers(...);
extern "C" int Lua_sd_OptionalArg(...);
extern "C" int beMessenger_DispatchSelected(...);
extern "C" int beMessenger_PrepareDelayedSelection(...);
extern "C" int beMessenger_EnqueueSelected(...);
extern "C" int beMessenger_GetBoolCount(...);
extern "C" int beMessenger_GetBool(...);
extern "C" int beMessenger_GetIntCount(...);
extern "C" int beMessenger_GetInt(...);
extern "C" int beLua__RunNamedChunk(...);
extern "C" int igObject_Destroy(...);
extern "C" int List_RemoveWordAt(...);
extern int DAT_0058a1e0[4];

struct VO {
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3();
    virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11();
    virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25();
    virtual void vX();
};

#define WORK(a, i) (((beDemoManagerWork **)((beDemoManagerWorkList *)(a)->_activeDataList)->_data)[i])
#define ITEMO(a, i, o) (*((beDemoKeepMes **)((char *)((beDemoKeepMesList *)WORK(a, i)->_keepMesList)->_data + (o))))
#define ITEM(a, i, j) (((beDemoKeepMes **)((beDemoKeepMesList *)WORK(a, i)->_keepMesList)->_data)[j])

extern "C" void Gap__Bec__beDemoManager__vfunc_27(beDemoManager *arg0) {
    int n;
    int i;
    int idx;
    int end;
    int rn;
    unsigned char flag;
    beDemoKeepMes *item;
    long long delay;
    int k;
    beDemoKeepMes *it4;
    int off;
    arg0->_disableRemoveAll = 1;
    n = ((beDemoManagerWorkList *)arg0->_activeDataList)->_count;
    for (i = n - 1; i >= 0; i--) {
        idx = WORK(arg0, i)->_advancec;
        end = ((beDemoKeepMesList *)WORK(arg0, i)->_keepMesList)->_count;
        flag = 0;
        for (; idx < end; idx++) {
            off = idx * 4;
            item = ITEMO(arg0, i, off);
            switch (item->_kind) {
            case 0: case 1: case 2: case 3:
                delay = item->_sendTime;
                if (delay <= 0) {
                    beMessenger_SelectReceivers(arg0->_messenger, item->_groupName, item->_infoName, item->_ramNo);
                    if (item->_mesParam != 0) Lua_sd_OptionalArg(item->_mesParam);
                    beMessenger_DispatchSelected(arg0->_messenger, item->_message);
                } else {
                    beMessenger_PrepareDelayedSelection(arg0->_messenger, item->_groupName, item->_infoName, item->_ramNo);
                    if (item->_mesParam != 0) Lua_sd_OptionalArg(item->_mesParam);
                    beMessenger_EnqueueSelected(arg0->_messenger, item->_message, delay);
                }
                switch (item->_kind) {
                case 1:
                    if (beMessenger_GetBoolCount(arg0->_messenger) == 0) flag = 1;
                    else if ((beMessenger_GetBool(arg0->_messenger, 0) & 0xff) != 1) flag = 1;
                    break;
                case 2:
                    if (beMessenger_GetBoolCount(arg0->_messenger) == 0) flag = 1;
                    else if ((beMessenger_GetBool(arg0->_messenger, 0) & 0xff) != 0) flag = 1;
                    break;
                case 3:
                    if (beMessenger_GetIntCount(arg0->_messenger) != 0) {
                        while (idx < end) {
                            idx++;
                            off += 4;
                            beDemoKeepMes *it2 = ITEMO(arg0, i, off);
                            if (idx >= end) break;
                            if (it2->_kind == 4) {
                                rn = it2->_ramNo;
                                if (rn == beMessenger_GetInt(arg0->_messenger, 0)) break;
                            } else if (it2->_kind == 5) break;
                        }
                    }
                    break;
                }
                break;
            case 4:
                while (idx < end) {
                    idx++;
                    it4 = ITEM(arg0, i, idx);
                    if (idx >= end) break;
                    if (it4->_kind == 5) break;
                }
                break;
            case 7:
                DAT_0058a1e0[0] = 0;
                beLua__RunNamedChunk(arg0->_lua, item->_mesParam, 0);
                break;
            }
            if (flag) break;
        }
        WORK(arg0, i)->_advancec = idx;
    }
    for (k = n - 1; k >= 0; k--) {
        beDemoManagerWorkList *l = (beDemoManagerWorkList *)arg0->_activeDataList;
        beDemoManagerWork *w = ((beDemoManagerWork **)l->_data)[k];
        if (w->_advancec < ((beDemoKeepMesList *)w->_keepMesList)->_count) continue;
        if (w != 0) {
            w->_refCount = (int)w->_refCount - 1;
            if (((unsigned long long)((long long)(int)w->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(w);
        }
        List_RemoveWordAt(l, k);
        ((int *)l->_data)[l->_count] = 0;
    }
    arg0->_disableRemoveAll = 0;
    if (arg0->_calledRemoveAll != 0) ((VO *)arg0)->vX();
}
