#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"

extern "C" int igInsightCore_FindManager(int, int);
extern "C" int Gap__Core__igObject__vfunc_23(...);
extern "C" int Gap__Bec__beNDMWMdlPlayer2__vfunc_20(void);
extern "C" int strcmp(int, int *);
extern "C" int Gap__Bec__beNDMWMdlPlayer2__vfunc_35(int dummy0, int arg1);
extern "C" void beMessenger_RegisterReceiverFromInfo(int, int, char *);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" int igObject_GetAllocator(...);
extern "C" int FUN_00396740(...);
extern "C" int beMessenger_SendGroup(...);
extern "C" int beMessenger_GetObject(...);
extern "C" int StringChunk_ReleaseHeader(...);
extern "C" int StringPool_Construct(...);
extern "C" int StringPool_Intern(...);
extern "C" int StringPool_Allocate(...);
extern "C" int Matrix44_GetTranslation(...);
extern "C" int bePadManager_GetPadForPlayer(int, int);
extern "C" int beTargetObj_SelectTarget(int, int *, int *);
extern "C" float beTargetObj_GetTargetDistanceSq(...);
extern "C" int beLua__RunNamedChunk(int, int *, int);
extern "C" int g_bePadManager_metaObject[4];
extern "C" int g_beNDMWMdlPlayer2_metaObject[4];
extern "C" void Gap__Bec__beNDMWMdlPlayer2__vfunc_23(beNDMWMdlPlayer2 *self);
extern "C" int DAT_005165b0[4];
extern "C" char DAT_005165c0[];
extern "C" void Gap__Bec__beNDMWMdlPlayer2__vfunc_37(beNDMWMdlPlayer2 * p0, int p1, char * p2);
extern "C" igObject *beBaseInfoDataList_Create(int);
extern "C" igObject *FUN_003bf560(int);
extern "C" beDataObjIntList *igProperty_GetRecordStringList(...);
extern "C" beDataObjFloatList *FUN_003a9370(...);
struct PropertyRecordView { char p[16]; int f16; igObject *f20; };
extern "C" PropertyRecordView * igProperty_FindByName(...);
extern "C" int DAT_005165c8[4];
extern "C" int DAT_005165d0[4];
extern "C" int DAT_005165d8[4];
extern "C" int DAT_005165e8[4];
extern "C" int DAT_005165f8[4];
extern "C" int g_propertyNameField[4];
extern "C" int g_stringPool[4];
extern "C" int g_defaultAllocatorSelector[4];
extern "C" unsigned char GPR_00554c14;
/* matching construct: Rel::go and Str::release inline the retail refcount releases */
struct Rel { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
struct Str { static inline int *intern(int s) {
    int *ref;
    if (s == 0) {
        ref = 0;
    } else {
        if (g_stringPool[0] == 0) {
            int pool = StringPool_Allocate(16);
            if (pool != 0) pool = StringPool_Construct(pool);
            g_stringPool[0] = pool;
        }
        ref = (int *)StringPool_Intern(g_stringPool[0], s);
    }
    return ref;
}
static inline void release(int *q) {
    if (q) { int *hd = q - 2; int c = q[-1] - 1; q[-1] = c; if (c == 0) StringChunk_ReleaseHeader(*hd, hd); }
} };
struct V3 { float x, y, z; };
/* Owning stack reference to the freshly created data list (reference count in the low 23 bits of
 * _refCount); released on scope exit. */

/* Owning stack reference to the new property value object; released on scope exit. */
class ValueRef {
public:
    igObject *p;
    ValueRef(igObject *o) : p(o) {}
    ~ValueRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]); releases the token on scope exit. */
class StringRef {
public:
    int *p;
    StringRef(int *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
/* Inlined helper shared by the model-controller "apply ram" methods: a ram without a data list gets a
 * fresh beBaseInfoDataList (allocator chosen by the global selector flag).  Being an inlined callee, its
 * list reference is laid out after the caller's own references (+0x74 below +0x7c/+0x78), as retail does. */

struct RamDataList { static inline void Ensure(beBaseInfoRam *ram) {
    if (ram->_dataList == 0) {
        int alloc = igObject_GetAllocator(ram);
        int a;
        if (GPR_00554c14 != 0) {
            a = alloc;
        } else {
            a = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        }
        igSmartPointer<igObject> list(beBaseInfoDataList_Create(a));
        igObject *s0 = list.p;
        if (s0 != 0) {
            s0->_refCount++;
        }
        Rel::go((igObject *)ram->_dataList);
        ram->_dataList = (int)s0;
    }
} };
extern "C" void Gap__Bec__beNDMWMdlPlayer2__vfunc_36(beNDMWMdlPlayer2 *arg0, beBaseInfoRam *arg1);
/* Player work record: byte at +236, int at +240. */
struct PlayerWorkTail { char p[236]; unsigned char f236; char p2[3]; int f240; };
/* property record: pointer to the work record at +20 */
struct PropertyRecord { char p[16]; int f16; PlayerWorkTail *q; };
extern "C" int DAT_00516608[4];
extern "C" int DAT_00516610[4];
extern "C" int DAT_00516618[4];
extern "C" int DAT_00516620[4];
extern "C" int DAT_00516630[4];
/* Owning stack reference to the freshly created data list; released on scope exit (reference count
 * in the low 23 bits of _refCount). */

/* matching construct: dummy-virtual class gives arg0 a vtable so v35 dispatches through slot 35 */
class MdlPlayer2VirtualShim { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32();  virtual void v35(beBaseInfoRam *, int *); char p[28]; int f32; char p2[8]; int f44; };
extern "C" void Gap__Bec__beNDMWMdlPlayer2__vfunc_38(MdlPlayer2VirtualShim *arg0, beBaseInfoRam *arg1);

/* After the shared igObject slot 23 body, caches the pad manager registered with the insight core
 * (_padManager), found by its class metaObject; the same binding step as the other managers' slot
 * 23. */
void Gap__Bec__beNDMWMdlPlayer2__vfunc_23(beNDMWMdlPlayer2 *self) {
    Gap__Core__igObject__vfunc_23();
    self->_padManager = igInsightCore_FindManager(self->_insight, g_bePadManager_metaObject[0]);
}

int Gap__Bec__beNDMWMdlPlayer2__vfunc_35(int dummy0, int arg1) {
    return strcmp(arg1, &DAT_005165b0[0]) == 0;
}

void Gap__Bec__beNDMWMdlPlayer2__vfunc_37(beNDMWMdlPlayer2 * p0, int p1, char * p2)
{
    beMessenger_RegisterReceiverFromInfo(p0->_messenger, p1, DAT_005165c0);
}

void Gap__Bec__beNDMWMdlPlayer2__vfunc_36(beNDMWMdlPlayer2 *arg0, beBaseInfoRam *arg1) {
    V3 t;
    PropertyRecordView *r;
    beDataObjIntList *s4;
    beDataObjFloatList *s3;
    int s2;
    int *e;
    int s1;
    RamDataList::Ensure(arg1);
    r = igProperty_FindByName((igObject *)arg1->_dataList, g_propertyNameField[0], DAT_005165c8);
    {
        int alloc = igObject_GetAllocator(arg0);
        int a;
        if (GPR_00554c14 != 0) {
            a = alloc;
        } else {
            a = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        }
        ValueRef value(FUN_003bf560(a));
        igObject *n = value.p;
        if (n != 0) {
            n->_refCount++;
        }
        Rel::go(r->f20);
        r->f20 = n;
    }
    FUN_00396740(arg0, arg1);
    beMessenger_SendGroup(arg0->_messenger, DAT_005165d0, DAT_005165d8);
    {
        int o = beMessenger_GetObject(arg0->_messenger, 0);
        s4 = igProperty_GetRecordStringList(o, DAT_005165e8);
        s3 = FUN_003a9370(o, DAT_005165f8);
    }
    /* matching construct: cast from the 4-byte _system reference */
    beSystem *cfg = (beSystem *)arg0->_system;
    s2 = cfg->_stageName;
    s1 = arg1->_ramNo;
    {
        int *tok = Str::intern(s2);
        StringRef name(tok);
        igIntList *l = (igIntList *)s4->_data;
        int n = l->_count;
        if (n != 0 && s1 >= 0 && s1 < n) {
            e = &((int *)l->_data)[s1];
            int *nv = name.p;
            if (nv) nv[-1] = nv[-1] + 1;
            Str::release((int *)*e);
            *e = (int)name.p;
        }
    }
    Matrix44_GetTranslation(r->f16 + 32, &t);
    {
        float *v = &t.x;
        igFloatList *l = (igFloatList *)s3->_data;
        int n = l->_count;
        if (n != 0) {
            int i = s1 * 3 + 0;
            if (i >= 0 && i < n) { float *d = (float *)l->_data; d[s1 * 3 + 0] = *v; }
        }
    }
    {
        float *v = &t.y;
        igFloatList *l = (igFloatList *)s3->_data;
        int n = l->_count;
        if (n != 0) {
            int i = s1 * 3 + 1;
            if (i >= 0 && i < n) { float *d = (float *)l->_data; d[s1 * 3 + 1] = *v; }
        }
    }
    {
        float *v = &t.z;
        igFloatList *l = (igFloatList *)s3->_data;
        int n = l->_count;
        if (n != 0) {
            int i = s1 * 3 + 2;
            if (i >= 0 && i < n) { float *d = (float *)l->_data; d[s1 * 3 + 2] = *v; }
        }
    }
}

void Gap__Bec__beNDMWMdlPlayer2__vfunc_38(MdlPlayer2VirtualShim *arg0, beBaseInfoRam *arg1) {
    PropertyRecord *prop;
    PlayerWorkTail *q;
    float f;
    if (arg1->_dataList == 0) {
        int alloc = igObject_GetAllocator(arg1);
        int a;
        if (GPR_00554c14 != 0) {
            a = alloc;
        } else {
            a = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        }
        igSmartPointer<igObject> created(beBaseInfoDataList_Create(a));
        igObject *s0 = created.p;
        if (s0 != 0) {
            s0->_refCount++;
        }
        igObject *old = (igObject *)arg1->_dataList;
        if (old != 0) {
            --old->_refCount;
            if ((old->_refCount & 0x7fffff) == 0) igObject_Destroy(old);
        }
        arg1->_dataList = (int)s0;
    }
    prop = ((PropertyRecord *)igProperty_FindByName(arg1->_dataList, g_propertyNameField[0], DAT_005165c8));
    q = prop->q;
    if (q->f240 < 10) {
        q->f240 = q->f240 + 1;
    }
    bePadManager_GetPadForPlayer(((beNDMWMdlPlayer2 *)arg0)->_padManager, arg1->_ramNo);
    if (beTargetObj_SelectTarget(prop->f16 + 32, DAT_00516608, DAT_00516610) != 0) {
        f = beTargetObj_GetTargetDistanceSq();
        if (q->f236 == 0) {
            if (f < 900.0f) {
                q->f236 = 1;
                arg0->v35(arg1, DAT_00516618);
            }
        } else if (!(f <= 900.0f)) {
            q->f236 = 0;
            arg0->v35(arg1, DAT_00516620);
        }
    } else {
        beLua__RunNamedChunk(((beNDMWMdlPlayer2 *)arg0)->_luaManager, DAT_00516630, 0);
    }
}

int Gap__Bec__beNDMWMdlPlayer2__vfunc_20(void)
{
    return g_beNDMWMdlPlayer2_metaObject[0];
}
