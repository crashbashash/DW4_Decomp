#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#define W(f) ((List *)w->f)
#define SETI(L, I, V) if (((List *)(L))->size != 0 && (I) >= 0 && (I) < ((List *)(L))->size) ((List *)(L))->data[I] = (V);
#define SETB(L, I, V) if (((BList *)(L))->size != 0 && (I) >= 0 && (I) < ((BList *)(L))->size) ((BList *)(L))->data[I] = (V);
#define MS(t) __divdi3((long long)(t) * 1000000000, 60)
#define CALLV(name) ((VC140 *)self)->vX(obj, name)
#define RELEASE(o) if ((o) != 0) { (o)->_refCount = (o)->_refCount - 1; if (((o)->_refCount & 0x7FFFFF) == 0) igObject_Destroy(o); }
#define SETI_445200(L, I, V) if ((L)->_count != 0 && (I) >= 0 && (I) < (L)->_count) ((int *)(L)->_data)[I] = (V);
#define SETB_445200(L, I, V) if ((L)->_count != 0 && (I) >= 0 && (I) < (L)->_count) ((unsigned char *)(L)->_data)[I] = (V);
#define GI(i) beMessenger_GetInt(self->_messenger, i)
#define MKLIST(H, F, CT) { int a = igObject_GetAllocator(self); a = GPR_00554c14 != 0 ? a : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]); { List *u = H.p; RELEASE(u) } H.p = (List *)CT(a); { List *c = H.p; if (c != 0) c->_refCount = c->_refCount + 1; { List *old = W(F); RELEASE(old) } w->F = (int)c; } }
#define SIZEIT(F, N, ES) { List *l = W(F); if (l->size < (N) + 1) List_Reserve(l, N, ES); } { List *l = W(F); if (l->cap >= (N)) l->size = N; else List_Resize(l, N, ES); }
#define FILLI(F, DAT) { int n = W(F)->size; int *d = W(F)->data; int j; for (j = 0; j < n; j++) d[j] = DAT[0]; }
#define FILLB(F, DAT) { BList *l = (BList *)w->F; int n = l->size; unsigned char *d = l->data; int j; for (j = 0; j < n; j++) d[j] = DAT; }
#define VC(name) ((VC140 *)self)->vX(obj, name)

extern "C" int FUN_00236f80(int, int);
extern "C" int beMessenger_AppendInt(...);
extern "C" int beMessenger_DispatchSelected(...);
extern "C" void * beMessenger_GetObject(...);
extern "C" int beMessenger_SelectGroup(...);
extern "C" int beMessenger_SendNamed(...);
extern "C" int FUN_00100610(void **);
extern "C" int FUN_002eb010(int);
extern "C" void * FUN_003a9250(...);
extern "C" int StringChunk_ReleaseHeader(int, int *);
extern "C" int StringPool_Construct(int);
extern "C" int StringPool_Intern(int, int);
extern "C" int beDataBase_GetRecordString(int, int, int *);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" int beMessenger_SelectReceivers(...);
extern "C" int beMessenger_AppendString(...);
extern "C" int beMessenger_AppendVec3(...);
extern "C" int beMessenger_GetObjectCount(...);
extern "C" int igObject_GetAllocator(...);
extern "C" int Matrix44_GetTranslation(...);
extern "C" int beBaseInfoRam_StartTimer(...);
extern "C" int beBaseInfoRam_IsTimerExpired(...);
extern "C" int beBaseInfoRam_RemoveTimer(...);
extern "C" long long __divdi3(...);
extern "C" int FUN_003c03e0(...);
extern "C" int strcmp(...);
extern "C" int beMessenger_AppendFloat(int, float);
extern "C" void * FUN_002caa70(...);
extern "C" int List_Reserve(...);
extern "C" int List_Resize(...);
extern "C" int beMessenger_PopArgContext(...);
extern "C" int beMessenger_PushArgContext(...);
extern "C" void *FUN_002cb0d0(...);
extern "C" int FUN_003c04a0(...);
extern "C" int FUN_003c0440(...);
extern "C" int beMessenger_ResolveEnumValue(...);
extern "C" int beMessenger_ClearObjects(...);
extern "C" int beMessenger_AppendObject(...);
extern "C" int beMessenger_GetInt(...);
extern "C" int beMessenger_GetIntCount(...);
extern "C" int beMessenger_GetString(...);
extern "C" int beMessenger_AppendBool(int, bool);
extern "C" int Gap__Bec__beNDMWMdlPEBaseInfoWork__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWMdlPEBase__vfunc_20(void);
extern "C" void FUN_004432a0(beNDMWShinkaCtrl *self);
extern "C" beDataObjBoolList *igProperty_GetRecordArray(...);
extern "C" igObject *FUN_003c99a0(...);
extern "C" int List_InsertWords(...);
extern "C" int ObjectList_AppendRetained(...);
extern "C" int DAT_0051d1e8[4];
extern "C" int DAT_0051d1a8[4];
extern "C" int DAT_0051d1b8[4];
extern "C" int DAT_0051d1c0[4];
extern "C" int DAT_0051d1d0[4];
extern "C" int DAT_0051d1d8[4];
extern "C" int g_beMessenger_metaObject[4];
extern "C" int g_beNDMWGameRam_metaObject[4];
extern "C" void FUN_00443110(beNDMWShinkaCtrl *arg0, int arg1, int arg2);
extern "C" int FUN_003fa3b0(beNDMWGameRam *, int, int, int);
extern "C" int FUN_003fa850(beNDMWGameRam *, int, int, int);
extern "C" int DAT_00519420[4];
extern "C" int DAT_00519430[4];
extern "C" int DAT_00519438[4];
extern "C" int DAT_0051d1f8[4];
extern "C" int DAT_0051d208[4];
extern "C" int DAT_0051d210[4];
extern "C" int g_stringPool[4];
/* Property record returned by FUN_003a9250: its int list sits at +12. */
struct PropertyIntArray { char pad[12]; igIntList *list; };
extern "C" void FUN_004435c0(beNDMWShinkaObject *out, beNDMWGameRam *ctx, int arg2, int arg3);
struct R { char p[16]; int f16; };
extern "C" int DAT_004cfc80[4];
extern "C" int DAT_004cfca0[4];
extern "C" int DAT_0051d3a0[4];
extern "C" int DAT_0051d3a8[4];
extern "C" int DAT_0051d3b8[4];
extern "C" int DAT_0051d3c8[4];
extern "C" int DAT_0051d3d8[4];
extern "C" float g_vec3Zero[4];
extern "C" float DAT_004e105c[4];
extern "C" float DAT_004e1060[4];
extern "C" int g_propertyNameField[4];
extern "C" int g_defaultAllocatorSelector[4];
extern "C" unsigned char GPR_00554c14;
struct Rel { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
struct V3 { float x, y, z; };
extern "C" int FUN_00443900(beNDMWMdlPEBase *arg0, beBaseInfoRam *arg1, int arg2, int arg3, int arg4, bool arg5);
struct igResult { int w0; bool operator==(const igResult &o) const { return w0 == o.w0; } };
typedef struct List : public igObject { int size; int cap; int *data; } List;
extern "C" List *beBaseInfoDataList_Create(...);
typedef struct BList : public igObject { int size; int cap; unsigned char *data; } BList;
typedef struct OList : public igObject { int size; int cap; beModelCtrlMoveObject **data; } OList;
typedef struct Param : public igObject { int pad8; int value; } Param;
typedef struct Entry { int w0, w1, w2, w3, w4; beNDMWMdlPEBaseInfoWork *work; } Entry;
typedef struct Model : public igObject { int id; char pad12[28]; List *props; } Model;
extern "C" Entry * igProperty_FindByName(...);
extern "C" Param *igProperty_GetRecord(...);
extern "C" igResult igMetaEnum_GetValueByName(...);
extern "C" int DAT_004cfc50[4];
extern "C" int DAT_004cfcb8[4];
extern "C" int DAT_004cfcc0[4];
extern "C" int DAT_004cfcc8[4];
extern "C" int DAT_004cfcd0[4];
extern "C" int DAT_004cfcd8[4];
extern "C" int DAT_004cfce0[4];
extern "C" int DAT_004cfce8[4];
extern "C" int DAT_004cfcf0[4];
extern "C" int DAT_004cfcf8[4];
extern "C" int DAT_004cfd00[4];
extern "C" int DAT_004cfd08[4];
extern "C" int DAT_004cfd10[4];
extern "C" int DAT_004cfd18[4];
extern "C" int DAT_004cfd20[4];
extern "C" int DAT_004cfd28[4];
extern "C" int DAT_004cfd30[4];
extern "C" int DAT_004cfd38[4];
extern "C" int DAT_004cfd40[4];
extern "C" int DAT_004cfd48[4];
extern "C" int DAT_004cfd50[4];
extern "C" int DAT_004cfd58[4];
extern "C" int DAT_004cfd60[4];
extern "C" int DAT_004cfd68[4];
extern "C" int DAT_004cfd70[4];
extern "C" int DAT_004cfd78[4];
extern "C" int DAT_004cfd80[4];
extern "C" int DAT_004cfd88[4];
extern "C" int DAT_004cfd90[4];
extern "C" int DAT_004cfd98[4];
extern "C" int DAT_004cfda0[4];
extern "C" int DAT_004cfda8[4];
extern "C" int DAT_004cfdb0[4];
extern "C" igResult g_statusSucceeded;
extern "C" int DAT_0051d3e8[4];
extern "C" int DAT_0051d3f0[4];
extern "C" int DAT_0051d3f8[4];
extern "C" int DAT_0051d408[4];
extern "C" int DAT_0051d410[4];
extern "C" int DAT_0051d420[4];
extern "C" int DAT_0051d430[4];
extern "C" int DAT_0051d438[4];
extern "C" int DAT_0051d448[4];
extern "C" int DAT_0051d450[4];
extern "C" int DAT_0051d458[4];
extern "C" int DAT_0051d460[4];
extern "C" int DAT_0051d468[4];
extern "C" int DAT_0051d470[4];
extern "C" int DAT_0051d478[4];
extern "C" int DAT_0051d480[4];
extern "C" int DAT_0051d488[4];
extern "C" int DAT_0051d490[4];
extern "C" int DAT_0051d498[4];
extern "C" int DAT_0051d4a0[4];
extern "C" int DAT_0051d4a8[4];
extern "C" int DAT_0051d4b0[4];
extern "C" int DAT_0051d4b8[4];
extern "C" int DAT_0051d4c8[4];
extern "C" unsigned char GPR_00554a78;
extern "C" unsigned char GPR_00554a7c;
extern "C" unsigned char GPR_00554a80;
extern "C" unsigned char GPR_00554a84;
extern "C" unsigned char GPR_00554a88;
extern "C" unsigned char GPR_00554a8c;
extern "C" unsigned char GPR_00554a90;
extern "C" unsigned char GPR_00554a94;
extern "C" unsigned char GPR_00554a98;
extern "C" unsigned char GPR_00554a9c;
/* Owning stack reference to the freshly created property list; released on scope exit (reference
 * count in the low 23 bits of _refCount). */

class VC140 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void vX(Model *, void *); };
extern "C" void Gap__Bec__beNDMWMdlPEBase__vfunc_46(beNDMWMdlPEBase *self, Model *obj);
extern "C" int DAT_004cfc74[4];
extern "C" int DAT_004cfdb8[4];
extern "C" int DAT_004cfdc0[4];
extern "C" int DAT_004cfdc8[4];
extern "C" int DAT_004cfdd0[4];
extern "C" unsigned char GPR_00554aa0;
extern "C" unsigned char GPR_00554aa4;
struct HpWord { char pad[12]; int f12; };
class MessengerVirt { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual int vX(void *, void *); };
extern "C" void FUN_00445200(beNDMWMdlPEBase *arg0, beBaseInfoRam *arg1);
typedef struct Obj { char pad[12]; igObject *f12; } Obj;
extern "C" int DAT_004cfdd8[4];
extern "C" int DAT_0051d4d8[4];
extern "C" void FUN_004456c0(beNDMWMdlPEBase *arg0, beBaseInfoRam *arg1, beNDMWMdlPEBaseInfoWork *arg2);
extern "C" int DAT_004cfde0[4];
extern "C" int DAT_0051d4e8[4];
extern "C" void FUN_00445990(beNDMWMdlPEBase *arg0, beBaseInfoRam *arg1, beNDMWMdlPEBaseInfoWork *arg2);
struct A1 { char pad[8]; int f8; };
extern "C" int DAT_0051d4f0[4];
extern "C" int DAT_0051d500[4];
extern "C" void FUN_00445c60(beNDMWMdlPEBase *arg0, struct A1 *arg1, beNDMWMdlPEBaseInfoWork *arg2);
class igResult;
extern "C" int DAT_004cfde8[4];
extern "C" int DAT_004cfdf0[4];
extern "C" int DAT_004cfdf8[4];
extern "C" int DAT_004cfe00[4];
extern "C" int DAT_004cfe08[4];
extern "C" int DAT_004cfe10[4];
extern "C" int DAT_004cfe18[4];
extern "C" int DAT_004cfe20[4];
extern "C" int DAT_004cfe28[4];
extern "C" int DAT_004cfe30[4];
extern "C" int DAT_004cfe38[4];
extern "C" int DAT_004cfe40[4];
extern "C" int DAT_004cfe48[4];
extern "C" int DAT_004cfe50[4];
extern "C" int DAT_004cfe58[4];
extern "C" int DAT_004cfe60[4];
extern "C" int DAT_004cfe68[4];
extern "C" unsigned char GPR_00554aa8;
extern "C" unsigned char GPR_00554aac;
extern "C" unsigned char GPR_00554ab0;
extern "C" unsigned char GPR_00554ab4;
extern "C" unsigned char GPR_00554ab8;
extern "C" unsigned char GPR_00554abc;
extern "C" unsigned char GPR_00554ac0;
extern "C" unsigned char GPR_00554ac4;
extern "C" unsigned char GPR_00554ac8;
extern "C" unsigned char GPR_00554acc;
extern "C" unsigned char GPR_00554ad0;
extern "C" unsigned char GPR_00554ad4;
extern "C" unsigned char GPR_00554ad8;
extern "C" unsigned char GPR_00554adc;
extern "C" unsigned char GPR_00554ae0;
extern "C" unsigned char GPR_00554ae4;
extern "C" unsigned char GPR_00554ae8;
extern "C" unsigned char GPR_00554aec;
extern "C" unsigned char GPR_00554af0;
extern "C" unsigned char GPR_00554af4;
extern "C" unsigned char GPR_00554af8;
extern "C" unsigned char GPR_00554afc;
/* Owning stack reference to the freshly created property data list; released at the end of the
 * full expression that stores it (reference count in the low 23 bits of _refCount). */

/* Owning stack reference that carries each new int list of the work while it is sized and filled:
 * starts empty, is handed one created list after another (MKLIST drops the previous one first) and
 * releases the last on scope exit. */
class IntListRef {
public:
    List *p;
    IntListRef(List *o) : p(o) {}
    ~IntListRef() { List *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* Same role for the work's bool list. */
class BoolListRef {
public:
    List *p;
    BoolListRef(List *o) : p(o) {}
    ~BoolListRef() { List *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* Store a freshly created data list in the model, taking the model's share and dropping the previous
 * list; the caller passes the list as a temporary holder that gives up the creating share at the end of
 * the full expression (matching construct: a temporary takes its frame slot after the named locals). */
struct DataList { static inline void store(Model *obj, const igSmartPointer<List> &list) {
    List *created = list.p;
    List *old;
    if (created != 0) created->_refCount = created->_refCount + 1;
    old = obj->props;
    RELEASE(old)
    obj->props = created;
} };
extern "C" int Gap__Bec__beNDMWMdlPEBase__vfunc_47(beNDMWMdlPEBase *self, Model *obj, int name);
extern "C" int Gap__Core__igObject__vfunc_08__002ff0f0(beNDMWMdlPEBaseInfoWork *);
extern "C" int DAT_004cfe70[4];
extern "C" int DAT_004cfe78[4];
extern "C" void Gap__Bec__beNDMWMdlPEBaseInfoWork__vfunc_8(beNDMWMdlPEBaseInfoWork *arg0);
extern "C" int FUN_00447b00(beNDMWMdlPEBaseInfoWork *owner);
extern "C" int DAT_004cfe80[4];
extern "C" void FUN_00447b40(beNDMWMdlPEBaseInfoWork *owner, void *arg);
extern "C" int g_beNDMWMdlPEBaseInfoWork_metaObject[4];
extern "C" int g_beNDMWMdlPEBase_metaObject[4];

void FUN_00443110(beNDMWShinkaCtrl *arg0, int arg1, int arg2) {
    igObject *t;
    igObject *a0;
    arg0->_playerNo = arg2;
    arg0->_messenger = FUN_00236f80(arg1, g_beMessenger_metaObject[0]);
    arg0->_gameRam = FUN_00236f80(arg1, g_beNDMWGameRam_metaObject[0]);
    beMessenger_SendNamed(arg0->_messenger, DAT_0051d1a8, DAT_0051d1b8, 0, DAT_0051d1c0);
    t = (igObject *)((int *)beMessenger_GetObject(arg0->_messenger, 0));
    if (t != 0) {
        t->_refCount = t->_refCount + 1;
    }
    a0 = (igObject *)arg0->_dBShinka;
    if (a0 != 0) {
        a0->_refCount = a0->_refCount - 1;
        if ((a0->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(a0);
        }
    }
    arg0->_dBShinka = (int)t;
    beMessenger_SelectGroup(arg0->_messenger, DAT_0051d1d0);
    beMessenger_AppendInt(arg0->_messenger, arg2);
    beMessenger_DispatchSelected(arg0->_messenger, DAT_0051d1d8);
    t = (igObject *)((int *)beMessenger_GetObject(arg0->_messenger, 0));
    if (t != 0) {
        t->_refCount = t->_refCount + 1;
    }
    a0 = (igObject *)arg0->_playerParameter;
    if (a0 != 0) {
        a0->_refCount = a0->_refCount - 1;
        if ((a0->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(a0);
        }
    }
    arg0->_playerParameter = (int)t;
    FUN_004432a0(arg0);
}

/* Owning stack reference to the evolution entry under construction; released on scope exit
 * (reference count in the low 23 bits of _refCount). */

void FUN_004432a0(beNDMWShinkaCtrl *self) {
    int ia;
    igObject *obj;
    igObjectList *l4;
    igObject *o3;
    igBoolList *s2;
    igObjectList *lst;
    int n;
    int i;
    int cnt;
    int j;
    int idx;
    int base;
    int alloc;

    lst = (igObjectList *)self->_list;
    n = lst->_count;
    for (i = 0; i < n; i++) {
        obj = ((igObject **)lst->_data)[i];
        if (obj != 0) {
            obj->_refCount = obj->_refCount - 1;
            if ((obj->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(obj);
            }
        }
    }
    cnt = lst->_count;
    for (j = 0; j < cnt; j++) {
        ((igObject **)lst->_data)[j] = 0;
    }
    lst->_count = 0;
    s2 = (igBoolList *)igProperty_GetRecordArray(self->_playerParameter, &DAT_0051d1e8[0])->_data;
    FUN_003a9250(self->_playerParameter, &DAT_0051d1f8[0]);
    for (idx = 0; idx < 16; idx++) {
        if ((*(unsigned char **)&s2->_data)[idx] != 0) {
            base = igObject_GetAllocator(self);
            if (GPR_00554c14 != 0) {
                alloc = base;
            } else {
                alloc = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
            }
            igSmartPointer<igObject> entry(FUN_003c99a0(alloc));
            igObject *slotB[1];
            FUN_004435c0((beNDMWShinkaObject *)entry.p, (beNDMWGameRam *)self->_gameRam, self->_playerNo, idx);
            if (idx == 3) {
                l4 = (igObjectList *)self->_list;
                o3 = (igObject *)slotB; /* matching construct: hand spelling — one-element array, the retained word is re-read through its address */
                slotB[0] = entry.p;
                o3 = *(igObject **)o3;
                if (o3 != 0) {
                    o3->_refCount = o3->_refCount + 1;
                }
                List_InsertWords(l4, 0, 1, slotB);
            } else {
                ObjectList_AppendRetained((igObjectList *)self->_list, entry.p);
            }
        }
    }
}

void FUN_004435c0(beNDMWShinkaObject *out, beNDMWGameRam *ctx, int arg2, int arg3) {
    igObject *o;
    igObject *old;
    int s;
    int pool;
    int ref;
    int oldref;
    int *hdr;
    int cnt;
    struct PropertyIntArray *t1;
    struct PropertyIntArray *t2;
    igIntList *sd;
    out->_id = arg3;
    if (ctx->_dBShinka == 0) {
        beMessenger_SendNamed(ctx->_messenger, &DAT_00519438[0], &DAT_00519430[0], 0, &DAT_00519420[0]);
        o = ((igObject *)beMessenger_GetObject(ctx->_messenger, 0));
        if (o != 0) {
            o->_refCount = o->_refCount + 1;
        }
        old = (igObject *)ctx->_dBShinka;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(old);
            }
        }
        ctx->_dBShinka = (int)o;
    }
    s = beDataBase_GetRecordString(ctx->_dBShinka, arg3, &DAT_0051d208[0]);
    if (g_stringPool[0] == 0) {
        pool = FUN_002eb010(16);
        if (pool != 0)
            pool = StringPool_Construct(pool);
        g_stringPool[0] = pool;
    }
    ref = StringPool_Intern(g_stringPool[0], s);
    oldref = out->_name;
    if (oldref != 0) {
        hdr = (int *)(oldref - 8);
        cnt = *(int *)(oldref - 4) - 1;
        *(int *)(oldref - 4) = cnt;
        if (cnt == 0)
            StringChunk_ReleaseHeader(*hdr, hdr);
    }
    out->_name = ref;
    t1 = ((struct PropertyIntArray *)FUN_003a9250(((int *)((igIntList *)ctx->_playerDataListList)->_data)[arg2], &DAT_0051d1f8[0]));
    out->_level = ((int *)t1->list->_data)[arg3];
    out->_hpMax = FUN_003fa3b0(ctx, arg2, arg3, 1);
    out->_mpMax = FUN_003fa3b0(ctx, arg2, arg3, 0);
    out->_tsuyosa = FUN_003fa850(ctx, arg2, arg3, 0);
    out->_mamori = FUN_003fa850(ctx, arg2, arg3, 1);
    out->_kashikosa = FUN_003fa850(ctx, arg2, arg3, 2);
    out->_seishin = FUN_003fa850(ctx, arg2, arg3, 3);
    out->_subayasa = FUN_003fa850(ctx, arg2, arg3, 4);
    t2 = ((struct PropertyIntArray *)FUN_003a9250(((int *)((igIntList *)ctx->_playerDataListList)->_data)[arg2], &DAT_0051d210[0]));
    sd = t2->list;
    out->_blunt = *(int *)(sd->_data + arg3 * 36);
    out->_slash = *(int *)(sd->_data + (arg3 * 9 + 1) * 4);
    out->_stab = *(int *)(sd->_data + (arg3 * 9 + 2) * 4);
    out->_bash = *(int *)(sd->_data + (arg3 * 9 + 3) * 4);
    out->_shot = *(int *)(sd->_data + (arg3 * 9 + 4) * 4);
    out->_crush = *(int *)(sd->_data + (arg3 * 9 + 5) * 4);
    out->_blast = *(int *)(sd->_data + (arg3 * 9 + 6) * 4);
    out->_heal = *(int *)(sd->_data + (arg3 * 9 + 7) * 4);
    out->_force = *(int *)(sd->_data + (arg3 * 9 + 8) * 4);
}

/* Owning stack reference to the freshly created property list; released on scope exit once the ram
 * holds its own reference (reference count in the low 23 bits of _refCount). */

int FUN_00443900(beNDMWMdlPEBase *arg0, beBaseInfoRam *arg1, int arg2, int arg3, int arg4, bool arg5) {
    igObject *s0;
    R *r;
    beBaseInfoRam *o;
    V3 t, c1, c2, c3;
    if (arg1->_dataList == 0) {
        int alloc = igObject_GetAllocator(arg1);
        int a;
        if (GPR_00554c14 != 0) {
            a = alloc;
        } else {
            a = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        }
        igSmartPointer<List> created(beBaseInfoDataList_Create(a));
        s0 = created.p;
        if (s0 != 0) {
            s0->_refCount++;
        }
        Rel::go((igObject *)arg1->_dataList);
        arg1->_dataList = (int)s0;
    }
    r = ((R *)igProperty_FindByName((void *)arg1->_dataList, g_propertyNameField[0], DAT_0051d3a0));
    Matrix44_GetTranslation(r->f16 + 32, &t);
    if (arg3 == -1) {
        beMessenger_SendNamed(arg0->_messenger, DAT_0051d3a8, arg2, -1, DAT_0051d3b8);
        if (beMessenger_GetObjectCount(arg0->_messenger) == 0) goto fail;
        {
            o = ((beBaseInfoRam *)beMessenger_GetObject(arg0->_messenger, 0));
            beMessenger_SelectReceivers(arg0->_messenger, DAT_0051d3a8, arg2, o->_ramNo);
            beMessenger_AppendString(arg0->_messenger, DAT_004cfc80[arg4]);
            c1 = t;
            beMessenger_AppendVec3(arg0->_messenger, &c1);
            beMessenger_DispatchSelected(arg0->_messenger, DAT_0051d3c8);
            return o->_ramNo;
        }
        goto fail;
    }
    if (arg5) {
        beMessenger_SendNamed(arg0->_messenger, DAT_0051d3a8, arg2, arg3, DAT_004cfca0[arg4]);
    }
    beMessenger_SelectReceivers(arg0->_messenger, DAT_0051d3a8, arg2, arg3);
    c2 = t;
    beMessenger_AppendVec3(arg0->_messenger, &c2);
    c3.x = g_vec3Zero[0];
    c3.y = DAT_004e105c[0];
    c3.z = DAT_004e1060[0];
    beMessenger_AppendVec3(arg0->_messenger, &c3);
    beMessenger_DispatchSelected(arg0->_messenger, DAT_0051d3d8);
    return arg3;
fail:
    return -1;
}

static inline void ensureProps(Model *obj)
{
    if (obj->props == 0) {
        int allocator = igObject_GetAllocator(obj);
        igSmartPointer<List> holder(beBaseInfoDataList_Create(GPR_00554c14 != 0 ? allocator : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0])));
        List *created = holder.p;
        if (created != 0) created->_refCount = created->_refCount + 1;
        List *old = obj->props;
        RELEASE(old)
        obj->props = created;
    }
}

void Gap__Bec__beNDMWMdlPEBase__vfunc_46(beNDMWMdlPEBase *self, Model *obj) {
    beNDMWMdlPEBaseInfoWork *w;
    List *l;
    int n;
    int *d;
    int j;
    int enumExtra;
    ensureProps(obj);
    w = igProperty_FindByName(obj->props, g_propertyNameField[0], &DAT_0051d3a0[0])->work;
    if (w->_timerList != 0) {
        if (((Param *)w->_hp)->value == 0) {
            int i = 0;
            int off = 0;
            int *p = &DAT_004cfc50[0];
            do {
                int v = *(int *)&((BList *)w->_dispRamNoList)->data[off];
                if (v != -1) beMessenger_SendNamed(self->_messenger, &DAT_0051d3a8[0], *p, v, &DAT_0051d3e8[0]);
                i++;
                off += 4;
                p += 1;
            } while (i < 12);
            { List *l1 = W(_timerList); int n1 = l1->size; int *d1 = l1->data; int j1;
              for (j1 = 0; j1 < n1; j1++) { d1[j1] = DAT_004cfcb8[0]; } }
            { List *l2 = W(_dispRamNoList); int n2 = l2->size; int *d2 = l2->data; int j2;
              for (j2 = 0; j2 < n2; j2++) { d2[j2] = DAT_004cfcc0[0]; } }
            return;
        }
        if (w->_messenger == 0) w->_messenger = self->_messenger;
        if (w->_isOnCtrl != 0 && W(_timerList)->data[0] != 0) {
            if (((BList *)w->_isFirstList)->data[0] != 0) {
                beBaseInfoRam_StartTimer(obj, &DAT_0051d3f0[0], 2000000000);
                { int v_ = W(_timerList)->data[0] - 1; SETI(w->_timerList, 0, v_) }
                SETB(w->_isFirstList, 0, GPR_00554a78)
            }
            if (beBaseInfoRam_IsTimerExpired(obj, &DAT_0051d3f0[0]) != 0) {
                Param *hp = (Param *)w->_hp;
                int v = hp->value - w->_poisonDamage;
                if (v >= 0) { v = (int)v; } else { v = 0; } hp->value = v;
                if (w->_isPlayer != 0) {
                    beMessenger_SelectReceivers(self->_messenger, &DAT_0051d3f8[0], &DAT_0051d408[0], obj->id);
                    beMessenger_AppendFloat(self->_messenger, 100.0f * (float)((Param *)w->_hp)->value / (float)((Param *)w->_mHp)->value);
                    beMessenger_DispatchSelected(self->_messenger, &DAT_0051d410[0]);
                    beMessenger_SelectReceivers(self->_messenger, &DAT_0051d420[0], &DAT_0051d430[0], obj->id);
                    beMessenger_AppendInt(self->_messenger, ((Param *)w->_hp)->value);
                    beMessenger_DispatchSelected(self->_messenger, &DAT_0051d438[0]);
                }
                hp = (Param *)w->_hp;
                if (hp->value <= 0) {
                    if (w->_isPlayer != 0) {
                        CALLV(&DAT_0051d448[0]);
                        beBaseInfoRam_RemoveTimer(obj, &DAT_0051d3f0[0]);
                        SETI(w->_timerList, 0, DAT_004cfcc8[0])
                    } else {
                        hp->value = 1;
                        beBaseInfoRam_RemoveTimer(obj, &DAT_0051d3f0[0]);
                        SETI(w->_timerList, 0, DAT_004cfcd0[0])
                    }
                } else {
                    { int v_ = W(_timerList)->data[0] - 1; SETI(w->_timerList, 0, v_) }
                    if (W(_timerList)->data[0] <= 0) {
                        beBaseInfoRam_RemoveTimer(obj, &DAT_0051d3f0[0]);
                        SETI(w->_timerList, 0, DAT_004cfcd8[0])
                    } else {
                        beBaseInfoRam_StartTimer(obj, &DAT_0051d3f0[0], 2000000000);
                    }
                }
            }
        }
        if (w->_isOnCtrl != 0 && W(_timerList)->data[8] != 0) {
            if (((BList *)w->_isFirstList)->data[8] != 0) {
                beBaseInfoRam_StartTimer(obj, &DAT_0051d450[0], MS(W(_timerList)->data[8]));
                if (strcmp(w->_seqCodeName, &DAT_0051d458[0]) != 0) CALLV(&DAT_0051d458[0]);
                SETB(w->_isFirstList, 8, GPR_00554a7c)
            }
            if (beBaseInfoRam_IsTimerExpired(obj, &DAT_0051d450[0]) != 0) {
                CALLV(&DAT_0051d460[0]);
                beBaseInfoRam_RemoveTimer(obj, &DAT_0051d450[0]);
                SETI(w->_timerList, 8, DAT_004cfce0[0])
            }
        }
        if (w->_isOnCtrl != 0 && W(_timerList)->data[9] != 0 && strcmp(w->_seqCodeName, &DAT_0051d468[0]) == 0) {
            if (((BList *)w->_isFirstList)->data[9] != 0) {
                beBaseInfoRam_StartTimer(obj, &DAT_0051d470[0], MS(W(_timerList)->data[9]));
                SETB(w->_isFirstList, 9, GPR_00554a80)
            }
            if (beBaseInfoRam_IsTimerExpired(obj, &DAT_0051d470[0]) != 0) {
                SETI(w->_timerList, 9, DAT_004cfce8[0])
                beBaseInfoRam_RemoveTimer(obj, &DAT_0051d470[0]);
                CALLV(&DAT_0051d460[0]);
            }
        }
        if (w->_isOnCtrl != 0 && W(_timerList)->data[3] != 0) {
            if (((BList *)w->_isFirstList)->data[3] != 0) {
                beBaseInfoRam_StartTimer(obj, &DAT_0051d478[0], MS(W(_timerList)->data[3]));
                SETB(w->_isFirstList, 3, GPR_00554a84)
            }
            if (beBaseInfoRam_IsTimerExpired(obj, &DAT_0051d478[0]) != 0) {
                beBaseInfoRam_RemoveTimer(obj, &DAT_0051d478[0]);
                SETI(w->_timerList, 3, DAT_004cfcf0[0])
                CALLV(&DAT_0051d460[0]);
            } else {
                if (!(igMetaEnum_GetValueByName(FUN_003c03e0(), w->_seqCodeName, &enumExtra) == g_statusSucceeded)) {
                    OList *moves = (OList *)w->_moveObjectList;
                    int n = moves->size;
                    int i;
                    for (i = 0; i < n; i++) {
                        if (i != 1) {
                            beModelCtrlMoveObject *o = moves->data[i];
                            o->_isRun = 0;
                            o->_speed = 0;
                        }
                    }
                }
            }
        }
        if (w->_isOnCtrl != 0 && W(_timerList)->data[1] != 0) {
            if (((BList *)w->_isFirstList)->data[1] != 0) {
                beBaseInfoRam_StartTimer(obj, &DAT_0051d480[0], MS(W(_timerList)->data[1]));
                SETB(w->_isFirstList, 1, GPR_00554a88)
            }
            if (beBaseInfoRam_IsTimerExpired(obj, &DAT_0051d480[0]) != 0) {
                beBaseInfoRam_RemoveTimer(obj, &DAT_0051d480[0]);
                SETI(w->_timerList, 1, DAT_004cfcf8[0])
                SETI(w->_downDataList, 0, DAT_004cfd00[0])
                SETI(w->_downDataList, 1, DAT_004cfd08[0])
                SETI(w->_downDataList, 2, DAT_004cfd10[0])
                SETI(w->_downDataList, 3, DAT_004cfd18[0])
                FUN_00445c60(self, (A1 *)obj, w);
            }
        }
        if (w->_isOnCtrl != 0 && W(_timerList)->data[2] != 0) {
            if (((BList *)w->_isFirstList)->data[2] != 0) {
                beBaseInfoRam_StartTimer(obj, &DAT_0051d488[0], MS(W(_timerList)->data[2]));
                SETB(w->_isFirstList, 2, GPR_00554a8c)
            }
            if (beBaseInfoRam_IsTimerExpired(obj, &DAT_0051d488[0]) != 0) {
                beBaseInfoRam_RemoveTimer(obj, &DAT_0051d488[0]);
                SETI(w->_timerList, 2, DAT_004cfd20[0])
                SETI(w->_downDataList, 4, DAT_004cfd28[0])
                SETI(w->_downDataList, 5, DAT_004cfd30[0])
                FUN_00445c60(self, (A1 *)obj, w);
            }
        }
        if (w->_isOnCtrl != 0 && W(_timerList)->data[5] != 0) {
            if (((BList *)w->_isFirstList)->data[5] != 0) {
                beBaseInfoRam_StartTimer(obj, &DAT_0051d490[0], MS(W(_timerList)->data[5]));
                SETB(w->_isFirstList, 5, GPR_00554a90)
            }
            if (beBaseInfoRam_IsTimerExpired(obj, &DAT_0051d490[0]) != 0) {
                beBaseInfoRam_RemoveTimer(obj, &DAT_0051d490[0]);
                SETI(w->_timerList, 5, DAT_004cfd38[0])
                SETI(w->_upDataList, 0, DAT_004cfd40[0])
                SETI(w->_upDataList, 1, DAT_004cfd48[0])
                SETI(w->_upDataList, 2, DAT_004cfd50[0])
                SETI(w->_upDataList, 3, DAT_004cfd58[0])
                FUN_00445c60(self, (A1 *)obj, w);
            }
        }
        if (w->_isOnCtrl != 0 && W(_timerList)->data[6] != 0) {
            if (((BList *)w->_isFirstList)->data[6] != 0) {
                beBaseInfoRam_StartTimer(obj, &DAT_0051d498[0], MS(W(_timerList)->data[6]));
                SETB(w->_isFirstList, 6, GPR_00554a94)
            }
            if (beBaseInfoRam_IsTimerExpired(obj, &DAT_0051d498[0]) != 0) {
                beBaseInfoRam_RemoveTimer(obj, &DAT_0051d498[0]);
                SETI(w->_timerList, 6, DAT_004cfd60[0])
                SETI(w->_upDataList, 4, DAT_004cfd68[0])
                SETI(w->_upDataList, 5, DAT_004cfd70[0])
                SETI(w->_upDataList, 6, DAT_004cfd78[0])
                FUN_00445c60(self, (A1 *)obj, w);
            }
        }
        if (w->_isOnCtrl != 0 && W(_timerList)->data[4] != 0) {
            if (((BList *)w->_isFirstList)->data[4] != 0) {
                beBaseInfoRam_StartTimer(obj, &DAT_0051d4a0[0], MS(W(_timerList)->data[4]));
                SETB(w->_isFirstList, 4, GPR_00554a98)
            }
            if (beBaseInfoRam_IsTimerExpired(obj, &DAT_0051d4a0[0]) != 0) {
                beBaseInfoRam_RemoveTimer(obj, &DAT_0051d4a0[0]);
                SETI(w->_timerList, 4, DAT_004cfd80[0])
                SETI(w->_upDataList, 7, DAT_004cfd88[0])
                SETI(w->_upDataList, 8, DAT_004cfd90[0])
                SETI(w->_upDataList, 9, DAT_004cfd98[0])
                SETI(w->_upDataList, 10, DAT_004cfda0[0])
                FUN_00445c60(self, (A1 *)obj, w);
            }
        }
        if (w->_isOnCtrl != 0 && W(_timerList)->data[7] != 0) {
            if (((BList *)w->_isFirstList)->data[7] != 0) {
                SETI(w->_downDataList, 6, DAT_004cfda8[0])
                beBaseInfoRam_StartTimer(obj, &DAT_0051d4a8[0], 0);
                SETB(w->_isFirstList, 7, GPR_00554a9c)
            }
            if (beBaseInfoRam_IsTimerExpired(obj, &DAT_0051d4a8[0]) != 0) {
                int t120;
                { List *L_ = W(_downDataList); int v_ = L_->data[6] + 4; SETI(L_, 6, v_) }
                beMessenger_SelectGroup(self->_messenger, &DAT_0051d4b0[0]);
                beMessenger_AppendInt(self->_messenger, obj->id);
                beMessenger_DispatchSelected(self->_messenger, &DAT_0051d4b8[0]);
                t120 = igProperty_GetRecord(((int)beMessenger_GetObject(self->_messenger, 0)), &DAT_0051d4c8[0])->value * 120;
                beBaseInfoRam_StartTimer(obj, &DAT_0051d4a8[0], MS(t120));
                FUN_00445c60(self, (A1 *)obj, w);
            }
        }
        {
            bool flag = false;
            int count = 0;
            int i = 0;
            do {
                int r;
                if (i == 11) { int fv = flag; SETI(w->_timerList, i, fv) }
                if (W(_timerList)->data[i] != 0) {
                    if (i < 8) {
                        bool changed = false;
                        if (count != W(_dispPosNoList)->data[i]) {
                            SETI(w->_dispPosNoList, i, count)
                            changed = true;
                        }
                        r = FUN_00443900((beNDMWMdlPEBase *)self, (beBaseInfoRam *)obj, DAT_004cfc50[i], W(_dispRamNoList)->data[i], count, changed);
                        count++;
                    } else if (i != 10) {
                        r = FUN_00443900((beNDMWMdlPEBase *)self, (beBaseInfoRam *)obj, DAT_004cfc50[i], W(_dispRamNoList)->data[i], 0, 0);
                    } else {
                        r = FUN_00443900((beNDMWMdlPEBase *)self, (beBaseInfoRam *)obj, DAT_004cfc50[i], W(_dispRamNoList)->data[i], W(_timerList)->data[10] - 1, 0);
                    }
                    SETI(w->_dispRamNoList, i, r)
                    if (i < 8) flag = true;
                } else {
                    int v = W(_dispRamNoList)->data[i];
                    if (v != -1) {
                        beMessenger_SendNamed(self->_messenger, &DAT_0051d3a8[0], DAT_004cfc50[i], v, &DAT_0051d3e8[0]);
                        SETI(w->_dispRamNoList, i, DAT_004cfdb0[0])
                    }
                }
                i++;
            } while (i < 12);
        }
    }
}

/* Owning stack reference to the freshly created data list; released on scope exit (reference count
 * in the low 23 bits of _refCount). */



void FUN_00445200(beNDMWMdlPEBase *arg0, beBaseInfoRam *arg1) {
    void *al;
    beNDMWMdlPEBaseInfoWork *st;
    igObject *s1;
    igObject *old;
    if (arg1->_dataList == 0) {
        al = ((void *)igObject_GetAllocator(arg1));
        if (GPR_00554c14 != 0) {
            al = (void *)(int)al;
        } else {
            al = ((void *)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]));
        }
        igSmartPointer<List> ref(beBaseInfoDataList_Create(al));
        s1 = ref.p;
        if (s1 != 0) s1->_refCount = s1->_refCount + 1;
        old = (igObject *)arg1->_dataList;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
        }
        arg1->_dataList = (int)s1;
    }
    st = *(beNDMWMdlPEBaseInfoWork **)((char *)((void *)igProperty_FindByName((igObject *)arg1->_dataList, g_propertyNameField[0], &DAT_0051d3a0[0])) + 20);
    if (st->_dispRamNoList != 0) {
        if (((igIntList *)st->_dispRamNoList)->_count != 0 && ((HpWord *)st->_hp)->f12 == 0) {
            int i;
            for (i = 0; i < 12; i++) {
                int v = ((int *)((igIntList *)st->_dispRamNoList)->_data)[i];
                if (v != -1) beMessenger_SendNamed(arg0->_messenger, &DAT_0051d3a8[0], DAT_004cfc50[i], v, &DAT_0051d3e8[0]);
            }
            {
                igIntList *l = (igIntList *)st->_timerList;
                int n = l->_count;
                int *q = (int *)l->_data;
                int j;
                for (j = 0; j < n; j++) q[j] = DAT_004cfdb8[0];
            }
            {
                igIntList *l2 = (igIntList *)st->_dispRamNoList;
                int n2 = l2->_count;
                int *q2 = (int *)l2->_data;
                int k;
                for (k = 0; k < n2; k++) q2[k] = DAT_004cfdc0[0];
            }
            return;
        }
        if (((igIntList *)st->_timerList)->_count != 0) {
            if (((int *)((igIntList *)st->_timerList)->_data)[8] != 0 && strcmp((char *)st->_seqCodeName, &DAT_0051d458[0]) != 0) {
                beBaseInfoRam_RemoveTimer(arg1, &DAT_0051d450[0]);
                SETB_445200((igUnsignedCharList *)st->_isFirstList, 8, GPR_00554aa0)
                SETI_445200((igIntList *)st->_timerList, 8, DAT_004cfdc8[0])
            }
            if (((int *)((igIntList *)st->_timerList)->_data)[9] != 0) {
                if (strcmp((char *)st->_seqCodeName, &DAT_0051d460[0]) == 0) {
                    ((MessengerVirt *)arg0)->vX(arg1, &DAT_0051d468[0]);
                    return;
                }
                if (strcmp((char *)st->_seqCodeName, &DAT_0051d468[0]) != 0) {
                    beBaseInfoRam_RemoveTimer(arg1, &DAT_0051d470[0]);
                    SETB_445200((igUnsignedCharList *)st->_isFirstList, 9, GPR_00554aa4)
                    SETI_445200((igIntList *)st->_timerList, 9, DAT_004cfdd0[0])
                    beMessenger_SendNamed(arg0->_messenger, &DAT_0051d3a8[0], DAT_004cfc74[0], ((int *)((igIntList *)st->_dispRamNoList)->_data)[9], &DAT_0051d3e8[0]);
                }
            }
        }
    }
}

/* Owning stack reference to the freshly created down-data list, released on scope exit (reference
 * count in the low 23 bits of _refCount). */

void FUN_004456c0(beNDMWMdlPEBase *arg0, beBaseInfoRam *arg1, beNDMWMdlPEBaseInfoWork *arg2) {
    if (arg2->_isPlayer != 0) {
        igObject *s0;
        igObject *old;
        beMessenger_PushArgContext(arg0->_messenger);
        beMessenger_SelectGroup(arg0->_messenger, &DAT_0051d4b0[0]);
        beMessenger_AppendInt(arg0->_messenger, arg1->_ramNo);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051d4b8[0]);
        s0 = ((Obj *)FUN_003a9250(beMessenger_GetObject(arg0->_messenger, 0), &DAT_0051d4d8[0]))->f12;
        if (s0 != 0) s0->_refCount = s0->_refCount + 1;
        old = (igObject *)arg2->_downDataList;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
        }
        arg2->_downDataList = (int)s0;
        beMessenger_PopArgContext(arg0->_messenger);
        return;
    }
    {
        int alloc;
        int n;
        int *data;
        int j;
        igObject *s0;
        igObject *old;
        alloc = igObject_GetAllocator(); /* matching construct: a0 still holds arg0, retail passes it without a move */
        /* The six-entry list is owned by the stack reference until the work record has taken its own. */
        IntListRef created((List *)FUN_002caa70(GPR_00554c14 != 0 ? alloc : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0])));
        if (created.p->size < 7) List_Reserve(created.p, 6, 4);
        if (created.p->cap >= 6) created.p->size = 6;
        else List_Resize(created.p, 6, 4);
        n = created.p->size;
        data = created.p->data;
        for (j = 0; j < n; j++) data[j] = DAT_004cfdd8[0];
        s0 = (igObject *)created.p;
        if (s0 != 0) s0->_refCount = s0->_refCount + 1;
        old = (igObject *)arg2->_downDataList;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
        }
        arg2->_downDataList = (int)s0;
    }
}

void FUN_00445990(beNDMWMdlPEBase *arg0, beBaseInfoRam *arg1, beNDMWMdlPEBaseInfoWork *arg2) {
    if (arg2->_isPlayer != 0) {
        igObject *s0;
        igObject *old;
        beMessenger_PushArgContext(arg0->_messenger);
        beMessenger_SelectGroup(arg0->_messenger, &DAT_0051d4b0[0]);
        beMessenger_AppendInt(arg0->_messenger, arg1->_ramNo);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051d4b8[0]);
        s0 = ((Obj *)FUN_003a9250(beMessenger_GetObject(arg0->_messenger, 0), &DAT_0051d4e8[0]))->f12;
        if (s0 != 0) s0->_refCount = s0->_refCount + 1;
        old = (igObject *)arg2->_upDataList;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
        }
        arg2->_upDataList = (int)s0;
        beMessenger_PopArgContext(arg0->_messenger);
        return;
    }
    {
        int alloc;
        int n;
        int *data;
        int j;
        igObject *s0;
        igObject *old;
        alloc = igObject_GetAllocator(); /* matching construct: a0 still holds arg0, retail passes it without a move */
        /* The seven-entry list is owned by the stack reference until the work record has taken its own. */
        IntListRef created((List *)FUN_002caa70(GPR_00554c14 != 0 ? alloc : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0])));
        if (created.p->size < 8) List_Reserve(created.p, 7, 4);
        if (created.p->cap >= 7) created.p->size = 7;
        else List_Resize(created.p, 7, 4);
        n = created.p->size;
        data = created.p->data;
        for (j = 0; j < n; j++) data[j] = DAT_004cfde0[0];
        s0 = (igObject *)created.p;
        if (s0 != 0) s0->_refCount = s0->_refCount + 1;
        old = (igObject *)arg2->_upDataList;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
        }
        arg2->_upDataList = (int)s0;
    }
}

void FUN_00445c60(beNDMWMdlPEBase *arg0, struct A1 *arg1, beNDMWMdlPEBaseInfoWork *arg2) {
    if (arg2->_isPlayer != 0) {
        beMessenger_PushArgContext(arg0->_messenger);
        beMessenger_SelectGroup(arg0->_messenger, &DAT_0051d4b0[0]);
        beMessenger_AppendInt(arg0->_messenger, arg1->f8);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051d4f0[0]);
        beMessenger_SelectGroup(arg0->_messenger, &DAT_0051d4b0[0]);
        beMessenger_AppendInt(arg0->_messenger, arg1->f8);
        beMessenger_AppendInt(arg0->_messenger, 0);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051d500[0]);
        beMessenger_PopArgContext(arg0->_messenger);
    }
}

int Gap__Bec__beNDMWMdlPEBase__vfunc_47(beNDMWMdlPEBase *self, Model *obj, int name) {
    beNDMWMdlPEBaseInfoWork *w;
    int e;
    ensureProps(obj);
    w = igProperty_FindByName(obj->props, g_propertyNameField[0], &DAT_0051d3a0[0])->work;
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
            if (w->_downDataList == 0) FUN_004456c0(self, (beBaseInfoRam *)obj, w);
            SETI(w->_downDataList, 0, a)
            SETI(w->_downDataList, 1, b)
            SETI(w->_downDataList, 2, c)
            SETI(w->_downDataList, 3, d)
            FUN_00445c60(self, (A1 *)obj, w);
        }
        return 1;
    case 5:
        if (w != 0) {
            SETB(w->_isFirstList, 2, GPR_00554ac0)
            { int v = GI(0); SETI(w->_timerList, 2, v) }
            int a = GI(1); int b = GI(2);
            if (w->_downDataList == 0) FUN_004456c0(self, (beBaseInfoRam *)obj, w);
            SETI(w->_downDataList, 4, a)
            SETI(w->_downDataList, 5, b)
            FUN_00445c60(self, (A1 *)obj, w);
        }
        return 1;
    case 7:
        if (w != 0) {
            SETB(w->_isFirstList, 5, GPR_00554ac4)
            { int v = GI(0); SETI(w->_timerList, 5, v) }
            int a = GI(1); int b = GI(2); int c = GI(3); int d = GI(4);
            if (w->_upDataList == 0) FUN_00445990(self, (beBaseInfoRam *)obj, w);
            SETI(w->_upDataList, 0, a)
            SETI(w->_upDataList, 1, b)
            SETI(w->_upDataList, 2, c)
            SETI(w->_upDataList, 3, d)
            FUN_00445c60(self, (A1 *)obj, w);
        }
        return 1;
    case 8:
        if (w != 0) {
            SETB(w->_isFirstList, 6, GPR_00554ac8)
            { int v = GI(0); SETI(w->_timerList, 6, v) }
            int a = GI(1); int b = GI(2); int c = GI(3);
            if (w->_upDataList == 0) FUN_00445990(self, (beBaseInfoRam *)obj, w);
            SETI(w->_upDataList, 4, a)
            SETI(w->_upDataList, 5, b)
            SETI(w->_upDataList, 6, c)
            FUN_00445c60(self, (A1 *)obj, w);
        }
        return 1;
    case 9:
        if (w != 0) {
            SETB(w->_isFirstList, 4, GPR_00554acc)
            { int v = GI(0); SETI(w->_timerList, 4, v) }
            int a = GI(1); int b = GI(2); int c = GI(3); int d = GI(4);
            if (w->_upDataList == 0) FUN_00445990(self, (beBaseInfoRam *)obj, w);
            SETI(w->_upDataList, 7, a)
            SETI(w->_upDataList, 8, b)
            SETI(w->_upDataList, 9, c)
            SETI(w->_upDataList, 10, d)
            FUN_00445c60(self, (A1 *)obj, w);
        }
        return 1;
    case 10:
        if (w != 0) {
            SETB(w->_isFirstList, 7, GPR_00554ad0)
            SETI(w->_timerList, 7, DAT_004cfe00[0])
            if (w->_downDataList == 0) FUN_004456c0(self, (beBaseInfoRam *)obj, w);
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
        bool r = false;
        if (w != 0 && w->_dispRamNoList != 0 && w->_timerList != 0) {
            int s = beMessenger_GetString(self->_messenger, 0);
            if (igMetaEnum_GetValueByName(FUN_003c0440(), s, &e2) == g_statusSucceeded && W(_timerList)->data[e2] != 0) r = 1;
        }
        beMessenger_AppendBool(self->_messenger, r);
        return 1;
    }
    case 14:
        if (w != 0 && w->_dispRamNoList != 0) {
            beBaseInfoRam_RemoveTimer(obj, &DAT_0051d3f0[0]);
            SETB(w->_isFirstList, 0, GPR_00554adc)
            SETI(w->_timerList, 0, DAT_004cfe18[0])
            beBaseInfoRam_RemoveTimer(obj, &DAT_0051d480[0]);
            SETB(w->_isFirstList, 1, GPR_00554ae0)
            SETI(w->_timerList, 1, DAT_004cfe20[0])
            beBaseInfoRam_RemoveTimer(obj, &DAT_0051d488[0]);
            SETB(w->_isFirstList, 2, GPR_00554ae4)
            SETI(w->_timerList, 2, DAT_004cfe28[0])
            beBaseInfoRam_RemoveTimer(obj, &DAT_0051d490[0]);
            SETB(w->_isFirstList, 5, GPR_00554ae8)
            SETI(w->_timerList, 5, DAT_004cfe30[0])
            beBaseInfoRam_RemoveTimer(obj, &DAT_0051d498[0]);
            SETB(w->_isFirstList, 6, GPR_00554aec)
            SETI(w->_timerList, 6, DAT_004cfe38[0])
            beBaseInfoRam_RemoveTimer(obj, &DAT_0051d4a0[0]);
            SETB(w->_isFirstList, 4, GPR_00554af0)
            SETI(w->_timerList, 4, DAT_004cfe40[0])
            if (w->_upDataList != 0) { FILLI(_upDataList, DAT_004cfe48) }
            if (w->_downDataList != 0) { FILLI(_downDataList, DAT_004cfe50) }
            if (w->_upDataList != 0 || w->_downDataList != 0) FUN_00445c60(self, (A1 *)obj, w);
        }
    case 13:
        if (w != 0 && w->_dispRamNoList != 0) {
            beBaseInfoRam_RemoveTimer(obj, &DAT_0051d450[0]);
            SETB(w->_isFirstList, 8, GPR_00554af4)
            SETI(w->_timerList, 8, DAT_004cfe58[0])
            beBaseInfoRam_RemoveTimer(obj, &DAT_0051d470[0]);
            SETB(w->_isFirstList, 9, GPR_00554af8)
            SETI(w->_timerList, 9, DAT_004cfe60[0])
            beBaseInfoRam_RemoveTimer(obj, &DAT_0051d478[0]);
            SETB(w->_isFirstList, 3, GPR_00554afc)
            SETI(w->_timerList, 3, DAT_004cfe68[0])
            VC(&DAT_0051d460[0]);
        }
        return 1;
    default:
        return 0;
    }
}

void Gap__Bec__beNDMWMdlPEBaseInfoWork__vfunc_8(beNDMWMdlPEBaseInfoWork *arg0) {
    igIntList *l;
    igIntList *l2;
    int n;
    int n2;
    int *d;
    int *d2;
    int j;
    int j2;
    int i;
    int off;
    int *p;
    igObject *o;

    if (arg0->_messenger != 0 && arg0->_dispRamNoList != 0) {
        if (arg0->_isPlayer != 0) {
            l = (igIntList *)arg0->_upDataList;
            if (l != 0) {
                n = l->_count;
                d = (int *)l->_data;
                for (j = 0; j < n; j++) d[j] = DAT_004cfe70[0];
            }
            l2 = (igIntList *)arg0->_downDataList;
            if (l2 != 0) {
                n2 = l2->_count;
                d2 = (int *)l2->_data;
                for (j2 = 0; j2 < n2; j2++) d2[j2] = DAT_004cfe78[0];
            }
        }
        i = 0;
        off = 0;
        p = &DAT_004cfc50[0];
        do {
            int v = *(int *)((char *)((igIntList *)arg0->_dispRamNoList)->_data + off);
            if (v != -1) {
                beMessenger_SendNamed(arg0->_messenger, &DAT_0051d3a8[0], *p, v, &DAT_0051d3e8[0]);
            }
            i++;
            off += 4;
            p += 1;
        } while (i < 12);
        o = (igObject *)arg0->_dispRamNoList;
        if (o != 0) {
            o->_refCount = (int)o->_refCount - 1;
            if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(o);
        }
        arg0->_dispRamNoList = 0;
        o = (igObject *)arg0->_dispPosNoList;
        if (o != 0) {
            o->_refCount = (int)o->_refCount - 1;
            if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(o);
        }
        arg0->_dispPosNoList = 0;
        o = (igObject *)arg0->_timerList;
        if (o != 0) {
            o->_refCount = (int)o->_refCount - 1;
            if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(o);
        }
        arg0->_timerList = 0;
        o = (igObject *)arg0->_isFirstList;
        if (o != 0) {
            o->_refCount = (int)o->_refCount - 1;
            if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(o);
        }
        arg0->_isFirstList = 0;
    }
    Gap__Core__igObject__vfunc_08__002ff0f0(arg0);
}

/* Written as C++ with the short-circuit `||` shape. */
int FUN_00447b00(beNDMWMdlPEBaseInfoWork *owner)
{
    if (owner->_timerList == 0 || *(int *)((igDataList *)owner->_timerList)->_data == 0) {
        return 0;
    }
    return 1;
}

void FUN_00447b40(beNDMWMdlPEBaseInfoWork *owner, void *arg)
{
    igDataList *list;
    int n;

    beBaseInfoRam_RemoveTimer(arg, ((const char *)DAT_0051d3f0));
    list = (igDataList *)owner->_timerList;
    n = list->_count;
    if (n != 0 && 0 < n) {
        *(int *)list->_data = DAT_004cfe80[0];
    }
}

int Gap__Bec__beNDMWMdlPEBaseInfoWork__vfunc_20(void)
{
    return g_beNDMWMdlPEBaseInfoWork_metaObject[0];
}

int Gap__Bec__beNDMWMdlPEBase__vfunc_20(void)
{
    return g_beNDMWMdlPEBase_metaObject[0];
}

