#include "dw4/reflected.h"
typedef struct List { int w0; int references; int size; int cap; int *data; } List;
typedef struct BList { int w0; int references; int size; int cap; unsigned char *data; } BList;
typedef struct Entry { int w0, w1, w2, w3, w4; beNDMWMdlPEBaseInfoWork *work; } Entry;
typedef struct Model { int w0; int references; int id; char pad12[28]; List *props; } Model;
extern "C" {
extern int igObject_GetAllocator(...);
extern int Memory_GetAllocatorBySelector(...);
extern void *beBaseInfoDataList_Create(...);
extern void *FUN_002caa70(...);
extern void *FUN_002cb0d0(...);
extern void igObject_Destroy(List *);
extern Entry *igProperty_FindByName(...);
extern int FUN_003c04a0(...);
extern int FUN_003c0440(...);
extern int beMessenger_ResolveEnumValue(...);
extern int List_Reserve(...);
extern int List_Resize(...);
extern int beMessenger_ClearObjects(...);
extern int beMessenger_AppendObject(...);
extern int beMessenger_GetInt(...);
extern int beMessenger_GetIntCount(...);
extern int beMessenger_GetString(...);
extern int beMessenger_AppendBool(int, bool);
extern int igMetaEnum_GetValueByName(...);
extern int FUN_004456c0(...);
extern int FUN_00445990(...);
extern int FUN_00445c60(...);
extern int FUN_003a8580(...);
extern int DAT_004cfde8[4], DAT_004cfdf0[4], DAT_004cfdf8[4], DAT_004cfe00[4], DAT_004cfe08[4], DAT_004cfe10[4], DAT_004cfe18[4], DAT_004cfe20[4], DAT_004cfe28[4], DAT_004cfe30[4], DAT_004cfe38[4], DAT_004cfe40[4], DAT_004cfe48[4], DAT_004cfe50[4], DAT_004cfe58[4], DAT_004cfe60[4], DAT_004cfe68[4];
extern int DAT_004fb410[4], DAT_0051d3a0[4], DAT_0051d3f0[4], DAT_0051d450[4], DAT_0051d460[4], DAT_0051d470[4], DAT_0051d478[4], DAT_0051d480[4], DAT_0051d488[4], DAT_0051d490[4], DAT_0051d498[4], DAT_0051d4a0[4], DAT_00585be0[4], DAT_00587110[4];
extern unsigned char GPR_00554aa8, GPR_00554aac, GPR_00554ab0, GPR_00554ab4, GPR_00554ab8, GPR_00554abc, GPR_00554ac0, GPR_00554ac4, GPR_00554ac8, GPR_00554acc, GPR_00554ad0, GPR_00554ad4, GPR_00554ad8, GPR_00554adc, GPR_00554ae0, GPR_00554ae4, GPR_00554ae8, GPR_00554aec, GPR_00554af0, GPR_00554af4, GPR_00554af8, GPR_00554afc, GPR_00554c14;
}
class VC140 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void vX(Model *, void *); };

#define W(f) ((List *)w->f)
#define SETI(L, I, V) if (((List *)(L))->size != 0 && (I) >= 0 && (I) < ((List *)(L))->size) ((List *)(L))->data[I] = (V);
#define SETB(L, I, V) if (((BList *)(L))->size != 0 && (I) >= 0 && (I) < ((BList *)(L))->size) ((BList *)(L))->data[I] = (V);
#define RELEASE(o) if ((o) != 0) { (o)->references = (o)->references - 1; if (((unsigned long long)((long long)(o)->references << 0x29) >> 0x29) == 0) igObject_Destroy(o); }
#define GI(i) beMessenger_GetInt(self->_messenger, i)
/* Owning stack reference to the freshly created property data list: constructed from the object and
 * released at the end of the full expression that stores it (reference count in the low 23 bits of
 * references).  The out-of-line copy the exception table names is the retail body 0x0033e9c0
 * (config/SLUS-20836/unit-objects.json, duplicate __dt__7ListRefFv). */
class ListRef {
public:
    List *p;
    ListRef(List *o) : p(o) {}
    ~ListRef() { List *o = p; if (o != 0) { --o->references; if ((o->references & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* Owning stack reference that carries each new int list of the work while it is sized and filled:
 * starts empty, is handed one created list after another (MKLIST drops the previous one first) and
 * releases the last on scope exit.  The out-of-line copy the exception table names is the retail body
 * 0x00150eb0 (config/SLUS-20836/unit-objects.json, duplicate __dt__10IntListRefFv). */
class IntListRef {
public:
    List *p;
    IntListRef(List *o) : p(o) {}
    ~IntListRef() { List *o = p; if (o != 0) { --o->references; if ((o->references & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* Same role for the work's bool list; retail body 0x00226990 (duplicate __dt__11BoolListRefFv). */
class BoolListRef {
public:
    List *p;
    BoolListRef(List *o) : p(o) {}
    ~BoolListRef() { List *o = p; if (o != 0) { --o->references; if ((o->references & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* Store a freshly created data list in the model, taking the model's share and dropping the previous
 * list; the caller passes the list as a temporary holder that gives up the creating share at the end of
 * the full expression (matching construct: a temporary takes its frame slot after the named locals). */
struct DataList { static inline void store(Model *obj, const ListRef &list) {
    List *created = list.p;
    List *old;
    if (created != 0) created->references = created->references + 1;
    old = obj->props;
    RELEASE(old)
    obj->props = created;
} };
/* create a list with CT in the holder H (dropping the list H held before, as retail does before the
 * create call) and give the work field F its own share of it */
#define MKLIST(H, F, CT) { int a = igObject_GetAllocator(self); a = GPR_00554c14 != 0 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]); { List *u = H.p; RELEASE(u) } H.p = (List *)CT(a); { List *c = H.p; if (c != 0) c->references = c->references + 1; { List *old = W(F); RELEASE(old) } w->F = (int)c; } }
#define SIZEIT(F, N, ES) { List *l = W(F); if (l->size < (N) + 1) List_Reserve(l, N, ES); } { List *l = W(F); if (l->cap >= (N)) l->size = N; else List_Resize(l, N, ES); }
#define FILLI(F, DAT) { int n = W(F)->size; int *d = W(F)->data; int j; for (j = 0; j < n; j++) d[j] = DAT[0]; }
#define FILLB(F, DAT) { BList *l = (BList *)w->F; int n = l->size; unsigned char *d = l->data; int j; for (j = 0; j < n; j++) d[j] = DAT; }
#define VC(name) ((VC140 *)self)->vX(obj, name)

extern "C" int Gap__Bec__beNDMWMdlPEBase__vfunc_47(beNDMWMdlPEBase *self, Model *obj, int name);
extern "C" int Gap__Bec__beNDMWMdlPEBase__vfunc_47(beNDMWMdlPEBase *self, Model *obj, int name) {
    beNDMWMdlPEBaseInfoWork *w;
    int e;
    if (obj->props == 0) {
        int allocator = igObject_GetAllocator(obj);
        DataList::store(obj, ListRef((List *)beBaseInfoDataList_Create(GPR_00554c14 != 0 ? allocator : Memory_GetAllocatorBySelector(DAT_00587110[0]))));
    }
    w = igProperty_FindByName(obj->props, DAT_00585be0[0], &DAT_0051d3a0[0])->work;
    e = beMessenger_ResolveEnumValue(self->_messenger, FUN_003c04a0(), name);
    switch (e) {
    default:
    if (w != 0 && w->_dispRamNoList == 0) {
        IntListRef h9C(0);
        BoolListRef h98(0);
        MKLIST(h9C, _dispRamNoList, FUN_002caa70)
        SIZEIT(_dispRamNoList, 12, 4)
        FILLI(_dispRamNoList, DAT_004cfde8)
        MKLIST(h9C, _dispPosNoList, FUN_002caa70)
        SIZEIT(_dispPosNoList, 12, 4)
        FILLI(_dispPosNoList, DAT_004cfdf0)
        MKLIST(h9C, _timerList, FUN_002caa70)
        SIZEIT(_timerList, 12, 4)
        FILLI(_timerList, DAT_004cfdf8)
        MKLIST(h98, _isFirstList, FUN_002cb0d0)
        SIZEIT(_isFirstList, 11, 1)
        FILLB(_isFirstList, GPR_00554aa8)
    }
    break;
    case 12:
    case 13:
        break;
    case -1:
        return 0;
    }
    switch (e) {
    case 15:
        if (w != 0) {
            beMessenger_ClearObjects(self->_messenger);
            beMessenger_AppendObject(self->_messenger, obj);
            beMessenger_AppendObject(self->_messenger, w);
        }
        return 1;
    case 0:
        if (w != 0) {
            int v = GI(0) / 120 + 1;
            SETI(w->_timerList, 0, v)
            SETB(w->_isFirstList, 0, GPR_00554aac)
            w->_poisonDamage = GI(1);
            if (beMessenger_GetIntCount(self->_messenger) == 3) w->_poisonEndurance = GI(2);
        }
        return 1;
    case 1:
        if (w != 0) {
            int v = GI(0);
            SETI(w->_timerList, 8, v)
            SETB(w->_isFirstList, 8, GPR_00554ab0)
        }
        return 1;
    case 2:
        if (w != 0) {
            int v = GI(0);
            SETI(w->_timerList, 9, v)
            SETB(w->_isFirstList, 9, GPR_00554ab4)
        }
        return 1;
    case 3:
        if (w != 0) {
            int v = GI(0);
            SETI(w->_timerList, 3, v)
            SETB(w->_isFirstList, 3, GPR_00554ab8)
        }
        return 1;
    case 4:
        if (w != 0) {
            SETB(w->_isFirstList, 1, GPR_00554abc)
            { int v = GI(0); SETI(w->_timerList, 1, v) }
            int a = GI(1); int b = GI(2); int c = GI(3); int d = GI(4);
            if (w->_downDataList == 0) FUN_004456c0(self, obj, w);
            SETI(w->_downDataList, 0, a)
            SETI(w->_downDataList, 1, b)
            SETI(w->_downDataList, 2, c)
            SETI(w->_downDataList, 3, d)
            FUN_00445c60(self, obj, w);
        }
        return 1;
    case 5:
        if (w != 0) {
            SETB(w->_isFirstList, 2, GPR_00554ac0)
            { int v = GI(0); SETI(w->_timerList, 2, v) }
            int a = GI(1); int b = GI(2);
            if (w->_downDataList == 0) FUN_004456c0(self, obj, w);
            SETI(w->_downDataList, 4, a)
            SETI(w->_downDataList, 5, b)
            FUN_00445c60(self, obj, w);
        }
        return 1;
    case 7:
        if (w != 0) {
            SETB(w->_isFirstList, 5, GPR_00554ac4)
            { int v = GI(0); SETI(w->_timerList, 5, v) }
            int a = GI(1); int b = GI(2); int c = GI(3); int d = GI(4);
            if (w->_upDataList == 0) FUN_00445990(self, obj, w);
            SETI(w->_upDataList, 0, a)
            SETI(w->_upDataList, 1, b)
            SETI(w->_upDataList, 2, c)
            SETI(w->_upDataList, 3, d)
            FUN_00445c60(self, obj, w);
        }
        return 1;
    case 8:
        if (w != 0) {
            SETB(w->_isFirstList, 6, GPR_00554ac8)
            { int v = GI(0); SETI(w->_timerList, 6, v) }
            int a = GI(1); int b = GI(2); int c = GI(3);
            if (w->_upDataList == 0) FUN_00445990(self, obj, w);
            SETI(w->_upDataList, 4, a)
            SETI(w->_upDataList, 5, b)
            SETI(w->_upDataList, 6, c)
            FUN_00445c60(self, obj, w);
        }
        return 1;
    case 9:
        if (w != 0) {
            SETB(w->_isFirstList, 4, GPR_00554acc)
            { int v = GI(0); SETI(w->_timerList, 4, v) }
            int a = GI(1); int b = GI(2); int c = GI(3); int d = GI(4);
            if (w->_upDataList == 0) FUN_00445990(self, obj, w);
            SETI(w->_upDataList, 7, a)
            SETI(w->_upDataList, 8, b)
            SETI(w->_upDataList, 9, c)
            SETI(w->_upDataList, 10, d)
            FUN_00445c60(self, obj, w);
        }
        return 1;
    case 10:
        if (w != 0) {
            SETB(w->_isFirstList, 7, GPR_00554ad0)
            SETI(w->_timerList, 7, DAT_004cfe00[0])
            if (w->_downDataList == 0) FUN_004456c0(self, obj, w);
        }
        return 1;
    case 11:
        if (w != 0) {
            SETB(w->_isFirstList, 7, GPR_00554ad4)
            SETI(w->_timerList, 7, DAT_004cfe08[0])
            if (w->_downDataList != 0) {
                SETI(w->_downDataList, 6, DAT_004cfe10[0])
            }
        }
        return 1;
    case 6:
        if (w != 0) {
            SETB(w->_isFirstList, 10, GPR_00554ad8)
            { int v = GI(0); SETI(w->_timerList, 10, v) }
        }
        return 1;
    case 12: {
        /* matching construct: the enum result pair is declared after the list holders so the holders
         * take the higher frame slots (+0x9c/+0x98), as in retail */
        int e2;
        int e1;
        bool r = false;
        if (w != 0 && w->_dispRamNoList != 0 && w->_timerList != 0) {
            int s = beMessenger_GetString(self->_messenger, 0);
            igMetaEnum_GetValueByName(&e1, FUN_003c0440(), s, &e2);
            int **ppp; int *pp = &e1; ppp = &pp;
            if (**ppp == DAT_004fb410[0] && W(_timerList)->data[e2] != 0) r = 1;
        }
        beMessenger_AppendBool(self->_messenger, r);
        return 1;
    }
    case 14:
        if (w != 0 && w->_dispRamNoList != 0) {
            FUN_003a8580(obj, &DAT_0051d3f0[0]);
            SETB(w->_isFirstList, 0, GPR_00554adc)
            SETI(w->_timerList, 0, DAT_004cfe18[0])
            FUN_003a8580(obj, &DAT_0051d480[0]);
            SETB(w->_isFirstList, 1, GPR_00554ae0)
            SETI(w->_timerList, 1, DAT_004cfe20[0])
            FUN_003a8580(obj, &DAT_0051d488[0]);
            SETB(w->_isFirstList, 2, GPR_00554ae4)
            SETI(w->_timerList, 2, DAT_004cfe28[0])
            FUN_003a8580(obj, &DAT_0051d490[0]);
            SETB(w->_isFirstList, 5, GPR_00554ae8)
            SETI(w->_timerList, 5, DAT_004cfe30[0])
            FUN_003a8580(obj, &DAT_0051d498[0]);
            SETB(w->_isFirstList, 6, GPR_00554aec)
            SETI(w->_timerList, 6, DAT_004cfe38[0])
            FUN_003a8580(obj, &DAT_0051d4a0[0]);
            SETB(w->_isFirstList, 4, GPR_00554af0)
            SETI(w->_timerList, 4, DAT_004cfe40[0])
            if (w->_upDataList != 0) { FILLI(_upDataList, DAT_004cfe48) }
            if (w->_downDataList != 0) { FILLI(_downDataList, DAT_004cfe50) }
            if (w->_upDataList != 0 || w->_downDataList != 0) FUN_00445c60(self, obj, w);
        }
    case 13:
        if (w != 0 && w->_dispRamNoList != 0) {
            FUN_003a8580(obj, &DAT_0051d450[0]);
            SETB(w->_isFirstList, 8, GPR_00554af4)
            SETI(w->_timerList, 8, DAT_004cfe58[0])
            FUN_003a8580(obj, &DAT_0051d470[0]);
            SETB(w->_isFirstList, 9, GPR_00554af8)
            SETI(w->_timerList, 9, DAT_004cfe60[0])
            FUN_003a8580(obj, &DAT_0051d478[0]);
            SETB(w->_isFirstList, 3, GPR_00554afc)
            SETI(w->_timerList, 3, DAT_004cfe68[0])
            VC(&DAT_0051d460[0]);
        }
        return 1;
    default:
        return 0;
    }
}
