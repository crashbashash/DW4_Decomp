#include "dw4/igSmartPointer.h"

extern "C" int strcmp(int, int *);
extern "C" int Gap__Bec__beNDMWMdlObject__vfunc_35(int dummy0, int arg1);
extern "C" void Gap__Bec__beNDMWMdlObject__vfunc_37(void);
extern "C" int Gap__Bec__beNDMWMdlObject__vfunc_20(void);
extern "C" int FUN_002eb010(...);
extern "C" void *FUN_00350020(...);
extern "C" void *beBaseInfoDataList_Create(...);
extern "C" int FUN_00396740(...);
extern "C" int Memory_GetAllocatorBySelector(int);
extern "C" int StringChunk_ReleaseHeader(...);
extern "C" int StringPool_Construct(...);
extern "C" void *StringPool_Intern(...);
extern "C" int beMessenger_GetInt(...);
extern "C" int beMessenger_GetIntCount(...);
extern "C" int beMessenger_GetString(...);
extern "C" int igObject_GetAllocator(...);
extern "C" void *igProperty_FindByName(...);
extern "C" int DAT_00515f40[4];
extern "C" int g_beNDMWMdlObject_metaObject[4];
extern "C" int DAT_00515f50[4];
extern "C" int g_propertyNameField[4];
extern "C" int g_stringPool[4];
extern "C" int g_defaultAllocatorSelector[4];
extern "C" unsigned char GPR_00554c14;
/* Property record: reference at +20. */
struct OneProperty { char pad[20]; igObject *f20; };
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
extern "C" void Gap__Bec__beNDMWMdlObject__vfunc_36(beNDMWMdlObject *arg0, beBaseInfoRam *arg1);

int Gap__Bec__beNDMWMdlObject__vfunc_35(int dummy0, int arg1) {
    return strcmp(arg1, &DAT_00515f40[0]) == 0;
}

void Gap__Bec__beNDMWMdlObject__vfunc_37(void)
{
}

void Gap__Bec__beNDMWMdlObject__vfunc_36(beNDMWMdlObject *arg0, beBaseInfoRam *arg1) {
    if (arg1->_dataList == 0) {
        int a = igObject_GetAllocator(arg1);
        int al = GPR_00554c14 != 0 ? a : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        igObject *created = (igObject *)beBaseInfoDataList_Create(al);
        /* matching construct: the new list is a temporary bound to the setter's reference parameter (it
         * takes the stack slot below the named info-work reference, as retail's +0x58 does) */
        DataListSlot::adopt(arg1, created);
    }
    OneProperty *s3 = (OneProperty *)igProperty_FindByName(arg1->_dataList, g_propertyNameField[0], DAT_00515f50);
    {
        int a2 = igObject_GetAllocator(arg0);
        int al2 = GPR_00554c14 != 0 ? a2 : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        InfoWorkRef w((igObject *)FUN_00350020(al2));
        igObject *t2 = w.p;
        if (t2 != 0) t2->_refCount = t2->_refCount + 1;
        RefRelease::go(s3->f20);
        s3->f20 = t2;
        if (beMessenger_GetIntCount(arg0->_messenger) != 0) {
            int str = beMessenger_GetString(arg0->_messenger, 0);
            int ns;
            beModelCtrlInfoWork *tg = (beModelCtrlInfoWork *)w.p;
            if (g_stringPool[0] == 0) {
                int v = FUN_002eb010(16);
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
            ((beModelCtrlInfoWork *)w.p)->_hitParentRamNo = beMessenger_GetInt(arg0->_messenger, 0);
        }
    }
    FUN_00396740(arg0, arg1);
}

int Gap__Bec__beNDMWMdlObject__vfunc_20(void)
{
    return g_beNDMWMdlObject_metaObject[0];
}
