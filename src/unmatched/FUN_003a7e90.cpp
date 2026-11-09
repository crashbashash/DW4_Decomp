/* The timer record returned by igProperty_FindByName; +32 is the int64 duration. */
#include "dw4/igSmartPointer.h"
struct P { char pad[32]; long long f32; };
extern "C" {
igObject *beBaseInfoDataList_Create(...);
long long FUN_003a7fd0(...);
int Memory_GetAllocatorBySelector(...);
int igObject_GetAllocator(...);
P *igProperty_FindByName(...);
extern int DAT_00585be0[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
int FUN_003a7e90(beAction2InfoRam *arg0, int arg1);
}
/* Owning stack reference to the freshly created property list; released on scope exit once the ram
 * holds its own reference (reference count in the low 23 bits of _refCount). */

/* matching construct: the (igObject *)/(int) casts on _dataList stand in for a 4-byte reference field */
int FUN_003a7e90(beAction2InfoRam *arg0, int arg1) {
    if (arg0->_dataList == 0) {
        int al;
        igObject *o;
        al = igObject_GetAllocator(arg0);
        al = GPR_00554c14 != 0 ? al : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        igSmartPointer<igObject> created(beBaseInfoDataList_Create(al));
        igObject *s0 = created.p;
        if (s0 != 0) {
            s0->_refCount = s0->_refCount + 1;
        }
        o = (igObject *)arg0->_dataList;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        arg0->_dataList = (int)s0;
    }
    {
        P *p = igProperty_FindByName((igObject *)arg0->_dataList, DAT_00585be0[0], arg1);
        if (p == 0) {
            return 1;
        }
        long long t = p->f32;
        return t < FUN_003a7fd0(arg0, arg1);
    }
}
