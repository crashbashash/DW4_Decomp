#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#define ALLOC(dst, obj) { int alloc = igObject_GetAllocator(obj); if (GPR_00554c14 != 0) { dst = alloc; } else { dst = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]); } }

extern "C" int Gap__Bec__beNDMWSaveCtrl__vfunc_30(void);
extern "C" int Gap__Bec__beNDMWSaveCtrl__vfunc_20(void);
extern "C" void beMessenger_RegisterReceiverFromInfo(int, int, char *);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" int igObject_GetAllocator(...);
extern "C" int FUN_003bd390(...);
extern "C" int beNDMWMcUtilCtrl__Init(...);
extern "C" int ObjectList_AppendRetained(int, int);
extern "C" int beMessenger_AppendObject(...);
extern "C" int beMessenger_GetObjectCount(...);
extern "C" int beMessenger_ResolveEnumValue(...);
extern "C" int igProperty_FindByName(...);
extern "C" igObject * igInsightCore_FindManager(...);
extern "C" int g_bePadManager_metaObject[4];
extern "C" void Gap__Bec__beNDMWSaveCtrl__vfunc_32(beNDMWSaveCtrl *arg0);
extern "C" int g_beNDMWSaveCtrlInfo_metaObject[4];
extern "C" int g_beNDMWSaveCtrl_metaObject[4];
extern "C" char DAT_005194c0[];
extern "C" void Gap__Bec__beNDMWSaveCtrl__vfunc_29(beNDMWSaveCtrl *p0, int p1, char *p2);
extern "C" igObject *beBaseInfoDataList_Create(int);
extern "C" igObject *FUN_003bd0b0(int);
extern "C" igObject *beNDMWLoadCtrl2CommonIntf_Create(int);
extern "C" igObject *beNDMWLoadSavePlWork_Create(int);
extern "C" igObject *beNDMWDegiData_Create(int);
extern "C" int DAT_005194e0[4];
extern "C" int DAT_005194e8[4];
extern "C" int g_propertyNameField[4];
extern "C" int g_defaultAllocatorSelector[4];
extern "C" int g_beSystem_metaObject[4];
extern "C" unsigned char GPR_00554c14;
/* The incoming message: its +20 word is the enum name. */
struct A2 { char p[20]; int f20; };
/* Owning stack references while the controller list is wired up; each releases its object on scope
 * exit. */

class SaveCtrlDataRef {
public:
    igObject *p;
    SaveCtrlDataRef(igObject *o) : p(o) {}
    ~SaveCtrlDataRef() { igObject *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
class CommonIntfRef {
public:
    igObject *p;
    CommonIntfRef(igObject *o) : p(o) {}
    ~CommonIntfRef() { igObject *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
class DegiDataRef {
public:
    igObject *p;
    DegiDataRef(igObject *o) : p(o) {}
    ~DegiDataRef() { igObject *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
class FlagWorkRef {
public:
    igObject *p;
    FlagWorkRef(igObject *o) : p(o) {}
    ~FlagWorkRef() { igObject *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* Releases an object reference, used for the old list during the list install. */
struct Rel { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if ((object->_refCount & 0x7fffff) == 0)
            igObject_Destroy(object);
    }
} };
extern "C" int Gap__Bec__beNDMWSaveCtrl__vfunc_34(beNDMWSaveCtrl *arg0, beBaseInfoRam *arg1, A2 *arg2);

void Gap__Bec__beNDMWSaveCtrl__vfunc_32(beNDMWSaveCtrl *arg0) {
    igObject *temp_a0;
    igObject *temp_v0;

    if (arg0->_padManager == 0) {
        temp_v0 = igInsightCore_FindManager(arg0->_insight, g_bePadManager_metaObject[0]);
        if (temp_v0 != 0) {
            temp_v0->_refCount = temp_v0->_refCount + 1;
            ;
        }
        temp_a0 = (igObject *)arg0->_padManager;
        if (temp_a0 != 0) {
            temp_a0->_refCount = temp_a0->_refCount - 1;
            if ((temp_a0->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
                ;
            }
        }
        arg0->_padManager = (int)temp_v0;
        ;
    }
}

int Gap__Bec__beNDMWSaveCtrl__vfunc_30(void)
{
    return g_beNDMWSaveCtrlInfo_metaObject[0];
}

void Gap__Bec__beNDMWSaveCtrl__vfunc_29(beNDMWSaveCtrl *p0, int p1, char *p2)
{
    beMessenger_RegisterReceiverFromInfo(p0->_messenger, p1, DAT_005194c0);
}

int Gap__Bec__beNDMWSaveCtrl__vfunc_34(beNDMWSaveCtrl *arg0, beBaseInfoRam *arg1, A2 *arg2) {
    int e;
    int i;
    e = beMessenger_ResolveEnumValue(arg0->_messenger, FUN_003bd390(), arg2->f20);
    if (e == 0) {
        if (arg1->_dataList == 0) {
            int a;
            ALLOC(a, arg0);
            {
            igSmartPointer<igObject> list(beBaseInfoDataList_Create(a));
            igObject *t = list.p;
            if (t != 0) t->_refCount++;
            Rel::go((igObject *)arg1->_dataList);
            arg1->_dataList = (int)t;
            ALLOC(a, arg0);
            {
            SaveCtrlDataRef ctrl(FUN_003bd0b0(a));
            ObjectList_AppendRetained((int)(igObject *)arg1->_dataList, (int)ctrl.p);
            beNDMWSaveCtrlCtrlData *o = (beNDMWSaveCtrlCtrlData *)ctrl.p;
            o->_st0 = 1;
            o->_st3 = 0;
            o->_st2 = 0;
            o->_st1 = 0;
            }
            ALLOC(a, arg0);
            {
            CommonIntfRef common(beNDMWLoadCtrl2CommonIntf_Create(a));
            ((beNDMWLoadCtrl2CommonIntf *)common.p)->_system = ((int)igInsightCore_FindManager(arg0->_insight, g_beSystem_metaObject[0]));
            ((beNDMWLoadCtrl2CommonIntf *)common.p)->_inforam = (int)arg1;
            ((beNDMWLoadCtrl2CommonIntf *)common.p)->_insight = arg0->_insight;
            i = 0;
            do {
                ALLOC(a, arg0);
                {
                DegiDataRef degi(beNDMWDegiData_Create(a));
                ObjectList_AppendRetained(((beNDMWLoadCtrl2CommonIntf *)common.p)->_gameUseData, (int)degi.p);
                }
                ALLOC(a, arg0);
                {
                FlagWorkRef flag(beNDMWLoadSavePlWork_Create(a));
                ObjectList_AppendRetained(((beNDMWLoadCtrl2CommonIntf *)common.p)->_flagWork, (int)flag.p);
                }
                i++;
            } while (i < 4);
            ((beNDMWLoadCtrl2CommonIntf *)common.p)->_kindHard = 0;
            beNDMWMcUtilCtrl__Init(((beNDMWLoadCtrl2CommonIntf *)common.p)->_mcUtilCtrl, arg0->_messenger, 0);
            ObjectList_AppendRetained(arg1->_dataList, (int)common.p);
            }
            }
        }
        return 1;
    }
    igObject *p = (igObject *)arg1->_dataList;
    if (p == 0) return 1;
    if (p == 0) {
        int a;
        ALLOC(a, arg1);
        {
        igSmartPointer<igObject> fresh(beBaseInfoDataList_Create(a));
        igObject *t = fresh.p;
        if (t != 0) t->_refCount++;
        Rel::go((igObject *)arg1->_dataList);
        arg1->_dataList = (int)t;
        }
    }
    igProperty_FindByName(arg1->_dataList, g_propertyNameField[0], &DAT_005194e0[0]);
    switch (e) {
    case 1:
        return 1;
    case 2:
        return 1;
    case 3:
        if (beMessenger_GetObjectCount(arg0->_messenger) == 0) {
            if (arg1->_dataList == 0) {
                int a;
                ALLOC(a, arg1);
                {
                igSmartPointer<igObject> fresh(beBaseInfoDataList_Create(a));
                igObject *t = fresh.p;
                if (t != 0) t->_refCount++;
                Rel::go((igObject *)arg1->_dataList);
                arg1->_dataList = (int)t;
                }
            }
            beMessenger_AppendObject(arg0->_messenger, igProperty_FindByName(arg1->_dataList, g_propertyNameField[0], &DAT_005194e8[0]));
        }
        return 1;
    default:
        return 0;
    }
}

int Gap__Bec__beNDMWSaveCtrl__vfunc_20(void)
{
    return g_beNDMWSaveCtrl_metaObject[0];
}

