#include "dw4/reflected.h"
extern "C" {
void *beBaseInfoDataList_Create(...);
int FUN_00396740(...);
void *FUN_003c1910(...);
int Memory_GetAllocatorBySelector(...);
int beDataBase_GetRecordInt(...);
int beMessenger_AppendInt(...);
int beMessenger_EnqueueSelected(...);
int beMessenger_GetInt(...);
int beMessenger_GetIntCount(...);
int beMessenger_GetObject(...);
int beMessenger_PopArgContext(...);
int beMessenger_PrepareDelayedSelection(...);
int beMessenger_PushArgContext(...);
int beMessenger_SendNamed(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
void *igProperty_FindByName(...);
extern int DAT_004e0858[4];
extern int DAT_00515e28[4];
extern int DAT_00515e30[4];
extern int DAT_00515e38[4];
extern int DAT_00515e48[4];
extern int DAT_00515e50[4];
extern int DAT_00515e60[4];
extern int DAT_00515e68[4];
extern int DAT_00585be0[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
/* Property record: reference at +20. */
struct Holder { char pad[20]; igObject *f20; };
/* matching construct: inline static helper reproduces the retail release sequence */
struct Rel {
    static inline void go(igObject *p) {
        if (p != 0) {
            p->_refCount = p->_refCount - 1;
            if ((p->_refCount & 0x7fffff) == 0) igObject_Destroy(p);
        }
    }
};
/* Owning stack reference to the slot's new data list; released on scope exit (reference count in
 * the low 23 bits of _refCount). */
template <class T> class igSmartPointer {
public:
    T *p;
    igSmartPointer(T *o) : p(o) {}
    ~igSmartPointer() { T *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* Owning stack reference to the new enemy info work; released on scope exit. */
class InfoWorkRef {
public:
    igObject *p;
    InfoWorkRef(igObject *o) : p(o) {}
    ~InfoWorkRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
struct Slot { static inline void setDataList(beBaseInfoRam *ram, const igSmartPointer<igObject> &r) {
    igObject *t = r.p;
    if (t != 0) t->_refCount = t->_refCount + 1;
    Rel::go((igObject *)ram->_dataList);
    ram->_dataList = (int)t;
} };
extern "C" void Gap__Bec__beNDMWMdlEnemy__vfunc_36(beNDMWMdlEnemy *arg0, beBaseInfoRam *arg1) {
    beBaseInfo *s0;
    Holder *s4;
    int *a2;
    int v;
    s0 = (beBaseInfo *)arg1->_parentInfo;
    if (arg1->_dataList == 0) {
        int a = igObject_GetAllocator(arg1);
        a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        igObject *created = (igObject *)beBaseInfoDataList_Create(a);
        /* matching construct: the new list is a temporary bound to the setter's reference parameter (it
         * takes the stack slot below the named info-work reference, as retail's +0x68 does) */
        Slot::setDataList(arg1, igSmartPointer<igObject>(created));
    }
    s4 = (Holder *)igProperty_FindByName((void *)arg1->_dataList, DAT_00585be0[0], &DAT_00515e30[0]);
    {
        int a = igObject_GetAllocator(arg0);
        a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        InfoWorkRef work((igObject *)FUN_003c1910(a));
        igObject *t = work.p;
        if (t != 0) t->_refCount = t->_refCount + 1;
        Rel::go(s4->f20);
        s4->f20 = t;
        if (beMessenger_GetIntCount(arg0->_messenger) != 0) {
            ((beNDMWMdlEnemyInfoWork *)work.p)->_recNo = beMessenger_GetInt(arg0->_messenger, 0);
            ((beDataObjInt *)((beNDMWMdlEnemyInfoWork *)work.p)->_mHp)->_data = beMessenger_GetInt(arg0->_messenger, 1);
            ((beDataObjInt *)((beNDMWMdlEnemyInfoWork *)work.p)->_hp)->_data = beMessenger_GetInt(arg0->_messenger, 1);
            beMessenger_PushArgContext(arg0->_messenger);
            beMessenger_SendNamed(arg0->_messenger, &DAT_00515e38[0], &DAT_00515e48[0], 0, &DAT_00515e50[0]);
            v = beDataBase_GetRecordInt(beMessenger_GetObject(arg0->_messenger, 0), ((beNDMWMdlEnemyInfoWork *)work.p)->_recNo, &DAT_00515e60[0]);
            if (v != 0) {
                int k = arg1->_ramNo;
                a2 = s0->_name ? (int *)s0->_name : &DAT_004e0858[0];
                beMessenger_PrepareDelayedSelection(arg0->_messenger, &DAT_00515e28[0], a2, k);
                beMessenger_AppendInt(arg0->_messenger, v);
                beMessenger_EnqueueSelected(arg0->_messenger, &DAT_00515e68[0], 0x3C);
            }
            beMessenger_PopArgContext(arg0->_messenger);
        }
    }
    FUN_00396740(arg0, arg1);
}
