#include "dw4/igSmartPointer.h"

extern "C" int strcmp(int, int *);
extern "C" int Gap__Bec__beNDMWMdlEBullet__vfunc_35(int dummy0, int arg1);
extern "C" void Gap__Bec__beNDMWMdlEBullet__vfunc_37(void);
extern "C" int Gap__Bec__beNDMWMdlEBullet__vfunc_20(void);
extern "C" int FUN_00396340(...);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" int igObject_GetAllocator(...);
extern "C" int KIND_EBULLET[4];
extern "C" int g_beNDMWMdlEBullet_metaObject[4];
extern "C" igObject *FUN_00350020(...);
extern "C" igObject *beBaseInfoDataList_Create(...);
struct PropertyRecord { char header[20]; igObject *value; };
extern "C" PropertyRecord *igProperty_FindByName(...);
extern "C" int ONE_9[4];
extern "C" int g_propertyNameField[4];
extern "C" int kIGMemoryPoolHandleUser1[4];
extern "C" unsigned char g_useOwnerAllocator;
/* matching construct: inline release helper reproduces the retail release sequence */
struct ReleaseRef { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
/* Owning stack reference to the freshly created data list (reference count in the low 23 bits of
 * _refCount); released on scope exit. */

/* Owning stack reference to the new property value object; released on scope exit. */
class ValueRef {
public:
    igObject *p;
    ValueRef(igObject *o) : p(o) {}
    ~ValueRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* Inlined helper shared by the model-controller "apply ram" methods: a ram without a data list gets a
 * fresh beBaseInfoDataList (allocator chosen by the global selector flag).  Being an inlined callee, its
 * list reference is laid out after the caller's own value reference (+0x58 below +0x5c), as retail does. */
struct RamDataList { static inline void Ensure(beBaseInfoRam *ram) {
    igObject *s0;
    if (ram->_dataList == 0) {
        int alloc = igObject_GetAllocator(ram);
        int a;
        if (g_useOwnerAllocator != 0) {
            a = alloc;
        } else {
            a = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
        }
        igSmartPointer<igObject> list(beBaseInfoDataList_Create(a));
        s0 = list.p;
        if (s0 != 0) {
            s0->_refCount++;
        }
        ReleaseRef::go((igObject *)ram->_dataList);
        ram->_dataList = (int)s0;
    }
} };
extern "C" void Gap__Bec__beNDMWMdlEBullet__vfunc_36(beNDMWMdlEBullet *arg0, beBaseInfoRam *arg1);

int Gap__Bec__beNDMWMdlEBullet__vfunc_35(int dummy0, int arg1) {
    return strcmp(arg1, &KIND_EBULLET[0]) == 0;
}

void Gap__Bec__beNDMWMdlEBullet__vfunc_37(void)
{
}

void Gap__Bec__beNDMWMdlEBullet__vfunc_36(beNDMWMdlEBullet *arg0, beBaseInfoRam *arg1) {
    igObject *s0;
    PropertyRecord *s1;
    int alloc;
    int a;
    RamDataList::Ensure(arg1);
    s1 = igProperty_FindByName((void *)arg1->_dataList, g_propertyNameField[0], ONE_9);
    alloc = igObject_GetAllocator(arg0);
    if (g_useOwnerAllocator != 0) {
        a = alloc;
    } else {
        a = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
    }
    ValueRef value(FUN_00350020(a));
    s0 = value.p;
    if (s0 != 0) {
        s0->_refCount++;
    }
    ReleaseRef::go(s1->value);
    s1->value = s0;
    FUN_00396340(arg0, arg1);
}

int Gap__Bec__beNDMWMdlEBullet__vfunc_20(void)
{
    return g_beNDMWMdlEBullet_metaObject[0];
}
