#include "dw4/igSmartPointer.h"

extern "C" int strcmp(int, int *);
extern "C" int Gap__Bec__beNDMWMdlMapCursor__vfunc_35(int dummy0, int arg1);
extern "C" int igObject_GetAllocator(...);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" int StringChunk_ReleaseHeader(int, int *);
extern "C" int StringPool_Construct(int);
extern "C" void *StringPool_Intern(int, int);
extern "C" int StringPool_Allocate(int);
extern "C" int beModelCtrl__OnGenerate(void *, void *);
extern "C" int beMessenger_GetInt(int, int);
extern "C" int beMessenger_GetIntCount(int);
extern "C" int beMessenger_GetString(int, int);
extern "C" int beMessenger_SendGroup(...);
extern "C" int beMessenger_SendNamed(...);
extern "C" int beMessenger_SendRam(...);
extern "C" int beMessenger_GetMatrixCount(...);
extern "C" int beMessenger_GetMatrix(...);
extern "C" int Matrix44_GetTranslation(...);
extern "C" int Matrix44_SetTranslation(...);
extern "C" int Gap__Bec__beNDMWMdlMapCursor__vfunc_20(void);
extern "C" int DAT_0051dc28[4];
extern "C" igObject *beBaseInfoDataList_Create(int);
struct CursorValue;
extern "C" CursorValue *FUN_00350020(int);
struct PropertyEntry;
extern "C" PropertyEntry * igProperty_FindByName(...);
extern "C" int DAT_0051dc38[4];
extern "C" int g_propertyNameField[4];
extern "C" int g_stringPool[4];
extern "C" int g_defaultAllocatorSelector[4];
extern "C" unsigned char g_useOwnerAllocator;
/* The value object FUN_00350020 creates: an igObject whose string token sits at +220 and whose
 * integer at +224. */
struct CursorValue { igObject base; char pad[212]; int *f220; int f224; };
/* igObject is 8 bytes */
struct PropertyEntry { char pad[20]; CursorValue *f20; };
/* matching construct: inline retain/release helpers reproduce the retail inlined refcount code */
struct RefCount { static inline void addref(igObject *o) { if (o != 0) o->_refCount = o->_refCount + 1; }
 static inline void release(igObject *o) { if (o != 0) { o->_refCount = o->_refCount - 1; if (((unsigned long long)(long long)o->_refCount & 0x7fffffULL) == 0) igObject_Destroy(o); } } };
/* Owning stack reference to the freshly created data list (reference count in the low 23 bits of
 * _refCount); released on scope exit. */

/* Owning stack reference to the new property value object; released on scope exit. */
class ValueRef {
public:
    CursorValue *p;
    ValueRef(CursorValue *o) : p(o) {}
    ~ValueRef() { igObject *o = &p->base; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* Inlined helper shared by the model-controller "apply ram" methods: a ram without a data list gets a
 * fresh beBaseInfoDataList (allocator chosen by the global selector flag).  Being an inlined callee, its
 * list reference is laid out after the caller's own value reference (+0x58 below +0x5c), as retail does. */
struct RamDataList { static inline void Ensure(beBaseInfoRam *ram) {
    if (ram->_dataList == 0) {
        int al = igObject_GetAllocator(ram);
        al = g_useOwnerAllocator ? al : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        igSmartPointer<igObject> list(beBaseInfoDataList_Create(al));
        igObject *t = list.p;
        RefCount::addref(t);
        RefCount::release((igObject *)ram->_dataList);
        ram->_dataList = (int)t;
    }
} };
extern "C" void Gap__Bec__beNDMWMdlMapCursor__vfunc_36(beNDMWMdlMapCursor *arg0, beBaseInfoRam *arg1);
struct PropertyEntry_44b520 { char p[16]; int f16; };
extern "C" int DAT_0051dc80[4];
extern "C" int DAT_0051dc88[4];
extern "C" int DAT_0051dc98[4];
extern "C" int DAT_0051dca8[4];
extern "C" int DAT_0051dcb8[4];
extern "C" int DAT_004cfed0[4];
extern "C" int emptyString[4];
extern "C" float g_vec3Zero[4];
extern "C" float DAT_004e105c[4];
extern "C" float DAT_004e1060[4];
/* matching construct: inline release helper reproduces the retail inlined release of the previous data list */
struct RefRelease { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
struct Vec3f { float x, y, z; };
extern "C" void Gap__Bec__beNDMWMdlMapCursor__vfunc_46(beNDMWMdlMapCursor *arg0, beBaseInfoRam *arg1);
extern "C" int g_beNDMWMdlMapCursor_metaObject[4];

int Gap__Bec__beNDMWMdlMapCursor__vfunc_35(int dummy0, int arg1) {
    return strcmp(arg1, &DAT_0051dc28[0]) == 0;
}

void Gap__Bec__beNDMWMdlMapCursor__vfunc_36(beNDMWMdlMapCursor *arg0, beBaseInfoRam *arg1) {
    CursorValue *t;
    void *nw;
    CursorValue *t2;
    int al;
    PropertyEntry *pr;
    int s;
    RamDataList::Ensure(arg1);
    pr = igProperty_FindByName(arg1->_dataList, g_propertyNameField[0], &DAT_0051dc38[0]);
    al = igObject_GetAllocator(arg0);
    al = g_useOwnerAllocator ? al : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
    {
    /* The new value object is owned by the stack reference while it replaces the record's value and
     * takes the messenger's reply; released at the block end, before the model refresh. */
    ValueRef value(FUN_00350020(al));
    t = value.p;
    RefCount::addref(&t->base);
    RefCount::release(&pr->f20->base);
    pr->f20 = t;
    if (beMessenger_GetIntCount(arg0->_messenger) != 0) {
        s = beMessenger_GetString(arg0->_messenger, 0);
        t2 = value.p;
        if (g_stringPool[0] == 0) {
            int pool = StringPool_Allocate(16);
            if (pool != 0) pool = StringPool_Construct(pool);
            g_stringPool[0] = pool;
        }
        nw = StringPool_Intern(g_stringPool[0], s);
        int *oldstr = t2->f220;
        if (oldstr != 0) {
            int *hdr = oldstr - 2;
            int c = oldstr[-1] - 1;
            oldstr[-1] = c;
            if (c == 0) StringChunk_ReleaseHeader(*hdr, hdr);
        }
        t2->f220 = (int *)nw;
        value.p->f224 = beMessenger_GetInt(arg0->_messenger, 0);
    }
    }
    beModelCtrl__OnGenerate(arg0, arg1);
}

void Gap__Bec__beNDMWMdlMapCursor__vfunc_46(beNDMWMdlMapCursor *arg0, beBaseInfoRam *arg1) {
    igObject *s0;
    PropertyEntry_44b520 *r;
    int m1[16];
    int m2[16];
    Vec3f sum;
    Vec3f t;
    bool s2;
    bool s1;
    float *py = &sum.y;
    float *pz = &sum.z;
    s2 = false;
    sum.x = g_vec3Zero[0];
    *py = DAT_004e105c[0];
    *pz = DAT_004e1060[0];
    s1 = false;
    beMessenger_SendRam(arg0->_messenger, DAT_0051dc80, arg1->_ramNo, DAT_0051dc88);
    if (beMessenger_GetMatrixCount(arg0->_messenger) != 0) {
        beMessenger_GetMatrix(m1, arg0->_messenger, 0);
        Matrix44_GetTranslation(m1, &sum);
        s2 = true;
    }
    switch (arg1->_st0) {
    case 0:
        if (s2) {
            int a2 = ((beBaseInfo *)arg1->_parentInfo)->_name;
            int a3 = arg1->_ramNo;
            a2 = a2 ? a2 : (int)emptyString;
            beMessenger_SendNamed(arg0->_messenger, DAT_0051dc98, a2, a3, DAT_004cfed0[a3]);
            s1 = true;
            arg1->_st0 = 1;
            arg1->_st3 = 0;
            arg1->_st2 = 0;
            arg1->_st1 = 0;
        }
        break;
    case 1:
        if (!(s2 & 0xFF)) {
            int a2 = ((beBaseInfo *)arg1->_parentInfo)->_name;
            int a3 = arg1->_ramNo;
            a2 = a2 ? a2 : (int)emptyString;
            beMessenger_SendNamed(arg0->_messenger, DAT_0051dc98, a2, a3, DAT_0051dca8);
            arg1->_st0 = 0;
            arg1->_st3 = 0;
            arg1->_st2 = 0;
            arg1->_st1 = 0;
        }
        s1 = true;
        break;
    }
    if (s1) {
        beMessenger_SendGroup(arg0->_messenger, DAT_0051dcb8, DAT_0051dc88);
        if (beMessenger_GetMatrixCount(arg0->_messenger) != 0) {
            beMessenger_GetMatrix(m2, arg0->_messenger, 0);
            Matrix44_GetTranslation(m2, &t);
            sum.x += t.x;
            *py += t.y;
            *pz += t.z;
            if (arg1->_dataList == 0) {
                int alloc = igObject_GetAllocator(arg1);
                int a;
                if (g_useOwnerAllocator != 0) {
                    a = alloc;
                } else {
                    a = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
                }
                igSmartPointer<igObject> ref(beBaseInfoDataList_Create(a));
                s0 = ref.p;
                if (s0 != 0) {
                    s0->_refCount++;
                }
                RefRelease::go((igObject *)arg1->_dataList);
                arg1->_dataList = (int)s0;
            }
            r = ((PropertyEntry_44b520 *)igProperty_FindByName(arg1->_dataList, g_propertyNameField[0], DAT_0051dc38));
            *py = 0.0f;
            Matrix44_SetTranslation(r->f16 + 32, &sum);
        }
    }
}

int Gap__Bec__beNDMWMdlMapCursor__vfunc_20(void)
{
    return g_beNDMWMdlMapCursor_metaObject[0];
}

