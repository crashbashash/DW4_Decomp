#include "dw4/reflected.h"
extern "C" {
void igObject_Destroy(igObject *);
int Memory_GetAllocatorBySelector(...);
int igObject_GetAllocator(...);
int FUN_00236f80(...);
igObject *beBaseInfoDataList_Create(int);
igObject *FUN_003bd0b0(int);
int FUN_003bd390(...);
igObject *FUN_003c4be0(int);
igObject *FUN_003c56b0(int);
igObject *beNDMWDegiData_Create(int);
int FUN_003f0ed0(...);
int ObjectList_AppendRetained(int, int);
int beMessenger_AppendObject(...);
int beMessenger_GetObjectCount(...);
int beMessenger_ResolveEnumValue(...);
int igProperty_FindByName(...);
extern int DAT_005194e0[4];
extern int DAT_005194e8[4];
extern int DAT_00585be0[4];
extern int DAT_00587110[4];
extern int DAT_00587d08[4];
extern unsigned char GPR_00554c14;
}
/* The incoming message: its +20 word is the enum name. */
struct A2 { char p[20]; int f20; };
/* Owning stack references while the controller list is wired up; each releases its object on scope
 * exit. */
template <class T> class igSmartPointer {
public:
    T *p;
    igSmartPointer(T *o) : p(o) {}
    ~igSmartPointer() { T *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
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
#define ALLOC(dst, obj) { int alloc = igObject_GetAllocator(obj); if (GPR_00554c14 != 0) { dst = alloc; } else { dst = Memory_GetAllocatorBySelector(DAT_00587110[0]); } }
extern "C" int Gap__Bec__beNDMWSaveCtrl__vfunc_34(beNDMWSaveCtrl *arg0, beBaseInfoRam *arg1, A2 *arg2);
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
            CommonIntfRef common(FUN_003c4be0(a));
            ((beNDMWLoadCtrl2CommonIntf *)common.p)->_system = FUN_00236f80(arg0->_insight, DAT_00587d08[0]);
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
                FlagWorkRef flag(FUN_003c56b0(a));
                ObjectList_AppendRetained(((beNDMWLoadCtrl2CommonIntf *)common.p)->_flagWork, (int)flag.p);
                }
                i++;
            } while (i < 4);
            ((beNDMWLoadCtrl2CommonIntf *)common.p)->_kindHard = 0;
            FUN_003f0ed0(((beNDMWLoadCtrl2CommonIntf *)common.p)->_mcUtilCtrl, arg0->_messenger, 0);
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
    igProperty_FindByName(arg1->_dataList, DAT_00585be0[0], &DAT_005194e0[0]);
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
            beMessenger_AppendObject(arg0->_messenger, igProperty_FindByName(arg1->_dataList, DAT_00585be0[0], &DAT_005194e8[0]));
        }
        return 1;
    default:
        return 0;
    }
}
