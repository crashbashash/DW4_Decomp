#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#define REL(o) { igObject *rr = (o); if (rr != 0) { rr->_refCount = rr->_refCount - 1; if ((rr->_refCount & 0x7FFFFF) == 0) { igObject_Destroy(rr); } } }
#define RET(o) { igObject *rt = (o); if (rt != 0) rt->_refCount = rt->_refCount + 1; }
#define SETP(T, panel, src, field) { igObject *c = (igObject *)(src); T *pp = (T *)(panel); if (c != 0) c->_refCount = c->_refCount + 1; { igObject *o = (igObject *)pp->field; REL(o) } pp->field = (int)c; }
#define HOOK(T, panel) SETP(T, panel, work->_textSetList, _textSetList) SETP(T, panel, work->_textColorList, _textColorList) ((T *)(panel))->_playerNo = ram->_ramNo; ((T *)(panel))->_manager = (int)self; ((T *)(panel))->_messenger = self->_messenger;

extern "C" int StringPool_Allocate(...);
extern "C" int StringChunk_ReleaseHeader(...);
extern "C" int StringPool_Construct(...);
extern "C" int StringPool_Intern(...);
extern "C" int beMessenger_AppendString(...);
extern "C" int beMessenger_AppendVec3(int, float *);
extern "C" int beMessenger_DispatchSelected(...);
extern "C" int beMessenger_SelectGroup(...);
extern "C" int strcmp(...);
extern "C" int beMessenger_SelectReceivers(int, int *, int, int);
extern "C" void FUN_003ce700(int *arg0);
extern "C" void igObject_Destroy(void *);
extern "C" int sprintf(...);
extern "C" int List_Reserve(...);
extern "C" int List_Resize(...);
extern "C" int ObjectList_AppendRetained(int, int);
extern "C" int beMessenger_AppendInt(...);
extern "C" void * beMessenger_GetObject(...);
extern "C" int beNDMWItemBase_GetRecordInt(...);
extern "C" int * beNDMWItemBase_GetRecordString(...);
extern "C" long long __divdi3(long long, int);
extern "C" int beMessenger_AppendFloat(int, float);
extern "C" int beMessenger_EnqueueSelected(int, int *, int);
extern "C" int beMessenger_PrepareDelayedSelection(int, int *, int *, int);
extern "C" int igInsightCore_FindManager(int, int);
extern "C" int Gap__Bec__beNDMWPanelWaza__vfunc_30(void);
extern "C" int Gap__Bec__beNDMWPanelWaza__vfunc_20(void);
extern "C" int beMessenger_RegisterReceiver(int, void *, int *, int, int);
extern "C" int beBaseInfoRam_StartTimer(...);
extern "C" int beBaseInfoRam_IsTimerExpired(void *, int *);
extern "C" int FUN_003cc3d0(int, int *);
extern "C" int FUN_003cc480(void *);
extern "C" int FUN_003cc540(void *);
extern "C" void *FUN_003bdb10(void *);
extern "C" int FUN_003bee30(...);
extern "C" void *Memory_GetAllocatorBySelector(int);
extern "C" void *igObject_GetAllocator(void *);
extern "C" unsigned int beMessenger_ResolveEnumValue(int, int, int);
extern "C" int beMessenger_AppendBool(int, unsigned char);
extern "C" int beMessenger_GetBool(int, int);
extern "C" int beMessenger_GetBoolCount(int);
extern "C" int beMessenger_GetInt(int, int);
extern "C" int beMessenger_PopArgContext(int);
extern "C" int beMessenger_PushArgContext(int);
extern "C" int beMessenger_SendNamed(int, int *, int, int, int *);
extern "C" int beMessenger_SetBool(int, int, unsigned char);
extern "C" int Gap__Bec__beNDMWPanelObjectStat__vfunc_20(void);
extern "C" void Gap__Bec__beNDMWPanelObjectStat__vfunc_22(void);
extern "C" int Gap__Bec__beNDMWPanelObjectItem__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWPanelObjectWaza__vfunc_20(void);
extern "C" int DAT_004cc6d0[4];
extern "C" int DAT_004cc6e0[4];
extern "C" int DAT_004cc720[4];
extern "C" int DAT_00515950[4];
extern "C" int DAT_00515958[4];
extern "C" int DAT_00515960[4];
extern "C" int DAT_00515968[4];
extern "C" int DAT_00515970[4];
extern "C" int DAT_00515978[4];
extern "C" int DAT_00515980[4];
extern "C" int DAT_00515988[4];
extern "C" int g_stringPool[4];
extern "C" float DAT_0058c180[12];
extern "C" char GPR_00554e6c;
struct RecoveryString { void *p; RecoveryString() {} RecoveryString(void *q) { p = q; } ~RecoveryString() { if (p != 0) { int *t = (int *)((char *)p - 8); int v = *(int *)((char *)p - 4) - 1; *(int *)((char *)p - 4) = v; if (v == 0) StringChunk_ReleaseHeader(*t, t); } } };
extern "C" RecoveryString StringList_CopyRetained(void *, int);
struct SetOp { static inline void go(igStringRefList *L, int idx, const RecoveryString &r) { int cnt; int *slot; int *t; int *a1; int c; cnt = L->_count; if (cnt != 0 && idx >= 0 && idx < cnt) { slot = (int *)L->_data + idx; t = (int *)r.p; if (t != 0) t[-1] = t[-1] + 1; t = (int *)(*slot); if (t != 0) { a1 = t - 2; c = t[-1] - 1; t[-1] = c; if (c == 0) StringChunk_ReleaseHeader(*a1, a1); } *slot = (int)r.p; } } };
extern "C" void FUN_003cdef0(beNDMWPanelObject *self, int g, int s, int *name, int val);
struct P4B { float x; float y; float z; };
extern "C" void FUN_003ce4c0(beNDMWPanelObject *arg0, struct P4B *arg1);
extern "C" int DAT_00515990[4];
typedef struct A { char pad[12]; int f12; char pad16[4]; int f20; } A;
extern "C" void FUN_003ce500(A *arg0, int *arg1, int *arg2, float *arg3, int arg4);
extern "C" int DAT_004cc690[][4];
extern "C" int DAT_005159a0[4];
extern "C" int DAT_005159b0[4];
extern "C" int DAT_005159c0[4];
extern "C" int DAT_005159c8[4];
extern "C" int DAT_005159d8[4];
extern "C" void FUN_003ce5b0(beNDMWPanelObject *arg0, int arg1, int arg2);
extern "C" int DAT_004cc69c[4];
extern "C" int DAT_005159e0[4];
extern "C" void FUN_003ce7e0(beNDMWPanelObject *arg0);
typedef struct O { char p0[12]; int f12; char p1[8]; int f24; int f28; char p2[20]; int f52; } O;
extern "C" void FUN_003ce890(O *arg0);
struct Rec { char p[12]; int f12; };
extern "C" Rec * igProperty_GetRecord(...);
extern "C" Rec * igProperty_GetRecordFolder(...);
extern "C" int DAT_005159f0[4];
extern "C" int DAT_005159f8[4];
extern "C" int DAT_00515a08[4];
extern "C" int DAT_00515a18[4];
extern "C" int DAT_00515a20[4];
extern "C" int DAT_00515a28[4];
struct Rel { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
extern "C" void Gap__Bec__beNDMWPanelObjectWaza__vfunc_21(beNDMWPanelObjectWaza *arg0);
extern "C" int DAT_00515a30[4];
extern "C" int DAT_00515a38[4];
extern "C" int DAT_00515a40[4];
extern "C" int DAT_00515a48[4];
extern "C" int DAT_00515a58[4];
extern "C" int DAT_00515a60[4];
extern "C" int DAT_00515a70[4];
extern "C" int DAT_00515a80[4];
extern "C" int DAT_00515a88[4];
extern "C" int DAT_00515a98[4];
/* Property record: integer value at +12. */
struct PropertyRecordInt { char p[12]; int value; };
extern "C" void Gap__Bec__beNDMWPanelObjectWaza__vfunc_22(beNDMWPanelObjectWaza *arg0, int *arg1, long long *arg2);
extern "C" int g_bePadManager_metaObject[4];
extern "C" void Gap__Bec__beNDMWPanelWaza__vfunc_32(beNDMWPanelWaza *arg0);
extern "C" int g_beNDMWPanelWazaInfo_metaObject[4];
extern "C" int g_beNDMWPanelWaza_metaObject[4];
extern "C" int DAT_00515b80[4];
extern "C" void Gap__Bec__beNDMWPanelWaza__vfunc_29(beNDMWPanelWaza *arg0, void *arg1);
extern "C" bePadData *bePadManager_GetPadForPlayer(int, int);
extern "C" int DAT_004cc680[4];
extern "C" int DAT_004cc6c0[4];
extern "C" int DAT_00515b90[4];
extern "C" int DAT_00515b98[4];
extern "C" int DAT_00515ba8[4];
extern "C" int DAT_00515bb8[4];
extern "C" int DAT_00515bc8[4];
class StringRef {
public:
    char *p;
    StringRef(const char *text);
    ~StringRef();
};
extern "C" int FUN_003cc490(int, StringRef *);
/* matching construct: dummy-virtual panel object; slot 21 refreshes, slot 22 asks for a fire request */
class PanelVt { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
 virtual void Refresh();
 virtual void GetFireRequest(int *label, long long *result);
};
/* matching construct: dummy-virtual info work; slot 16 is the "finished" notification */
class WorkVt { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
 virtual void Finished();
};
struct H {
static void SetLabel(beNDMWPanelWazaInfoWork *w, int str)
{
    int pool;
    int fresh;
    int old;
    int *hd;
    int rc;

    if (g_stringPool[0] == 0) {
        pool = StringPool_Allocate(0x10);
        if (pool != 0) {
            pool = StringPool_Construct(pool);
        }
        g_stringPool[0] = pool;
    }
    fresh = StringPool_Intern(g_stringPool[0], str);
    old = w->_retWazaLabel;
    if (old != 0) {
        hd = (int *)(old - 8);
        rc = *(int *)(old - 4) - 1;
        *(int *)(old - 4) = rc;
        if (rc == 0) {
            StringChunk_ReleaseHeader(*hd, hd);
        }
    }
    w->_retWazaLabel = fresh;
}
};
extern "C" void Gap__Bec__beNDMWPanelWaza__vfunc_31(beNDMWPanelWaza *self, beNDMWPanelWazaInfoRam *ram);
/* matching construct: dummy-virtual view of beNDMWPanelObjectItem so the call
 * through slot 21 compiles to the retail vtable load; the data fields are
 * reached through the reflected struct. */
class ItemPanelShim {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4();
    virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void v21();
};
/* property record returned by the igProperty lookup (no reflected class) */
struct Rec_3d0760 { int p[3]; igObjectList *f12; };
extern "C" int DAT_00515aa8[4];
extern "C" int FUN_003d0760(beNDMWPanelWaza *arg0, beNDMWPanelWazaInfoRam *arg1);
/* matching construct: dummy-virtual view of beNDMWPanelObjectWaza so the call
 * through slot 21 (Gap__Bec__beNDMWPanelObjectWaza__vfunc_21) compiles to the
 * retail vtable load; the data fields are reached through the reflected struct. */
class WazaPanelShim {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4();
    virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void v21();
};
/* property records returned by the igProperty lookups (no reflected class) */
struct Rec_3d08f0 { int p[3]; igObjectList *f12; };
struct Fld { int p[3]; int f12; };
extern "C" int FUN_003d08f0(beNDMWPanelWaza *arg0, beNDMWPanelWazaInfoRam *arg1);
struct Rel_3d0a90 { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
extern "C" void FUN_003d0a90(int arg0, beNDMWPanelWazaInfoRam *arg1, int arg2, igObject *arg3);
extern "C" int DAT_00515bd8[4];
extern "C" int DAT_00515be0[4];
extern "C" int DAT_00515be8[4];
extern "C" int g_defaultAllocatorSelector[4];
extern "C" unsigned char g_useOwnerAllocator;
extern "C" int Gap__Bec__beNDMWPanelWaza__vfunc_34(beNDMWPanelWaza *self, beNDMWPanelWazaInfoRam *ram, beMessengerWork *arg2);
extern "C" int g_beNDMWPanelObjectStat_metaObject[4];
extern "C" int g_beNDMWPanelObjectItem_metaObject[4];
extern "C" int g_beNDMWPanelObjectWaza_metaObject[4];

void FUN_003cdef0(beNDMWPanelObject *self, int g, int s, int *name, int val) {
    float v[3];
    int idx;
    int pool;
    int ref;
    int cnt;
    bool x;
    float *p;
    int *slot;
    int *t;

    if (GPR_00554e6c == 0) {
        DAT_0058c180[0] = 0.9f;
        DAT_0058c180[1] = 0.9f;
        DAT_0058c180[2] = 0.9f;
        DAT_0058c180[3] = 0.5f;
        DAT_0058c180[4] = 0.5f;
        DAT_0058c180[5] = 0.7f;
        DAT_0058c180[6] = 1.0f;
        DAT_0058c180[7] = 0.68f;
        DAT_0058c180[8] = 1.0f;
        DAT_0058c180[9] = 0.0f;
        DAT_0058c180[10] = 0.96f;
        DAT_0058c180[11] = 1.0f;
        GPR_00554e6c = 1;
    }
    idx = s + g * 16;
    if (name != 0) {
        if ((t = (int *)StringList_CopyRetained(((igStringRefList *)self->_textSetList), idx).p, x = true, t != 0) && (strcmp((int *)StringList_CopyRetained(((igStringRefList *)self->_textSetList), idx).p, name) == 0 ? (x = false, 1) : 0)) {}
        if (x) {
            if (name == 0) {
                ref = 0;
            } else {
                if (g_stringPool[0] == 0) {
                    pool = StringPool_Allocate(16);
                    if (pool != 0) pool = StringPool_Construct(pool);
                    g_stringPool[0] = pool;
                }
                ref = StringPool_Intern(g_stringPool[0], name);
            }
            SetOp::go(((igStringRefList *)self->_textSetList), idx, RecoveryString((void *)ref));
            beMessenger_SelectGroup(self->_messenger, &DAT_00515950[0]);
            beMessenger_AppendString(self->_messenger, DAT_004cc6d0[g]);
            beMessenger_AppendString(self->_messenger, DAT_004cc6e0[s]);
            beMessenger_AppendString(self->_messenger, name);
            beMessenger_DispatchSelected(self->_messenger, &DAT_00515958[0]);
            if (g == 1) {
                beMessenger_SelectGroup(self->_messenger, &DAT_00515950[0]);
                beMessenger_AppendString(self->_messenger, DAT_004cc6d0[g]);
                beMessenger_AppendString(self->_messenger, DAT_004cc6e0[s]);
                beMessenger_AppendString(self->_messenger, &DAT_00515960[0]);
                beMessenger_DispatchSelected(self->_messenger, &DAT_00515968[0]);
            }
            beMessenger_SelectGroup(self->_messenger, &DAT_00515950[0]);
            beMessenger_AppendString(self->_messenger, DAT_004cc6d0[g]);
            beMessenger_AppendString(self->_messenger, DAT_004cc6e0[s]);
            beMessenger_AppendString(self->_messenger, &DAT_00515970[0]);
            beMessenger_DispatchSelected(self->_messenger, &DAT_00515978[0]);
        }
        slot = (int *)((igIntList *)self->_textColorList)->_data + idx;
        if (val != *slot) {
            cnt = ((igIntList *)self->_textColorList)->_count;
            if (cnt != 0 && idx >= 0 && idx < cnt) {
                *slot = val;
            }
            beMessenger_SelectGroup(self->_messenger, &DAT_00515950[0]);
            beMessenger_AppendString(self->_messenger, DAT_004cc6d0[g]);
            beMessenger_AppendString(self->_messenger, DAT_004cc6e0[s]);
            p = &DAT_0058c180[val * 3];
            v[0] = p[0]; v[1] = p[1]; v[2] = p[2];
            beMessenger_AppendVec3((int)self->_messenger, (float *)(&v[0]));
            beMessenger_DispatchSelected(self->_messenger, &DAT_00515980[0]);
        }
    } else {
        SetOp::go(((igStringRefList *)self->_textSetList), idx, RecoveryString((void *)0));
        cnt = ((igIntList *)self->_textColorList)->_count;
        if (cnt != 0 && idx >= 0 && idx < cnt) {
            *((int *)((igIntList *)self->_textColorList)->_data + idx) = DAT_004cc720[0];
        }
        beMessenger_SelectGroup(self->_messenger, &DAT_00515950[0]);
        beMessenger_AppendString(self->_messenger, DAT_004cc6d0[g]);
        beMessenger_AppendString(self->_messenger, DAT_004cc6e0[s]);
        beMessenger_AppendString(self->_messenger, &DAT_00515988[0]);
        beMessenger_DispatchSelected(self->_messenger, &DAT_00515978[0]);
    }
}

void FUN_003ce4c0(beNDMWPanelObject *arg0, struct P4B *arg1) {
    arg1->x = 150.0f * (float) arg0->_playerNo - 260.0f;
    arg1->y = -160.0f;
    arg1->z = 0.0f;
}

void FUN_003ce500(A *arg0, int *arg1, int *arg2, float *arg3, int arg4) {
    float sp50[4];

    beMessenger_SelectReceivers(arg0->f12, &DAT_00515990[0], (int)arg1, arg0->f20);
    if (arg3 != 0) {
        sp50[0] = arg3[0];
        sp50[1] = arg3[1];
        sp50[2] = arg3[2];
        beMessenger_AppendVec3(arg0->f12, &sp50[0]);
    }
    if (arg4 != 0) {
        beMessenger_AppendString(arg0->f12, arg4);
    }
    beMessenger_DispatchSelected(arg0->f12, (int)arg2);
}

void FUN_003ce5b0(beNDMWPanelObject *arg0, int arg1, int arg2) {
    int sp40[3];
    int v;
    int k;

    switch (arg0->_listKazu) {
    case 0:
    case 1:
    case 2:
        v = 2;
        break;
    case 3:
        v = 1;
        break;
    default:
        v = 0;
        break;
    }
    arg0->_lineMode = v;
    if (arg1 != 0) {
        FUN_003ce4c0(arg0, (struct P4B *)sp40);
        FUN_003ce500((A *)arg0, &DAT_005159a0[0], &DAT_005159b0[0], (float *)sp40, DAT_004cc690[arg0->_page][v]);
    } else {
        FUN_003ce500((A *)arg0, &DAT_005159a0[0], (int *)DAT_004cc690[arg0->_page][v], (float *)0, 0);
    }
    if (!(arg2 & 0xFF)) {
        beMessenger_SelectGroup(arg0->_messenger, &DAT_005159c0[0]);
        beMessenger_AppendString(arg0->_messenger, &DAT_005159c8[0]);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_005159d8[0]);
    }
}

void FUN_003ce700(int *arg0) {
    int i;
    int t;

    FUN_003ce500((A *)arg0, &DAT_005159a0[0], (int *)(DAT_004cc69c[arg0[4] * 4]), (float *)0, 0);
    i = 0;
    do {
        t = i + arg0[5] * 4;
        FUN_003cdef0((beNDMWPanelObject *)arg0, 0, t, (int *)0, 0);
        FUN_003cdef0((beNDMWPanelObject *)arg0, 2, t, (int *)0, 0);
        if (i == 0) {
            FUN_003cdef0((beNDMWPanelObject *)arg0, 1, t / 4, (int *)0, 0);
        }
        i += 1;
    } while (i < 4);
}

void FUN_003ce7e0(beNDMWPanelObject *arg0) {
    int temp_v1;
    int temp_v1_2;
    temp_v1 = arg0->_cursor;
    if (temp_v1 != 0) {
        arg0->_cursor = temp_v1 - 1;
        beMessenger_SelectGroup(arg0->_messenger, &DAT_005159c0[0]);
        beMessenger_AppendString(arg0->_messenger, &DAT_005159e0[0]);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_005159d8[0]);
        return;
    }
    temp_v1_2 = arg0->_offset;
    if (temp_v1_2 != 0) {
        arg0->_offset = temp_v1_2 - 1;
        beMessenger_SelectGroup(arg0->_messenger, &DAT_005159c0[0]);
        beMessenger_AppendString(arg0->_messenger, &DAT_005159e0[0]);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_005159d8[0]);
    }
}

void FUN_003ce890(O *arg0) {
    int n;
    int cur;
    int t;
    n = arg0->f52;
    if (n != 0 && (cur = arg0->f24, cur != (n - 1))) {
        if (cur != 3) {
            arg0->f24 = cur + 1;
            beMessenger_SelectGroup(arg0->f12, &DAT_005159c0[0]);
            beMessenger_AppendString(arg0->f12, &DAT_005159e0[0]);
            beMessenger_DispatchSelected(arg0->f12, &DAT_005159d8[0]);
            return;
        }
        t = arg0->f28;
        if ((t + 4) < n) {
            arg0->f28 = t + 1;
            beMessenger_SelectGroup(arg0->f12, &DAT_005159c0[0]);
            beMessenger_AppendString(arg0->f12, &DAT_005159e0[0]);
            beMessenger_DispatchSelected(arg0->f12, &DAT_005159d8[0]);
        }
    }
}

static inline int countOf(const igIntList *l) { return l->_count; }

void Gap__Bec__beNDMWPanelObjectWaza__vfunc_21(beNDMWPanelObjectWaza *arg0) {
    int spB0[3];
    int spA8[2];
    if (arg0->_playerDataList == 0) {
        beMessenger_SelectGroup(arg0->_messenger, DAT_005159f0);
        beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
        beMessenger_DispatchSelected(arg0->_messenger, DAT_005159f8);
        igObject *o = (igObject *)beMessenger_GetObject(arg0->_messenger, 0);
        if (o != 0) {
            o->_refCount = o->_refCount + 1;
        }
        Rel::go((igObject *)arg0->_playerDataList);
        arg0->_playerDataList = (int)o;
    }
    igObjectList *fl = (igObjectList *)igProperty_GetRecordFolder(arg0->_playerDataList, DAT_00515a08)->f12;
    igObjectList *l = (igObjectList *)arg0->_listFolder;
    int n1 = l->_count;
    int i1 = 0;
    if (0 < n1) {
        do {
            Rel::go(((igObject **)l->_data)[i1]);
            i1++;
        } while (i1 < n1);
    }
    int m = l->_count;
    for (int j = 0; j < m; j++) {
        ((igObject **)l->_data)[j] = 0;
    }
    l->_count = 0;
    int n2 = fl->_count;
    for (int k = 0; k < n2; k++) {
        ObjectList_AppendRetained(arg0->_listFolder, (int)((igObject **)fl->_data)[k]);
    }
    int cnt = ((igObjectList *)arg0->_listFolder)->_count;
    igIntList *d = (igIntList *)arg0->_listColor;
    if (d->_count < cnt) {
        if (!(cnt < countOf(d))) List_Reserve(d, cnt, 4);
    }
    d = (igIntList *)arg0->_listColor;
    if (cnt >= 0) {
        if (cnt <= d->_capacity) {
            d->_count = cnt;
        } else {
            List_Resize(d, cnt, 4);
        }
    }
    int c2 = ((igObjectList *)arg0->_listFolder)->_count;
    if (c2 != arg0->_listKazu) {
        arg0->_cursor = 0;
        arg0->_offset = 0;
        arg0->_listKazu = c2;
    }
    FUN_003ce4c0((beNDMWPanelObject *)arg0, (struct P4B *)spB0);
    int i = 0;
    do {
        int s3 = i + arg0->_playerNo * 4;
        int a = arg0->_lineMode;
        int s2 = (i + arg0->_offset) - a;
        if (a <= i) {
            igObjectList *v1 = (igObjectList *)arg0->_listFolder;
            if (s2 < v1->_count) {
                int s6 = s2 * 4;
                int s1 = 0;
                beNDMWItemBase *s0 = ((beNDMWItemBase **)v1->_data)[s2];
                int *s7 = beNDMWItemBase_GetRecordString(s0, arg0->_manager, DAT_00515a18);
                int s8 = igProperty_GetRecord(arg0->_playerDataList, DAT_00515a20)->f12;
                if (s8 < beNDMWItemBase_GetRecordInt(s0, arg0->_manager, DAT_00515a20)) {
                    s1 = 1;
                }
                if (arg0->_isNoHealing != 0) {
                    int t = s0->_recNo;
                    if (t >= 40 && t < 50) s1 = 2;
                }
                if (arg0->_isNoParaUp != 0) {
                    int t = s0->_recNo;
                    if (t >= 65 && t < 70) s1 = 2;
                    else if (t >= 75 && t < 85) s1 = 2;
                }
                if (arg0->_isNoCureling != 0) {
                    int t = s0->_recNo;
                    if (t >= 50 && t < 65) s1 = 2;
                }
                igIntList *w = (igIntList *)arg0->_listColor;
                int nn = w->_count;
                if (nn != 0 && s2 >= 0 && s2 < nn) {
                    ((int *)w->_data)[s2] = s1;
                }
                FUN_003cdef0((beNDMWPanelObject *)arg0, 0, (int)s3, (int *)s7, (int)s1);
            } else {
                FUN_003cdef0((beNDMWPanelObject *)arg0, 0, (int)s3, (int *)0, 0);
            }
        } else {
            FUN_003cdef0((beNDMWPanelObject *)arg0, 0, (int)s3, (int *)0, 0);
        }
        FUN_003cdef0((beNDMWPanelObject *)arg0, 2, (int)s3, (int *)0, 0);
        if (i == 0) {
            sprintf(spA8, DAT_00515a28, beNDMWItemBase_GetRecordInt(((beNDMWItemBase **)((igObjectList *)arg0->_listFolder)->_data)[arg0->_cursor + arg0->_offset], arg0->_manager, DAT_00515a20));
            FUN_003cdef0((beNDMWPanelObject *)arg0, 1, (int)(s3 / 4), (int *)spA8, 0);
        }
        i++;
    } while (i < 4);
}

void Gap__Bec__beNDMWPanelObjectWaza__vfunc_22(beNDMWPanelObjectWaza *arg0, int *arg1, long long *arg2) {
    int temp_s2;
    struct PropertyRecordInt *temp_s1;
    int temp_s0;
    int temp_v1;
    int temp_v0;

    *arg2 = 0;
    *arg1 = 0;
    temp_v1 = arg0->_cursor + arg0->_offset;
    if (((int *)((igDataList *)arg0->_listColor)->_data)[temp_v1] == 0) {
        temp_s2 = ((int *)((igObjectList *)arg0->_listFolder)->_data)[temp_v1];
        temp_s1 = (struct PropertyRecordInt *)igProperty_GetRecord(arg0->_playerDataList, &DAT_00515a20[0]);
        temp_v0 = beNDMWItemBase_GetRecordInt(temp_s2, arg0->_manager, &DAT_00515a20[0]);
        if (temp_s1->value >= temp_v0) {
            *arg2 = (long long)beNDMWItemBase_GetRecordInt(temp_s2, arg0->_manager, &DAT_00515a30[0]);
            *arg2 = __divdi3(*arg2 * 0x3B9ACA00LL, 0x3C);
            *arg1 = ((int)beNDMWItemBase_GetRecordString(temp_s2, arg0->_manager, &DAT_00515a38[0]));
            temp_s1->value = temp_s1->value - temp_v0;
            temp_s0 = ((struct PropertyRecordInt *)((void *)igProperty_GetRecord(arg0->_playerDataList, &DAT_00515a40[0])))->value;
            beMessenger_PrepareDelayedSelection(arg0->_messenger, &DAT_00515a48[0], &DAT_00515a58[0], arg0->_playerNo);
            beMessenger_AppendFloat(arg0->_messenger, (float)(temp_s1->value * 100 / temp_s0));
            beMessenger_EnqueueSelected(arg0->_messenger, &DAT_00515a60[0], 1);
            beMessenger_PrepareDelayedSelection(arg0->_messenger, &DAT_00515a70[0], &DAT_00515a80[0], arg0->_playerNo);
            beMessenger_AppendInt(arg0->_messenger, temp_s1->value);
            beMessenger_EnqueueSelected(arg0->_messenger, &DAT_00515a88[0], 1);
            return;
        }
        beMessenger_SelectGroup(arg0->_messenger, &DAT_005159c0[0]);
        beMessenger_AppendString(arg0->_messenger, &DAT_00515a98[0]);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_005159d8[0]);
        return;
    }
    beMessenger_SelectGroup(arg0->_messenger, &DAT_005159c0[0]);
    beMessenger_AppendString(arg0->_messenger, &DAT_00515a98[0]);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_005159d8[0]);
}

void Gap__Bec__beNDMWPanelWaza__vfunc_32(beNDMWPanelWaza *arg0) {
    if (arg0->_padManager == 0) {
        arg0->_padManager = igInsightCore_FindManager(arg0->_insight, g_bePadManager_metaObject[0]);
    }
}

int Gap__Bec__beNDMWPanelWaza__vfunc_30(void)
{
    return g_beNDMWPanelWazaInfo_metaObject[0];
}

void Gap__Bec__beNDMWPanelWaza__vfunc_29(beNDMWPanelWaza *arg0, void *arg1) {
    beMessenger_RegisterReceiver(arg0->_messenger, arg1, &DAT_00515b80[0], 0, *(int *)((char *)(arg1) + 8));
    *(char *)((char *)(arg1) + 20) = 0;
}

/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]). The constructor interns the text and the destructor releases the token on scope exit;
 * both are out of line. */
static inline int st3(const beNDMWPanelWazaInfoRam *ram) { return ram->_st3; }

void Gap__Bec__beNDMWPanelWaza__vfunc_31(beNDMWPanelWaza *self, beNDMWPanelWazaInfoRam *ram)
{
    unsigned char show;
    beNDMWPanelWazaInfoRam *ramState;
    int sel;
    int both;
    beNDMWPanelObject *panel;
    int prevKazu;
    int vec[4];
    long long ret;
    int *obj;
    unsigned char emg;
    bePadData *pad;
    unsigned char decide;
    int idx;
    int refStr;
    unsigned char blocked;
    beNDMWPanelWazaInfoWork *work;
    int rep;
    unsigned char cancel;
    int prevCursor;
    int trig;

    if (ram->_isRun == 1) {
        work = (beNDMWPanelWazaInfoWork *)ram->_work;
        ramState = (beNDMWPanelWazaInfoRam *)(int)ram;
        pad = (bePadData *)bePadManager_GetPadForPlayer(self->_padManager, ramState->_ramNo);
        trig = pad->_trigger;
        decide = 1;
        both = pad->_rTrg | pad->_rRpt;
        rep = pad->_repeat;
        if (!(both & 1) && !((trig | rep) & 0x10)) {
            decide = 0;
        }
        cancel = 1;
        if (!(both & 4) && !((trig | rep) & 0x40)) {
            cancel = 0;
        }
        switch (work->_page) {
        case 0:
            panel = (beNDMWPanelObject *)work->_panelWaza;
            break;
        case 1:
            panel = (beNDMWPanelObject *)work->_panelItem;
            break;
        case 2:
            panel = (beNDMWPanelObject *)work->_panelStat;
            break;
        }
        prevCursor = panel->_cursor;
        prevKazu = panel->_listKazu;
        idx = prevCursor + panel->_lineMode;
        obj = (int *)*(int *)(work->_playerWork + 200);
        blocked = 0;
        if (obj[2] != 0 && *(unsigned char *)(*(int *)(obj[4] + 4) + 8) != 0) {
            blocked = 1;
        }
        switch (ramState->_st0) {
        case 0:
            {
                StringRef empty(0);
                FUN_003cc490(FUN_003cc540(work), &empty);
            }
            FUN_003cc3d0(FUN_003cc480(work), &DAT_004cc680[0]);
            prevKazu = idx = -1;
            ramState->_st0 = ramState->_st0 + 1;
            ramState->_st3 = 0;
            ramState->_st2 = 0;
            ramState->_st1 = 0;
        case 1:
            emg = 1;
            switch (ramState->_st1) {
            case 0:
                if ((unsigned char)beBaseInfoRam_IsTimerExpired(ramState, &DAT_00515b90[0])) {
                    emg = 0;
                    if (panel->_isEmg != 0 ||
                        (blocked == 0 && (trig & 0x4000) && panel->_listKazu != 0 && work->_page != 2)) {
                        if (ramState->_st3 >= 2) {
                            ((PanelVt *)panel)->GetFireRequest(&refStr, &ret);
                            if (0 < ret) {
                                H::SetLabel(work, refStr);
                                work->_retIsFire = 1;
                                beBaseInfoRam_StartTimer(ramState, &DAT_00515b90[0], ret);
                                ramState->_st1 = ramState->_st1 + 1;
                                ramState->_st3 = 0;
                                ramState->_st2 = 0;
                                panel->_isEmg = 0;
                            } else if (ret < 0) {
                                ramState->_st0 = 2;
                                ramState->_st3 = 0;
                                ramState->_st2 = 0;
                                ramState->_st1 = 0;
                            } else {
                                beBaseInfoRam_StartTimer(ramState, &DAT_00515b90[0], 0x0FE502AA);
                                ramState->_st1 = ramState->_st1 + 1;
                                ramState->_st3 = 0;
                                ramState->_st2 = 0;
                            }
                        }
                    } else if (decide) {
                        FUN_003ce7e0((beNDMWPanelObject *)panel);
                    } else if (cancel) {
                        FUN_003ce890((O *)panel);
                    } else if (trig & 0x800) {
                        if (work->_page != 0) {
                            work->_page = 0;
                            ramState->_st0 = 0;
                            ramState->_st3 = 0;
                            ramState->_st2 = 0;
                            ramState->_st1 = 0;
                        } else {
                            H::SetLabel(work, 0);
                            ramState->_st0 = 2;
                            ramState->_st3 = 0;
                            ramState->_st2 = 0;
                            ramState->_st1 = 0;
                            beMessenger_SelectGroup(self->_messenger, &DAT_005159c0[0]);
                            beMessenger_AppendString(self->_messenger, &DAT_00515b98[0]);
                            beMessenger_DispatchSelected(self->_messenger, &DAT_005159d8[0]);
                        }
                    } else if (trig & 0x400) {
                        if (work->_page != 1) {
                            work->_page = 1;
                            ramState->_st0 = 0;
                            ramState->_st3 = 0;
                            ramState->_st2 = 0;
                            ramState->_st1 = 0;
                        } else {
                            H::SetLabel(work, 0);
                            ramState->_st0 = 2;
                            ramState->_st3 = 0;
                            ramState->_st2 = 0;
                            ramState->_st1 = 0;
                            beMessenger_SelectGroup(self->_messenger, &DAT_005159c0[0]);
                            beMessenger_AppendString(self->_messenger, &DAT_00515b98[0]);
                            beMessenger_DispatchSelected(self->_messenger, &DAT_005159d8[0]);
                        }
                    } else if (trig & 0x200) {
                        if (work->_page != 2) {
                            work->_page = 2;
                            ramState->_st0 = 0;
                            ramState->_st3 = 0;
                            ramState->_st2 = 0;
                            ramState->_st1 = 0;
                        } else {
                            H::SetLabel(work, 0);
                            ramState->_st0 = 2;
                            ramState->_st3 = 0;
                            ramState->_st2 = 0;
                            ramState->_st1 = 0;
                            beMessenger_SelectGroup(self->_messenger, &DAT_005159c0[0]);
                            beMessenger_AppendString(self->_messenger, &DAT_00515b98[0]);
                            beMessenger_DispatchSelected(self->_messenger, &DAT_005159d8[0]);
                        }
                    }
                    if (st3(ramState) < 2) {
                        ramState->_st3 = ramState->_st3 + 1;
                    }
                }
                break;
            case 1:
                if (beBaseInfoRam_IsTimerExpired(ramState, &DAT_00515b90[0]) != 0) {
                    ramState->_st1 = 0;
                    ramState->_st3 = 0;
                    ramState->_st2 = 0;
                }
                break;
            }
            ((PanelVt *)panel)->Refresh();
            if (prevKazu != panel->_listKazu) {
                if (panel->_isEmg != 0 && emg) {
                    FUN_003ce5b0((beNDMWPanelObject *)panel, work->_isWindowGenerate, 1);
                } else {
                    FUN_003ce5b0((beNDMWPanelObject *)panel, work->_isWindowGenerate, 0);
                }
                work->_isWindowGenerate = 0;
            }
            show = 1;
            if (ramState->_st0 == 1 && ramState->_st1 == 1) {
                show = 0;
            } else if (panel->_listKazu == 0) {
                show = 0;
            } else if (blocked) {
                show = 0;
            }
            if (show) {
                sel = panel->_cursor + panel->_lineMode;
                if (work->_isCursorGenerate == 0) {
                    FUN_003ce4c0((beNDMWPanelObject *)panel, (struct P4B *)vec);
                    FUN_003ce500((A *)panel, (int *)(&DAT_00515ba8[0]), (int *)(&DAT_005159b0[0]), (float *)vec, DAT_004cc6c0[sel]);
                    work->_isCursorGenerate = 1;
                    return;
                }
                if (idx != sel) {
                    FUN_003ce500((A *)panel, (int *)(&DAT_00515ba8[0]), (int *)((void *)DAT_004cc6c0[sel]), (float *)0, 0);
                    return;
                }
            } else if (work->_isCursorGenerate != 0) {
                FUN_003ce500((A *)panel, (int *)(&DAT_00515ba8[0]), (int *)(&DAT_00515bb8[0]), (float *)0, 0);
                work->_isCursorGenerate = 0;
                return;
            }
            break;
        case 2:
            beMessenger_SelectGroup(self->_messenger, &DAT_005159c0[0]);
            beMessenger_AppendString(self->_messenger, &DAT_00515bc8[0]);
            beMessenger_DispatchSelected(self->_messenger, &DAT_005159d8[0]);
            FUN_003ce700((int *)panel);
            if (work->_isCursorGenerate != 0) {
                FUN_003ce500((A *)panel, (int *)(&DAT_00515ba8[0]), (int *)(&DAT_00515bb8[0]), (float *)0, 0);
            }
            ramState->_st0 = 3;
            ramState->_st3 = 0;
            ramState->_st2 = 0;
            ramState->_st1 = 0;
            return;
        case 3:
            ramState->_isRun = 0;
            ((WorkVt *)work)->Finished();
            break;
        }
    }
}

int FUN_003d0760(beNDMWPanelWaza *arg0, beNDMWPanelWazaInfoRam *arg1) {
    int len;
    int start;
    beNDMWPanelWazaInfoWork *s2;
    s2 = (beNDMWPanelWazaInfoWork *)arg1->_work;
    if (((beNDMWPanelObjectItem *)s2->_panelItem)->_isNoHealing != 0) {
        return 0;
    }
    beMessenger_SelectGroup(arg0->_messenger, &DAT_005159f0[0]);
    beMessenger_AppendInt(arg0->_messenger, arg1->_ramNo);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_005159f8[0]);
    int o = ((int)beMessenger_GetObject(arg0->_messenger, 0));
    igObjectList *arr = ((Rec_3d0760 *)igProperty_GetRecordFolder(o, &DAT_00515aa8[0]))->f12;
    int best = -1;
    int idx = 0;
    int n = arr->_count - 2;
    int j = 0;
    int t;
    beNDMWItemDisk *it;
    beNDMWItemDisk **p;
    if (j < n) {
        p = (beNDMWItemDisk **)arr->_data;
        do {
            it = *p;
            if (it->_kazu != 0) {
                t = it->_recNo;
                if ((t <= 2 || t == 9) && best < t) {
                    len = idx - 3;
                    best = t;
                    start = idx;
                    if (len < 0) {
                        len = 0;
                    } else {
                        start = idx - len;
                    }
                }
                idx += 1;
            }
            j += 1;
            p += 1;
        } while (j < n);
    }
    if (best != -1) {
        ((ItemPanelShim *)s2->_panelItem)->v21();
        ((beNDMWPanelObjectItem *)s2->_panelItem)->_cursor = start;
        ((beNDMWPanelObjectItem *)s2->_panelItem)->_offset = len;
        ((beNDMWPanelObjectItem *)s2->_panelItem)->_isEmg = 1;
        return 1;
    }
    return 0;
}

int FUN_003d08f0(beNDMWPanelWaza *arg0, beNDMWPanelWazaInfoRam *arg1) {
    igObjectList *s5 = 0;
    int s4 = 0;
    int s3 = 0;
    beNDMWPanelWazaInfoWork *s2 = 0;
    int s1 = 0;
    int s0 = 0;
    s2 = (beNDMWPanelWazaInfoWork *)arg1->_work;
    if (((beNDMWPanelObjectWaza *)s2->_panelWaza)->_isNoHealing != 0) {
        return 0;
    }
    beMessenger_SelectGroup(arg0->_messenger, &DAT_005159f0[0]);
    beMessenger_AppendInt(arg0->_messenger, arg1->_ramNo);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_005159f8[0]);
    int o = ((int)beMessenger_GetObject(arg0->_messenger, 0));
    s1 = ((Fld *)igProperty_GetRecord(o, &DAT_00515a20[0]))->f12;
    s5 = ((Rec_3d08f0 *)igProperty_GetRecordFolder(o, &DAT_00515a08[0]))->f12;
    s4 = s5->_count;
    s3 = s4 - 1;
    s0 = s3 * 4;
    if (s3 >= 0) {
        do {
            beNDMWItemBase *it = ((beNDMWItemBase **)(s5->_data + s0))[0];
            int t = it->_recNo;
            s4 -= 1;
            if (t >= 40 && t < 50 && s1 >= beNDMWItemBase_GetRecordInt(it, arg0, &DAT_00515a20[0])) {
                int r = s4 - 3;
                if (r < 0) {
                    r = 0;
                } else {
                    s4 -= r;
                }
                ((WazaPanelShim *)s2->_panelWaza)->v21();
                ((beNDMWPanelObjectWaza *)s2->_panelWaza)->_cursor = s4;
                ((beNDMWPanelObjectWaza *)s2->_panelWaza)->_offset = r;
                ((beNDMWPanelObjectWaza *)s2->_panelWaza)->_isEmg = 1;
                return 1;
            }
            s3 -= 1;
            s0 -= 4;
        } while (s3 >= 0);
    }
    return 0;
}

void FUN_003d0a90(int arg0, beNDMWPanelWazaInfoRam *arg1, int arg2, igObject *arg3) {
    beNDMWPanelWazaInfoWork *s0 = (beNDMWPanelWazaInfoWork *)arg1->_work;
    beNDMWPanelObjectStat *c;
    if (arg1->_isRun != 0) {
        if (arg1->_st0 == 3) {
            arg1->_isRun = 1;
            s0->_isWindowGenerate = 1;
            s0->_isCursorGenerate = 0;
        }
        arg1->_st0 = 0;
        arg1->_st3 = 0;
        arg1->_st2 = 0;
        arg1->_st1 = 0;
    } else {
        arg1->_isRun = 1;
        s0->_isWindowGenerate = 1;
        s0->_isCursorGenerate = 0;
        arg1->_st0 = 0;
        arg1->_st3 = 0;
        arg1->_st2 = 0;
        arg1->_st1 = 0;
    }
    s0->_page = arg2;
    s0->_retIsFire = 0;
    if (arg3 != 0) {
        arg3->_refCount = arg3->_refCount + 1;
    }
    Rel_3d0a90::go((igObject *)s0->_playerWork);
    s0->_playerWork = (int)arg3;
    c = (beNDMWPanelObjectStat *)s0->_panelStat;
    if (arg3 != 0) {
        arg3->_refCount = arg3->_refCount + 1;
    }
    Rel_3d0a90::go((igObject *)c->_playerWork);
    c->_playerWork = (int)arg3;
}

/* Owning stack reference to the freshly created panel work; released on scope exit (reference
 * count in the low 23 bits of _refCount). */





/* matching constructs: ok is a C++ bool (daddiu); the AppendBool/SetBool bool arguments are unsigned char so
 * the byte load is scheduled like retail. */
int Gap__Bec__beNDMWPanelWaza__vfunc_34(beNDMWPanelWaza *self, beNDMWPanelWazaInfoRam *ram, beMessengerWork *arg2) {
    unsigned int kind;
    beNDMWPanelWazaInfoWork *work;
    bool ok;
    void *alloc;
    void *obj;
    kind = beMessenger_ResolveEnumValue(self->_messenger, FUN_003bee30(), arg2->_message);
    work = (beNDMWPanelWazaInfoWork *)ram->_work;
    if (work == 0) {
        alloc = igObject_GetAllocator(self);
        alloc = g_useOwnerAllocator ? alloc : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        igSmartPointer<igObject> created((igObject *)FUN_003bdb10(alloc));
        { igObject *n = created.p; RET(n) { igObject *o = (igObject *)ram->_work; REL(o) } ram->_work = (int)n; }
        work = (beNDMWPanelWazaInfoWork *)created.p;
        HOOK(beNDMWPanelObjectWaza, work->_panelWaza)
        HOOK(beNDMWPanelObjectItem, work->_panelItem)
        HOOK(beNDMWPanelObjectStat, work->_panelStat)
    }
    switch (kind) {
    case 1:
    case 0:
    case 2:
    case 3:
        ok = true;
        beMessenger_PushArgContext(self->_messenger);
        beMessenger_SendNamed(self->_messenger, DAT_00515bd8, 0, 0, DAT_00515be0);
        if (beMessenger_GetBoolCount(self->_messenger) == 0) {
            ok = false;
        } else if (!(beMessenger_GetBool(self->_messenger, 0) & 0xFF)) {
            ok = false;
        }
        beMessenger_PopArgContext(self->_messenger);
        if (ok) {
            return 1;
        }
        break;
    default:
        break;
    }
    switch (kind) {
    case 0:
    case 1:
    case 2:
        obj = beMessenger_GetObject(self->_messenger, 0);
        switch (kind) {
        case 1:
            FUN_003d0a90((int)self, (beNDMWPanelWazaInfoRam *)ram, 0, (igObject *)obj);
            break;
        case 0:
            FUN_003d0a90((int)self, (beNDMWPanelWazaInfoRam *)ram, 1, (igObject *)obj);
            break;
        case 2:
            FUN_003d0a90((int)self, (beNDMWPanelWazaInfoRam *)ram, 2, (igObject *)obj);
            break;
        }
        ((beNDMWPanelObjectWaza *)work->_panelWaza)->_isEmg = 0;
        ((beNDMWPanelObjectItem *)work->_panelItem)->_isEmg = 0;
        ((beNDMWPanelObjectStat *)work->_panelStat)->_isEmg = 0;
        beMessenger_AppendBool(self->_messenger, 1);
        return 1;
    case 3:
        obj = beMessenger_GetObject(self->_messenger, 0);
        if (FUN_003d0760((beNDMWPanelWaza *)self, (beNDMWPanelWazaInfoRam *)ram) != 0) {
            FUN_003d0a90((int)self, (beNDMWPanelWazaInfoRam *)ram, 1, (igObject *)obj);
        } else if (FUN_003d08f0((beNDMWPanelWaza *)self, (beNDMWPanelWazaInfoRam *)ram) != 0) {
            FUN_003d0a90((int)self, (beNDMWPanelWazaInfoRam *)ram, 0, (igObject *)obj);
        } else if (beBaseInfoRam_IsTimerExpired(ram, DAT_00515be8) != 0) {
            beMessenger_PushArgContext(self->_messenger);
            beMessenger_SelectGroup(self->_messenger, DAT_005159c0);
            beMessenger_AppendString(self->_messenger, (int)DAT_00515a98);
            beMessenger_DispatchSelected(self->_messenger, DAT_005159d8);
            beMessenger_PopArgContext(self->_messenger);
            beBaseInfoRam_StartTimer(ram, DAT_00515be8, 0x0FE502AA);
        }
        beMessenger_AppendBool(self->_messenger, 1);
        return 1;
    case 5:
        if (ram->_isRun == 0) {
            return 1;
        }
        ram->_st0 = 2;
        ram->_st3 = 0;
        ram->_st2 = 0;
        ram->_st1 = 0;
        work->_retIsFire = 0;
        return 1;
    case 10:
        if (beMessenger_GetBoolCount(self->_messenger) == 0) {
            beMessenger_AppendBool(self->_messenger, ram->_isRun);
        } else if (!(beMessenger_GetBool(self->_messenger, 0) & 0xFF)) {
            beMessenger_SetBool(self->_messenger, 0, ram->_isRun);
        }
        return 1;
    case 4:
        beMessenger_AppendBool(self->_messenger, ram->_isRun);
        switch (work->_page) {
        case 0:
            beMessenger_AppendBool(self->_messenger, 0);
            beMessenger_AppendBool(self->_messenger, work->_retIsFire);
            beMessenger_AppendString(self->_messenger, work->_retWazaLabel);
            break;
        case 1:
            beMessenger_AppendBool(self->_messenger, 1);
            beMessenger_AppendBool(self->_messenger, work->_retIsFire);
            break;
        case 2:
            beMessenger_AppendBool(self->_messenger, 0);
            beMessenger_AppendBool(self->_messenger, 0);
            break;
        }
        work->_retIsFire = 0;
        return 1;
    case 6:
        if (beMessenger_GetInt(self->_messenger, 0) == 1) {
            ((beNDMWPanelObjectItem *)work->_panelItem)->_isNoGateDisk = 1;
        } else {
            ((beNDMWPanelObjectItem *)work->_panelItem)->_isNoGateDisk = 0;
        }
        return 1;
    case 7:
        if (beMessenger_GetInt(self->_messenger, 0) == 1) {
            ((beNDMWPanelObjectItem *)work->_panelItem)->_isNoHealing = 1;
            ((beNDMWPanelObjectWaza *)work->_panelWaza)->_isNoHealing = 1;
        } else {
            ((beNDMWPanelObjectItem *)work->_panelItem)->_isNoHealing = 0;
            ((beNDMWPanelObjectWaza *)work->_panelWaza)->_isNoHealing = 0;
        }
        return 1;
    case 8:
        if (beMessenger_GetInt(self->_messenger, 0) == 1) {
            ((beNDMWPanelObjectWaza *)work->_panelWaza)->_isNoParaUp = 1;
        } else {
            ((beNDMWPanelObjectWaza *)work->_panelWaza)->_isNoParaUp = 0;
        }
        return 1;
    case 9:
        if (beMessenger_GetInt(self->_messenger, 0) == 1) {
            ((beNDMWPanelObjectItem *)work->_panelItem)->_isNoCureling = 1;
            ((beNDMWPanelObjectWaza *)work->_panelWaza)->_isNoCureling = 1;
        } else {
            ((beNDMWPanelObjectItem *)work->_panelItem)->_isNoCureling = 0;
            ((beNDMWPanelObjectWaza *)work->_panelWaza)->_isNoCureling = 0;
        }
        return 1;
    default:
        return 0;
    }
}

int Gap__Bec__beNDMWPanelWaza__vfunc_20(void)
{
    return g_beNDMWPanelWaza_metaObject[0];
}

int Gap__Bec__beNDMWPanelObjectStat__vfunc_20(void)
{
    return g_beNDMWPanelObjectStat_metaObject[0];
}

void Gap__Bec__beNDMWPanelObjectStat__vfunc_22(void)
{
}

int Gap__Bec__beNDMWPanelObjectItem__vfunc_20(void)
{
    return g_beNDMWPanelObjectItem_metaObject[0];
}

int Gap__Bec__beNDMWPanelObjectWaza__vfunc_20(void)
{
    return g_beNDMWPanelObjectWaza_metaObject[0];
}
