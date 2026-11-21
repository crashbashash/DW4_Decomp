#include "dw4/core/igSmartPointer.h"
#include "dw4/game/beBaseInfoDataList.h"
#include "dw4/game/beModelCtrl.h"
#include "dw4/game/beModelCtrlInfoWork.h"
#include "dw4/game/ndmw/beNDMWMdlEffect.h"
#include "dw4/core/igDataLists.h"
#include "dw4/core/igMemoryPoolContext.h"
#include "dw4/core/igNamedObject.h"
#include "dw4/core/igObject.h"
#include <string.h>

extern "C" unsigned char beNDMWMdlEffect_IsKind(int dummy0, int kind);
extern "C" void beNDMWMdlEffect_RegisterReceiver(void);
extern "C" int beNDMWMdlEffect_GetMeta(void);
extern "C" int KIND_EFFECT[4];
/* matching construct: inline static helper reproduces the retail release sequence */
struct ReleaseRef { static inline void go(igObject *object) {
    igObject::release(object);
} };
/* Owning stack reference to the freshly created property data list; released at the end of the
 * full expression that stores it (reference count in the low 23 bits of _refCount). */

/* Owning stack reference to the effect work object created here; released on scope exit. */
class EffectRef {
public:
    igObject *p;
    EffectRef(igObject *o) : p(o) {}
    ~EffectRef() { igObject *o = p; igObject::release(o); }
};
struct DataList { static inline void store(beBaseInfoRam *ram, const igSmartPointer<igObject> &list) {
    igObject *created = list.p;
    igObject *old;
    igObject::ref(created);
    old = (igObject *)ram->_dataList;
    igObject::release(old);
    ram->_dataList = (int)created;
}
static inline void create(beBaseInfoRam *ram, igMemoryPoolView *a) { igSmartPointer<igObject> list(beBaseInfoDataList_Create((int)a)); store(ram, list); }
};
extern "C" void beNDMWMdlEffect_OnGenerate(beNDMWMdlEffect *self, beBaseInfoRam *ram);

#pragma push
#pragma readonly_strings on

unsigned char beNDMWMdlEffect_IsKind(int dummy0, int kind) {
    return strcmp((const char *)kind, (const char *)KIND_EFFECT) == 0;
}

void beNDMWMdlEffect_RegisterReceiver(void)
{
}

void beNDMWMdlEffect_OnGenerate(beNDMWMdlEffect *self, beBaseInfoRam *ram) {
    igObject *s0;
    beModelCtrlInfoRamData *s1;
    igMemoryPoolView *alloc;
    igMemoryPoolView *a;
    if (ram->_dataList == 0) {
        alloc = ((Gap::Core::igObject *)ram)->getMemoryPool();
        if (g_useOwnerAllocator != 0) {
            a = alloc;
        } else {
            a = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        }
        DataList::create(ram, a);
    }
    s1 = (beModelCtrlInfoRamData *)((Gap::Core::igObjectList *)ram->_dataList)->search((Gap::Core::igStringMetaField *)g_propertyNameField, "ONE");
    alloc = ((Gap::Core::igObject *)self)->getMemoryPool();
    if (g_useOwnerAllocator != 0) {
        a = alloc;
    } else {
        a = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
    }
    /* matching construct: the effect holder is a named local and the list holder above an unnamed
     * temporary; named locals take their frame slots before temporaries (effect +0x5c, list +0x58) */
    EffectRef effect(beModelCtrlInfoWork_Create((int)a));
    s0 = effect.p;
    igObject::ref(s0);
    ReleaseRef::go((igObject *)s1->_work);
    s1->_work = (int)s0;
    beModelCtrl__OnGenerateFromParent((beModelCtrl *)self, ram);
}

int beNDMWMdlEffect_GetMeta(void)
{
    return (int)g_beNDMWMdlEffect_metaObject;
}

#pragma pop
