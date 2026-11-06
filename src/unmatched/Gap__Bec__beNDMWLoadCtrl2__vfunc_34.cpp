#include "dw4/reflected.h"
extern "C" {
void igObject_Destroy(igObject *);
int Memory_GetAllocatorBySelector(...);
int igObject_GetAllocator(...);
int FUN_00236f80(...);
int FUN_003c7d40(...);
igObject *beBaseInfoDataList_Create(int);
igObject *FUN_003c7a40(int);
igObject *FUN_003c4be0(int);
igObject *FUN_003c56b0(int);
igObject *beNDMWDegiData_Create(int);
int FUN_003f0ed0(...);
int ObjectList_AppendRetained(int, int);
int beMessenger_AppendObject(...);
int beMessenger_AppendInt(...);
int beMessenger_GetObjectCount(...);
int beMessenger_GetIntCount(...);
int beMessenger_GetInt(...);
int beMessenger_GetObject(...);
int beMessenger_SelectGroup(...);
int beMessenger_DispatchSelected(...);
int beMessenger_ResolveEnumValue(...);
int igProperty_FindByName(...);
struct Rec { char p[12]; unsigned char b12; };
Rec *igProperty_GetRecordByte(...);
extern int DAT_00517e58[4];
extern int DAT_00518130[4];
extern int DAT_00518138[4];
extern int DAT_005181c8[4];
extern int DAT_005182a0[4];
extern int DAT_005182b0[4];
extern int DAT_00585be0[4];
extern int DAT_00587110[4];
extern int DAT_00587d08[4];
extern unsigned char GPR_00554c14;
}
/* Owning stack references while the controller list is wired up (retail keeps one stack slot per
 * holder; each releases its object on scope exit). One class per retail destructor copy:
 * DataListRef 0x0033e9c0 (the property list and the ensure-list temporaries), CtrlDataRef
 * 0x003f2cc0, CommonIntfRef 0x003f2c40, DegiDataRef 0x003e9010, FlagWorkRef 0x003f2bc0 (the
 * 0x003f2xxx copies sit behind this function and are emitted by it). */
class DataListRef {
public:
    igObject *p;
    DataListRef(igObject *o) : p(o) {}
    ~DataListRef() { igObject *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
class CtrlDataRef {
public:
    igObject *p;
    CtrlDataRef(igObject *o) : p(o) {}
    ~CtrlDataRef() { igObject *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
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
/* Releases an object reference (retail's old-list release inside the list install). */
struct Rel { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if ((object->_refCount & 0x7fffff) == 0)
            igObject_Destroy(object);
    }
} };
#define ALLOC(dst, obj) { int alloc = igObject_GetAllocator(obj); if (GPR_00554c14 != 0) { dst = alloc; } else { dst = Memory_GetAllocatorBySelector(DAT_00587110[0]); } }
extern "C" int Gap__Bec__beNDMWLoadCtrl2__vfunc_34(beNDMWLoadCtrl2 *arg0, beBaseInfoRam *arg1, beBaseInfo *arg2);
extern "C" int Gap__Bec__beNDMWLoadCtrl2__vfunc_34(beNDMWLoadCtrl2 *arg0, beBaseInfoRam *arg1, beBaseInfo *arg2);
extern "C" int Gap__Bec__beNDMWLoadCtrl2__vfunc_34(beNDMWLoadCtrl2 *arg0, beBaseInfoRam *arg1, beBaseInfo *arg2) {
    int e;
    int j;
    int i;
    e = beMessenger_ResolveEnumValue(arg0->_messenger, FUN_003c7d40(), arg2->_dataList);
    if (e == 0 || e == 1) {
        if (e == 1) {
            if (beMessenger_GetIntCount(arg0->_messenger) > 0) {
                arg0->_cameraMode = beMessenger_GetInt(arg0->_messenger, 0);
                arg0->_lightMode = beMessenger_GetInt(arg0->_messenger, 1);
            } else {
                arg0->_cameraMode = 0;
                arg0->_lightMode = 0;
            }
        }
        if (arg1->_dataList == 0) {
            int a;
            ALLOC(a, arg0);
            {
            DataListRef list(beBaseInfoDataList_Create(a));
            igObject *t = list.p;
            if (t != 0) t->_refCount++;
            Rel::go((igObject *)arg1->_dataList);
            arg1->_dataList = (int)t;
            ALLOC(a, arg0);
            {
            CtrlDataRef ctrl(FUN_003c7a40(a));
            ObjectList_AppendRetained((int)(igObject *)arg1->_dataList, (int)ctrl.p);
            beNDMWLoadCtrl2CtrlData *o = (beNDMWLoadCtrl2CtrlData *)ctrl.p;
            i = 1;
            o->_st0 = i;
            o->_st3 = 0;
            o->_st2 = 0;
            o->_st1 = 0;
            if (e == 1) {
                ((beNDMWLoadCtrl2CtrlData *)ctrl.p)->_isTitle = i;
                j = 0;
                do {
                    beMessenger_SelectGroup(arg0->_messenger, &DAT_005181c8[0]);
                    beMessenger_AppendInt(arg0->_messenger, j);
                    beMessenger_DispatchSelected(arg0->_messenger, &DAT_005182a0[0]);
                    j++;
                } while (j < 4);
            } else {
                do {
                    beMessenger_SelectGroup(arg0->_messenger, &DAT_005181c8[0]);
                    beMessenger_AppendInt(arg0->_messenger, i);
                    beMessenger_DispatchSelected(arg0->_messenger, &DAT_005182b0[0]);
                    if (igProperty_GetRecordByte(beMessenger_GetObject(arg0->_messenger, 0), &DAT_00517e58[0])->b12 != 1) {
                        beMessenger_SelectGroup(arg0->_messenger, &DAT_005181c8[0]);
                        beMessenger_AppendInt(arg0->_messenger, i);
                        beMessenger_DispatchSelected(arg0->_messenger, &DAT_005182a0[0]);
                    }
                    i++;
                } while (i < 4);
                ((beNDMWLoadCtrl2CtrlData *)ctrl.p)->_isTitle = 0;
            }
            }
            ALLOC(a, arg0);
            {
            CommonIntfRef common(FUN_003c4be0(a));
            ((beNDMWLoadCtrl2CommonIntf *)common.p)->_system = FUN_00236f80(arg0->_insight, DAT_00587d08[0]);
            ((beNDMWLoadCtrl2CommonIntf *)common.p)->_inforam = (int)arg1;
            ((beNDMWLoadCtrl2CommonIntf *)common.p)->_insight = arg0->_insight;
            if (e == 1) {
                ((beNDMWLoadCtrl2CommonIntf *)common.p)->_isTitle = 1;
            }
            i = 0;
            do {
                ALLOC(a, arg0);
                {
                DegiDataRef degi(beNDMWDegiData_Create(a));
                ObjectList_AppendRetained(((beNDMWLoadCtrl2CommonIntf *)common.p)->_gameUseData, (int)degi.p);
                }
                ALLOC(a, arg0);
                {
                FlagWorkRef flag(FUN_003c56b0(a));
                ObjectList_AppendRetained(((beNDMWLoadCtrl2CommonIntf *)common.p)->_flagWork, (int)flag.p);
                }
                i++;
            } while (i < 4);
            ((beNDMWLoadCtrl2CommonIntf *)common.p)->_kindHard = 0;
            FUN_003f0ed0(((beNDMWLoadCtrl2CommonIntf *)common.p)->_mcUtilCtrl, arg0->_messenger, 0);
            ObjectList_AppendRetained((int)(igObject *)arg1->_dataList, (int)common.p);
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
        DataListRef fresh(beBaseInfoDataList_Create(a));
        igObject *t = fresh.p;
        if (t != 0) t->_refCount++;
        Rel::go((igObject *)arg1->_dataList);
        arg1->_dataList = (int)t;
        }
    }
    igProperty_FindByName(arg1->_dataList, DAT_00585be0[0], &DAT_00518130[0]);
    switch (e) {
    case 2:
        return 1;
    case 3:
        if (beMessenger_GetObjectCount(arg0->_messenger) == 0) {
            if (arg1->_dataList == 0) {
                int a;
                ALLOC(a, arg1);
                {
                DataListRef fresh(beBaseInfoDataList_Create(a));
                igObject *t = fresh.p;
                if (t != 0) t->_refCount++;
                Rel::go((igObject *)arg1->_dataList);
                arg1->_dataList = (int)t;
                }
            }
            beMessenger_AppendObject(arg0->_messenger, igProperty_FindByName(arg1->_dataList, DAT_00585be0[0], &DAT_00518138[0]));
        }
        return 1;
    default:
        return 0;
    }
}
