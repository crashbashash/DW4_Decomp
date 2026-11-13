#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#define POOL(v) if (g_stringPool[0] == 0) { v = StringPool_Allocate(16); if (v != 0) v = StringPool_Construct(v); g_stringPool[0] = v; }
#define SETSTR(fld, arg) { int *nw; beDemoKeepMes *c = e.p; POOL(v) nw = (int *)((void *)StringPool_Intern(g_stringPool[0], arg)); old = (int *)c->fld; if (old != 0) { hd = old - 2; r = old[-1] - 1; old[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*hd, hd); } c->fld = (int)nw; }
#define WORK(a, i) (((beDemoManagerWork **)((beDemoManagerWorkList *)(a)->_activeDataList)->_data)[i])
#define ITEMO(a, i, o) (*((beDemoKeepMes **)((char *)((beDemoKeepMesList *)WORK(a, i)->_keepMesList)->_data + (o))))
#define ITEM(a, i, j) (((beDemoKeepMes **)((beDemoKeepMesList *)WORK(a, i)->_keepMesList)->_data)[j])

extern "C" int Memory_GetAllocatorBySelector(int);
extern "C" int ObjectList_AppendRetained(...);
extern "C" int igObject_GetAllocator(...);
extern "C" int StringPool_Allocate(int);
extern "C" int StringPool_Construct(int);
extern "C" void StringChunk_ReleaseHeader(...);
extern "C" char * StringPool_Intern(...);
extern "C" int igInsightCore_FindManager(int, int);
extern "C" void Gap__Bec__beDemoManager__vfunc_24(void);
extern "C" int Gap__Bec__beDemoManager__vfunc_25(void);
extern "C" int Gap__Bec__beDemoManager__vfunc_20(void);
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
extern "C" int List_RemoveWordAt(...);
extern "C" void FUN_0037e110(beDemoManager *arg0, int arg1, int arg2, int arg3, int arg4, int arg5);
extern "C" beDemoKeepMes * FUN_00363c20(...);
extern "C" int g_defaultAllocatorSelector[4];
extern "C" unsigned char GPR_00554c14;
extern "C" void FUN_0037e180(beDemoManager *a0);
extern "C" void FUN_0037e2d0(beDemoManager *a0, int ramNo);
extern "C" int g_stringPool[4];
extern "C" void FUN_0037e3a0(beDemoManager *self, int a1, int a2, int a3, int t0, int t1, int t2, long long t3);
extern "C" beDemoManagerWork * FUN_003637c0(...);
extern "C" void FUN_0037e6e0(beDemoManager *arg0, int arg1);
extern "C" void FUN_0037e890(beDemoManager *arg0, int arg1, int arg2);
extern "C" void FUN_0037ea50(beDemoManager *arg0);
extern "C" void igInsightCore_AddToScheduler(int, beDemoManager *);
extern "C" void igInsightCore_RemoveFromScheduler(int, beDemoManager *);
extern "C" void Gap__Bec__beDemoManager__vfunc_21(beDemoManager *self, int unusedArg);
extern "C" void Gap__Bec__beDemoManager__vfunc_22(beDemoManager *self, int unusedArg);
extern "C" int g_beMessenger_metaObject[4];
extern "C" int g_beLua_metaObject[4];
extern "C" void Gap__Bec__beDemoManager__vfunc_23(beDemoManager *arg0);
extern "C" int g_beDemoManager_metaObject[4];
extern "C" int List_Reserve(igObjectList *, int, int);
extern "C" void Gap__Bec__beDemoManager__vfunc_26(beDemoManager *arg0);
extern "C" int g_mdlEntity[4];
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
extern "C" void Gap__Bec__beDemoManager__vfunc_27(beDemoManager *arg0);

void FUN_0037e110(beDemoManager *arg0, int arg1, int arg2, int arg3, int arg4, int arg5) {
    if (arg0->_turningOK == 0) {
        arg0->_turningOK = 1;
    } else {
        return;
    }
    FUN_0037e3a0(arg0, 3, arg1, arg2, arg3, arg4, arg5, (long long)0);
}

/* Owning stack reference to a keep-message; its destructor releases the object (reference count in
 * the low 23 bits of _refCount). */

void FUN_0037e180(beDemoManager *a0) {
    beDemoManagerWork *l;
    int al;
    if (a0->_buildData != 0) {
        if (a0->_turningOK == 1) {
            a0->_turningOK = 0;
        } else {
            return;
        }
        {
            l = (beDemoManagerWork *)a0->_buildData;
            al = igObject_GetAllocator(a0);
            al = GPR_00554c14 ? al : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
            igSmartPointer<beDemoKeepMes> mes(FUN_00363c20(al));
            mes.p->_kind = 5;
            ObjectList_AppendRetained(l->_keepMesList, mes.p);
        }
    }
}

/* Owning stack reference to a keep-message; its destructor releases the object (reference count in
 * the low 23 bits of _refCount). */

void FUN_0037e2d0(beDemoManager *a0, int ramNo) {
    beDemoManagerWork *l;
    int al;

    l = (beDemoManagerWork *)a0->_buildData;
    if ((l != 0) && (a0->_turningOK != 0)) {
        al = igObject_GetAllocator(a0);
        al = GPR_00554c14 ? al : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        igSmartPointer<beDemoKeepMes> mes(FUN_00363c20(al));
        mes.p->_kind = 4;
        mes.p->_ramNo = ramNo;
        ObjectList_AppendRetained(l->_keepMesList, mes.p);
    }
}

void FUN_0037e3a0(beDemoManager *self, int a1, int a2, int a3, int t0, int t1, int t2, long long t3) {
    int v;
    beDemoManagerWork *q;
    beDemoManagerWork *q2;
    int *old;
    int *hd;
    int r;
    if (self->_buildData == 0) {
        v = igObject_GetAllocator(self);
        v = (GPR_00554c14 != 0) ? v : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        q = (beDemoManagerWork *)self->_buildData;
        if (q != 0) {
            q->_refCount = q->_refCount - 1;
            if ((q->_refCount & 0x7fffff) == 0) igObject_Destroy(q);
        }
        self->_buildData = (int)FUN_003637c0(v);
        self->_turningOK = 0;
    }
    q2 = (beDemoManagerWork *)self->_buildData;
    v = igObject_GetAllocator(self);
    v = (GPR_00554c14 != 0) ? v : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
    /* matching construct: the holder is declared after the allocation call returns, so retail's protected range starts after the allocator and not at it */
    beDemoKeepMes *k = (beDemoKeepMes *)((void *)FUN_00363c20(v));
    igSmartPointer<beDemoKeepMes> e(k);
    e.p->_kind = a1;
    e.p->_sendTime = t3;
    SETSTR(_groupName, a2)
    SETSTR(_infoName, a3)
    e.p->_ramNo = t0;
    SETSTR(_message, t1)
    SETSTR(_mesParam, t2)
    ObjectList_AppendRetained((void *)q2->_keepMesList, e.p);
}

/* Owning stack reference to a keep-message; its destructor releases the object (reference count in
 * the low 23 bits of _refCount). */

void FUN_0037e6e0(beDemoManager *arg0, int arg1) {
    beDemoManagerWork *l;
    beDemoKeepMes *s1;
    beDemoManagerWork *old;
    int var_v0;
    int key;
    int *temp_v1;
    int temp_v0;
    int var_v0_2;
    int *temp_a1;
    int var_v0_3;

    key = arg1;
    if (arg0->_buildData == 0) {
        var_v0_3 = igObject_GetAllocator(arg0);
        if (GPR_00554c14 != 0) {
            var_v0_3 = (int)var_v0_3;
        } else {
            var_v0_3 = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        }
        old = (beDemoManagerWork *)arg0->_buildData;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(old);
            }
        }
        arg0->_buildData = (int)FUN_003637c0(var_v0_3);
        arg0->_turningOK = 0;
    }
    l = (beDemoManagerWork *)arg0->_buildData;
    var_v0 = igObject_GetAllocator(arg0);
    if (GPR_00554c14 != 0) {
        var_v0 = (int)var_v0;
    } else {
        var_v0 = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
    }
    igSmartPointer<beDemoKeepMes> mes(FUN_00363c20(var_v0));
    mes.p->_kind = 7;
    s1 = mes.p;
    if (g_stringPool[0] == 0) {
        var_v0_2 = StringPool_Allocate(0x10);
        if (var_v0_2 != 0) {
            var_v0_2 = StringPool_Construct(var_v0_2);
        }
        g_stringPool[0] = var_v0_2;
    }
    key = (int)StringPool_Intern(g_stringPool[0], key);
    temp_v1 = (int *)s1->_mesParam;
    if (temp_v1 != 0) {
        temp_a1 = temp_v1 - 2;
        temp_v0 = temp_v1[-1] - 1;
        temp_v1[-1] = temp_v0;
        if (temp_v0 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
    s1->_mesParam = key;
    ObjectList_AppendRetained(l->_keepMesList, mes.p);
}

/* Owning stack reference to a keep-message; its destructor releases the object (reference count in
 * the low 23 bits of _refCount). */

void FUN_0037e890(beDemoManager *arg0, int arg1, int arg2) {
    beDemoManagerWork *old;
    int var_v0;
    int key;
    int *temp_v1;
    beDemoManagerWork *l;
    int temp_v0;
    beDemoKeepMes *s1;
    int var_v0_2;
    int *temp_a1;
    int var_v0_3;

    key = arg1;
    if (arg0->_buildData == 0) {
        var_v0_3 = igObject_GetAllocator(arg0);
        if (GPR_00554c14 != 0) {
            var_v0_3 = (int)var_v0_3;
        } else {
            var_v0_3 = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        }
        old = (beDemoManagerWork *)arg0->_buildData;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(old);
            }
        }
        arg0->_buildData = (int)FUN_003637c0(var_v0_3);
        arg0->_turningOK = 0;
    }
    l = (beDemoManagerWork *)arg0->_buildData;
    var_v0 = igObject_GetAllocator(arg0);
    if (GPR_00554c14 != 0) {
        var_v0 = (int)var_v0;
    } else {
        var_v0 = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
    }
    igSmartPointer<beDemoKeepMes> mes(FUN_00363c20(var_v0));
    mes.p->_kind = 6;
    s1 = mes.p;
    if (g_stringPool[0] == 0) {
        var_v0_2 = StringPool_Allocate(0x10);
        if (var_v0_2 != 0) {
            var_v0_2 = StringPool_Construct(var_v0_2);
        }
        g_stringPool[0] = var_v0_2;
    }
    key = (int)StringPool_Intern(g_stringPool[0], key);
    temp_v1 = (int *)s1->_mesParam;
    if (temp_v1 != 0) {
        temp_a1 = temp_v1 - 2;
        temp_v0 = temp_v1[-1] - 1;
        temp_v1[-1] = temp_v0;
        if (temp_v0 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
    s1->_mesParam = key;
    mes.p->_ramNo = arg2;
    ObjectList_AppendRetained(l->_keepMesList, mes.p);
}

void FUN_0037ea50(beDemoManager *arg0) {
    igObject *temp_a0;
    igObject *temp_a1;

    temp_a1 = (igObject *)arg0->_buildData;
    if ((temp_a1 != 0) && (arg0->_turningOK != 1)) {
        ObjectList_AppendRetained(arg0->_activeDataList, temp_a1);
        temp_a0 = (igObject *)arg0->_buildData;
        if (temp_a0 != 0) {
            temp_a0->_refCount = temp_a0->_refCount - 1;
            if (((unsigned long long)((long long)(int)temp_a0->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        arg0->_buildData = 0;
        arg0->_turningOK = 0;
    }
}

/* Hands the object to the insight core's helper igInsightCore_AddToScheduler, which asks the scheduler at +12 of
 * the insight object (_insight) whether it already has the object (scheduler slot 26) and, if not,
 * calls scheduler slot 24 with it. Same body as beMessenger slot 21. The second argument is
 * unused. */
void Gap__Bec__beDemoManager__vfunc_21(beDemoManager *self, int unusedArg)
{
    igInsightCore_AddToScheduler(self->_insight, self);
}

/* Counterpart of slot 21 through igInsightCore_RemoveFromScheduler, which calls scheduler slot 25 with the object only
 * when scheduler slot 26 reports it present. Same body as beMessenger slot 22. The second argument
 * is unused. */
void Gap__Bec__beDemoManager__vfunc_22(beDemoManager *self, int unusedArg)
{
    igInsightCore_RemoveFromScheduler(self->_insight, self);
}

void Gap__Bec__beDemoManager__vfunc_23(beDemoManager *arg0) {
    arg0->_messenger = igInsightCore_FindManager(arg0->_insight, g_beMessenger_metaObject[0]);
    arg0->_lua = igInsightCore_FindManager(arg0->_insight, g_beLua_metaObject[0]);
}

void Gap__Bec__beDemoManager__vfunc_24(void)
{
}

int Gap__Bec__beDemoManager__vfunc_25(void) {
    return 0;
}

void Gap__Bec__beDemoManager__vfunc_26(beDemoManager *arg0) {
    igObjectList *l;
    int n;
    int i;
    igObject *o;
    igObjectList *l2;
    if (arg0->_disableRemoveAll == 1) {
        arg0->_calledRemoveAll = 1;
        return;
    }
    l = (igObjectList *)arg0->_activeDataList;
    n = l->_count;
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
    l2 = (igObjectList *)arg0->_activeDataList;
    /* matching construct: empty then-branch reproduces the retail branch layout */
    if (0 < l2->_count) {
    } else {
        List_Reserve(l2, 0, 4);
    }
    o = (igObject *)arg0->_buildData;
    if (o != 0) {
        o->_refCount = (int)o->_refCount - 1;
        if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(o);
        }
    }
    arg0->_buildData = 0;
    arg0->_turningOK = 0;
    arg0->_calledRemoveAll = 0;
}

void Gap__Bec__beDemoManager__vfunc_27(beDemoManager *arg0) {
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
                g_mdlEntity[0] = 0;
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

int Gap__Bec__beDemoManager__vfunc_20(void)
{
    return g_beDemoManager_metaObject[0];
}

