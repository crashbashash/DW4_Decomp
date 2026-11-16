#include "dw4/igSmartPointer.h"

extern "C" int strcmp(int, int *);
extern "C" int beNDMWMdlPBullet_IsKind(int dummy0, int kind);
extern "C" void beNDMWMdlPBullet_RegisterReceiver(void);
extern "C" int beNDMWMdlPBullet_GetMeta(void);
extern "C" int beModelCtrl__OnGenerateFromParent(...);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" int igObject_GetAllocator(...);
extern "C" int KIND_PBULLET[4];
extern "C" int g_beNDMWMdlPBullet_metaObject[4];
extern "C" igObject *beModelCtrlInfoWork_Create(...);
extern "C" igObject *beBaseInfoDataList_Create(...);
extern "C" beModelCtrlInfoRamData *igProperty_FindByName(...);
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
extern "C" void beNDMWMdlPBullet_OnGenerate(beNDMWMdlPBullet *self, beBaseInfoRam *ram);

#pragma push
#pragma readonly_strings on

int beNDMWMdlPBullet_IsKind(int dummy0, int kind) {
    return strcmp(kind, &KIND_PBULLET[0]) == 0;
}

void beNDMWMdlPBullet_RegisterReceiver(void)
{
}

void beNDMWMdlPBullet_OnGenerate(beNDMWMdlPBullet *self, beBaseInfoRam *ram) {
    igObject *s0;
    beModelCtrlInfoRamData *s1;
    int alloc;
    int a;
    RamDataList::Ensure(ram);
    s1 = igProperty_FindByName((void *)ram->_dataList, g_propertyNameField[0], "ONE");
    alloc = igObject_GetAllocator(self);
    if (g_useOwnerAllocator != 0) {
        a = alloc;
    } else {
        a = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
    }
    ValueRef value(beModelCtrlInfoWork_Create(a));
    s0 = value.p;
    if (s0 != 0) {
        s0->_refCount++;
    }
    ReleaseRef::go((igObject *)s1->_work);
    s1->_work = (int)s0;
    beModelCtrl__OnGenerateFromParent(self, ram);
}

int beNDMWMdlPBullet_GetMeta(void)
{
    return g_beNDMWMdlPBullet_metaObject[0];
}

#pragma pop
