#include "dw4/igSmartPointer.h"
#include "dw4/beBaseInfoDataList.h"
#include "dw4/beModelCtrl.h"
#include "dw4/beModelCtrlInfoWork.h"
#include "dw4/beNDMWMdlEffect.h"
#include "dw4/igDataLists.h"
#include "dw4/igMemoryPoolContext.h"
#include "dw4/igNamedObject.h"
#include "dw4/igObject.h"
#include <string.h>

extern "C" unsigned char beNDMWMdlEffect_IsKind(int dummy0, int kind);
extern "C" void beNDMWMdlEffect_RegisterReceiver(void);
extern "C" int beNDMWMdlEffect_GetMeta(void);
extern "C" int KIND_EFFECT[4];
/* matching construct: inline static helper reproduces the retail release sequence */
struct ReleaseRef { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
/* Owning stack reference to the freshly created property data list; released at the end of the
 * full expression that stores it (reference count in the low 23 bits of _refCount). */

/* Owning stack reference to the effect work object created here; released on scope exit. */
class EffectRef {
public:
    igObject *p;
    EffectRef(igObject *o) : p(o) {}
    ~EffectRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
struct DataList { static inline void store(beBaseInfoRam *ram, const igSmartPointer<igObject> &list) {
    igObject *created = list.p;
    igObject *old;
    if (created != 0) {
        created->_refCount++;
    }
    old = (igObject *)ram->_dataList;
    if (old) {
        --old->_refCount;
        if (((unsigned long long)(long long)old->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(old);
    }
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
        alloc = igObject_GetAllocator(ram);
        if (g_useOwnerAllocator != 0) {
            a = alloc;
        } else {
            a = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        }
        DataList::create(ram, a);
    }
    s1 = (beModelCtrlInfoRamData *)igProperty_FindByName((igObjectList *)ram->_dataList, g_propertyNameField, "ONE");
    alloc = igObject_GetAllocator(self);
    if (g_useOwnerAllocator != 0) {
        a = alloc;
    } else {
        a = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
    }
    /* matching construct: the effect holder is a named local and the list holder above an unnamed
     * temporary; named locals take their frame slots before temporaries (effect +0x5c, list +0x58) */
    EffectRef effect(beModelCtrlInfoWork_Create((int)a));
    s0 = effect.p;
    if (s0 != 0) {
        s0->_refCount++;
    }
    ReleaseRef::go((igObject *)s1->_work);
    s1->_work = (int)s0;
    beModelCtrl__OnGenerateFromParent((beModelCtrl *)self, ram);
}

int beNDMWMdlEffect_GetMeta(void)
{
    return (int)g_beNDMWMdlEffect_metaObject;
}

#pragma pop
