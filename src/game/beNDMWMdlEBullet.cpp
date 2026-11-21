#include "dw4/core/igSmartPointer.h"
#include "dw4/game/beBaseInfoDataList.h"
#include "dw4/game/beModelCtrl.h"
#include "dw4/game/beModelCtrlInfoWork.h"
#include "dw4/game/ndmw/beNDMWMdlEBullet.h"
#include "dw4/core/igDataLists.h"
#include "dw4/core/igMemoryPoolContext.h"
#include "dw4/core/igNamedObject.h"
#include "dw4/core/igObject.h"
#include <string.h>

extern "C" unsigned char beNDMWMdlEBullet_IsKind(int dummy0, int kind);
extern "C" void beNDMWMdlEBullet_RegisterReceiver(void);
extern "C" int beNDMWMdlEBullet_GetMeta(void);
extern "C" int KIND_EBULLET[4];
/* matching construct: inline release helper reproduces the retail release sequence */
struct ReleaseRef { static inline void go(igObject *object) {
    igObject::release(object);
} };
/* Owning stack reference to the freshly created data list (reference count in the low 23 bits of
 * _refCount); released on scope exit. */

/* Owning stack reference to the new property value object; released on scope exit. */
class ValueRef {
public:
    igObject *p;
    ValueRef(igObject *o) : p(o) {}
    ~ValueRef() { igObject *o = p; igObject::release(o); }
};
/* Inlined helper shared by the model-controller "apply ram" methods: a ram without a data list gets a
 * fresh beBaseInfoDataList (allocator chosen by the global selector flag).  Being an inlined callee, its
 * list reference is laid out after the caller's own value reference (+0x58 below +0x5c), as retail does. */
struct RamDataList { static inline void Ensure(beBaseInfoRam *ram) {
    igObject *s0;
    if (ram->_dataList == 0) {
        igMemoryPoolView *alloc = ((Gap::Core::igObject *)ram)->getMemoryPool();
        igMemoryPoolView *a;
        if (g_useOwnerAllocator != 0) {
            a = alloc;
        } else {
            a = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        }
        igSmartPointer<igObject> list(beBaseInfoDataList_Create((int)a));
        s0 = list.p;
        igObject::ref(s0);
        ReleaseRef::go((igObject *)ram->_dataList);
        ram->_dataList = (int)s0;
    }
} };
extern "C" void beNDMWMdlEBullet_OnGenerate(beNDMWMdlEBullet *self, beBaseInfoRam *ram);

#pragma push
#pragma readonly_strings on

unsigned char beNDMWMdlEBullet_IsKind(int dummy0, int kind) {
    return strcmp((const char *)kind, (const char *)KIND_EBULLET) == 0;
}

void beNDMWMdlEBullet_RegisterReceiver(void)
{
}

void beNDMWMdlEBullet_OnGenerate(beNDMWMdlEBullet *self, beBaseInfoRam *ram) {
    igObject *s0;
    beModelCtrlInfoRamData *s1;
    igMemoryPoolView *alloc;
    igMemoryPoolView *a;
    RamDataList::Ensure(ram);
    s1 = (beModelCtrlInfoRamData *)((Gap::Core::igObjectList *)ram->_dataList)->search((Gap::Core::igStringMetaField *)g_propertyNameField, "ONE");
    alloc = ((Gap::Core::igObject *)self)->getMemoryPool();
    if (g_useOwnerAllocator != 0) {
        a = alloc;
    } else {
        a = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
    }
    ValueRef value(beModelCtrlInfoWork_Create((int)a));
    s0 = value.p;
    igObject::ref(s0);
    ReleaseRef::go((igObject *)s1->_work);
    s1->_work = (int)s0;
    beModelCtrl__OnGenerateFromParent((beModelCtrl *)self, ram);
}

int beNDMWMdlEBullet_GetMeta(void)
{
    return (int)g_beNDMWMdlEBullet_metaObject;
}

#pragma pop
