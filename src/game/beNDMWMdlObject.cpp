#include "dw4/igSmartPointer.h"
#include "dw4/StringPool.h"
#include "dw4/beBaseInfoDataList.h"
#include "dw4/beMessenger.h"
#include "dw4/beModelCtrl.h"
#include "dw4/beModelCtrlInfoWork.h"
#include "dw4/beNDMWMdlObject.h"
#include "dw4/igDataLists.h"
#include "dw4/igMemoryPoolContext.h"
#include "dw4/igNamedObject.h"
#include "dw4/igObject.h"
#include <string.h>

extern "C" int beNDMWMdlObject_IsKind(int dummy0, int kind);
extern "C" void beNDMWMdlObject_RegisterReceiver(void);
extern "C" int beNDMWMdlObject_GetMeta(void);
extern "C" int KIND_OBJECT[4];
struct RefRelease { static inline void go(igObject *o) { igObject *t = o; if (t != 0) { --t->_refCount; if ((t->_refCount & 0x7fffff) == 0) igObject_Destroy(t); } } };
/* Owning stack reference to the new map info work; released on scope exit. */
class InfoWorkRef {
public:
    igObject *p;
    InfoWorkRef(igObject *o) : p(o) {}
    ~InfoWorkRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
struct DataListSlot { static inline void setDataList(beBaseInfoRam *ram, const igSmartPointer<igObject> &r) {
    igObject *t = r.p;
    if (t != 0) t->_refCount = t->_refCount + 1;
    RefRelease::go((igObject *)ram->_dataList);
    ram->_dataList = (int)t;
}
static inline void adopt(beBaseInfoRam *ram, igObject *created) { igSmartPointer<igObject> list(created); setDataList(ram, list); }
};
extern "C" void beNDMWMdlObject_OnGenerate(beNDMWMdlObject *self, beBaseInfoRam *ram);

#pragma push
#pragma readonly_strings on

int beNDMWMdlObject_IsKind(int dummy0, int kind) {
    return strcmp((const char *)kind, (const char *)KIND_OBJECT) == 0;
}

void beNDMWMdlObject_RegisterReceiver(void)
{
}

void beNDMWMdlObject_OnGenerate(beNDMWMdlObject *self, beBaseInfoRam *ram) {
    if (ram->_dataList == 0) {
        igMemoryPoolView *a = igObject_GetAllocator(ram);
        igMemoryPoolView *al = g_useOwnerAllocator != 0 ? a : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        igObject *created = beBaseInfoDataList_Create((int)al);
        /* matching construct: the new list is a temporary bound to the setter's reference parameter (it
         * takes the stack slot below the named info-work reference, as retail's +0x58 does) */
        DataListSlot::adopt(ram, created);
    }
    beModelCtrlInfoRamData *s3 = (beModelCtrlInfoRamData *)igProperty_FindByName((igObjectList *)ram->_dataList, g_propertyNameField, "ONE");
    {
        igMemoryPoolView *a2 = igObject_GetAllocator(self);
        igMemoryPoolView *al2 = g_useOwnerAllocator != 0 ? a2 : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        InfoWorkRef w(beModelCtrlInfoWork_Create((int)al2));
        igObject *t2 = w.p;
        if (t2 != 0) t2->_refCount = t2->_refCount + 1;
        RefRelease::go((igObject *)s3->_work);
        s3->_work = (int)t2;
        if (beMessenger_GetIntCount((beMessenger *)self->_messenger) != 0) {
            const char *str = beMessenger_GetString((beMessenger *)self->_messenger, 0);
            int ns;
            beModelCtrlInfoWork *tg = (beModelCtrlInfoWork *)w.p;
            if (g_stringPool == 0) {
                StringPool *v = (StringPool *)StringPool_Allocate(16);
                if (v != 0) v = StringPool_Construct(v);
                g_stringPool = v;
            }
            ns = (int)StringPool_Intern(g_stringPool, str);
            int old = tg->_hitParentName;
            if (old != 0) {
                int *hdr = (int *)(old - 8);
                int c = hdr[1] - 1;
                hdr[1] = c;
                if (c == 0) StringChunk_ReleaseHeader((StringChunk *)*hdr, (StringTokenHeader *)hdr);
            }
            tg->_hitParentName = ns;
            ((beModelCtrlInfoWork *)w.p)->_hitParentRamNo = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
        }
    }
    beModelCtrl__OnGenerate((beModelCtrl *)self, ram);
}

int beNDMWMdlObject_GetMeta(void)
{
    return (int)g_beNDMWMdlObject_metaObject;
}

#pragma pop
