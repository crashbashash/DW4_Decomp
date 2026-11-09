#include "dw4/igSmartPointer.h"
extern "C" {
/* igObject header: the reference count at +4 is not a reflected field */
igObject *beBaseInfoDataList_Create(int);
int Memory_GetAllocatorBySelector(...);
int beMessenger_SendNamed(...);
int igObject_GetAllocator(...);
/* igProperty record payload: only the flag byte at +292 is used */
struct PropertyValueView { char p[292]; unsigned char f292; };
struct PropertyRecordView { char p[20]; PropertyValueView *q; };
PropertyRecordView *igProperty_FindByName(...);
extern int DAT_00516110[4];
extern int DAT_00516148[4];
extern int DAT_005164b0[4];
extern int DAT_00585be0[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
void Gap__Bec__beNDMWMdlPlayer__vfunc_42(beNDMWMdlPlayer *arg0, beBaseInfoRam *arg1);
}
struct Rel { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
/* Owning stack reference to the freshly created property list; released on scope exit once the ram
 * holds its own reference (reference count in the low 23 bits of _refCount). */

void Gap__Bec__beNDMWMdlPlayer__vfunc_42(beNDMWMdlPlayer *arg0, beBaseInfoRam *arg1) {
    igObject *s0;
    if (((igObject *)arg1->_dataList) == 0) {
        int alloc = igObject_GetAllocator(arg1);
        int a;
        if (GPR_00554c14 != 0) {
            a = alloc;
        } else {
            a = Memory_GetAllocatorBySelector(DAT_00587110[0]);
        }
        igSmartPointer<igObject> created(beBaseInfoDataList_Create(a));
        s0 = created.p;
        if (s0 != 0) {
            s0->_refCount++;
        }
        Rel::go(((igObject *)arg1->_dataList));
        arg1->_dataList = (int)s0;
    }
    PropertyValueView *q = igProperty_FindByName(((igObject *)arg1->_dataList), DAT_00585be0[0], DAT_00516110)->q;
    if (q->f292 != 0) {
        q->f292 = 0;
        beMessenger_SendNamed(arg0->_messenger, DAT_00516148, 0, arg1->_ramNo, DAT_005164b0);
    }
}
