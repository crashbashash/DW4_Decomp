#include "dw4/igSmartPointer.h"
#include "dw4/beBaseInfoDataList.h"
#include "dw4/beModelCtrl.h"
#include "dw4/beModelCtrlInfoWork.h"
#include "dw4/beNDMWMdlPBullet.h"
#include "dw4/igDataLists.h"
#include "dw4/igMemoryPoolContext.h"
#include "dw4/igNamedObject.h"
#include "dw4/igObject.h"
#include <string.h>

extern "C" int beNDMWMdlPBullet_IsKind(int dummy0, int kind);
extern "C" void beNDMWMdlPBullet_RegisterReceiver(void);
extern "C" int beNDMWMdlPBullet_GetMeta(void);
extern "C" int KIND_PBULLET[4];
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
        igMemoryPoolView *alloc = igObject_GetAllocator(ram);
        igMemoryPoolView *a;
        if (g_useOwnerAllocator != 0) {
            a = alloc;
        } else {
            a = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        }
        igSmartPointer<igObject> list(beBaseInfoDataList_Create((int)a));
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
    return strcmp((const char *)kind, (const char *)KIND_PBULLET) == 0;
}

void beNDMWMdlPBullet_RegisterReceiver(void)
{
}

void beNDMWMdlPBullet_OnGenerate(beNDMWMdlPBullet *self, beBaseInfoRam *ram) {
    igObject *s0;
    beModelCtrlInfoRamData *s1;
    igMemoryPoolView *alloc;
    igMemoryPoolView *a;
    RamDataList::Ensure(ram);
    s1 = (beModelCtrlInfoRamData *)igProperty_FindByName((igObjectList *)ram->_dataList, g_propertyNameField, "ONE");
    alloc = igObject_GetAllocator(self);
    if (g_useOwnerAllocator != 0) {
        a = alloc;
    } else {
        a = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
    }
    ValueRef value(beModelCtrlInfoWork_Create((int)a));
    s0 = value.p;
    if (s0 != 0) {
        s0->_refCount++;
    }
    ReleaseRef::go((igObject *)s1->_work);
    s1->_work = (int)s0;
    beModelCtrl__OnGenerateFromParent((beModelCtrl *)self, ram);
}

int beNDMWMdlPBullet_GetMeta(void)
{
    return (int)g_beNDMWMdlPBullet_metaObject;
}

#pragma pop
