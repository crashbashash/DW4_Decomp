#include "dw4/igSmartPointer.h"
extern "C" {
igObject *beBaseInfoDataList_Create(int);
igObject *FUN_003bf560(int);
int Memory_GetAllocatorBySelector(...);
int igObject_GetAllocator(...);
int FUN_00396740(...);
int beMessenger_SendGroup(...);
beDataObjIntList *FUN_003a9310(...);
beDataObjFloatList *FUN_003a9370(...);
int beMessenger_GetObject(...);
int StringChunk_ReleaseHeader(...);
int StringPool_Construct(...);
int StringPool_Intern(...);
int FUN_002eb010(...);
int Matrix44_GetTranslation(...);
struct PropertyRecordView { char p[16]; int f16; igObject *f20; };
PropertyRecordView *igProperty_FindByName(...);
extern int DAT_005165c8[4];
extern int DAT_005165d0[4];
extern int DAT_005165d8[4];
extern int DAT_005165e8[4];
extern int DAT_005165f8[4];
extern int DAT_00585be0[4];
extern int DAT_00586f20[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
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
        if (DAT_00586f20[0] == 0) {
            int pool = FUN_002eb010(16);
            if (pool != 0) pool = StringPool_Construct(pool);
            DAT_00586f20[0] = pool;
        }
        ref = (int *)StringPool_Intern(DAT_00586f20[0], s);
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
            a = Memory_GetAllocatorBySelector(DAT_00587110[0]);
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
void Gap__Bec__beNDMWMdlPlayer2__vfunc_36(beNDMWMdlPlayer2 *arg0, beBaseInfoRam *arg1) {
    V3 t;
    PropertyRecordView *r;
    beDataObjIntList *s4;
    beDataObjFloatList *s3;
    int s2;
    int *e;
    int s1;
    RamDataList::Ensure(arg1);
    r = igProperty_FindByName((igObject *)arg1->_dataList, DAT_00585be0[0], DAT_005165c8);
    {
        int alloc = igObject_GetAllocator(arg0);
        int a;
        if (GPR_00554c14 != 0) {
            a = alloc;
        } else {
            a = Memory_GetAllocatorBySelector(DAT_00587110[0]);
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
        s4 = FUN_003a9310(o, DAT_005165e8);
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
