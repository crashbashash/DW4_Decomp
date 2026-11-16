#include "dw4/igSmartPointer.h"

extern "C" int strcmp(int, int *);
extern "C" int beNDMWMdlObject_IsKind(int dummy0, int kind);
extern "C" void beNDMWMdlObject_RegisterReceiver(void);
extern "C" int beNDMWMdlObject_GetMeta(void);
extern "C" int StringPool_Allocate(...);
extern "C" void *beModelCtrlInfoWork_Create(...);
extern "C" void *beBaseInfoDataList_Create(...);
extern "C" int beModelCtrl__OnGenerate(...);
extern "C" int Memory_GetAllocatorBySelector(int);
extern "C" int StringChunk_ReleaseHeader(...);
extern "C" int StringPool_Construct(...);
extern "C" void *StringPool_Intern(...);
extern "C" int beMessenger_GetInt(...);
extern "C" int beMessenger_GetIntCount(...);
extern "C" int beMessenger_GetString(...);
extern "C" int igObject_GetAllocator(...);
extern "C" beModelCtrlInfoRamData *igProperty_FindByName(...);
extern "C" int KIND_OBJECT[4];
extern "C" int g_beNDMWMdlObject_metaObject[4];
extern "C" int g_propertyNameField[4];
extern "C" int g_stringPool[4];
extern "C" int kIGMemoryPoolHandleUser1[4];
extern "C" unsigned char g_useOwnerAllocator;
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
    return strcmp(kind, &KIND_OBJECT[0]) == 0;
}

void beNDMWMdlObject_RegisterReceiver(void)
{
}

void beNDMWMdlObject_OnGenerate(beNDMWMdlObject *self, beBaseInfoRam *ram) {
    if (ram->_dataList == 0) {
        int a = igObject_GetAllocator(ram);
        int al = g_useOwnerAllocator != 0 ? a : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
        igObject *created = (igObject *)beBaseInfoDataList_Create(al);
        /* matching construct: the new list is a temporary bound to the setter's reference parameter (it
         * takes the stack slot below the named info-work reference, as retail's +0x58 does) */
        DataListSlot::adopt(ram, created);
    }
    beModelCtrlInfoRamData *s3 = igProperty_FindByName(ram->_dataList, g_propertyNameField[0], "ONE");
    {
        int a2 = igObject_GetAllocator(self);
        int al2 = g_useOwnerAllocator != 0 ? a2 : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
        InfoWorkRef w((igObject *)beModelCtrlInfoWork_Create(al2));
        igObject *t2 = w.p;
        if (t2 != 0) t2->_refCount = t2->_refCount + 1;
        RefRelease::go((igObject *)s3->_work);
        s3->_work = (int)t2;
        if (beMessenger_GetIntCount(self->_messenger) != 0) {
            int str = beMessenger_GetString(self->_messenger, 0);
            int ns;
            beModelCtrlInfoWork *tg = (beModelCtrlInfoWork *)w.p;
            if (g_stringPool[0] == 0) {
                int v = StringPool_Allocate(16);
                if (v != 0) v = StringPool_Construct(v);
                g_stringPool[0] = v;
            }
            ns = (int)StringPool_Intern(g_stringPool[0], str);
            int old = tg->_hitParentName;
            if (old != 0) {
                int *hdr = (int *)(old - 8);
                int c = hdr[1] - 1;
                hdr[1] = c;
                if (c == 0) StringChunk_ReleaseHeader(*hdr, hdr);
            }
            tg->_hitParentName = ns;
            ((beModelCtrlInfoWork *)w.p)->_hitParentRamNo = beMessenger_GetInt(self->_messenger, 0);
        }
    }
    beModelCtrl__OnGenerate(self, ram);
}

int beNDMWMdlObject_GetMeta(void)
{
    return g_beNDMWMdlObject_metaObject[0];
}

#pragma pop
