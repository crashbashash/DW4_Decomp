/* 0x003a1830 - Gap__Bec__beWeapon__vfunc_29: register the weapon with the messenger.
 * On the first call the attach-data list (FUN_0033f8b0 creates it) is built with four attach-data
 * objects (FUN_0033fa80) before the receiver is registered from the weapon's info table.  The new list
 * and each new element live on the stack in owning references whose releases the retail exception
 * table records. */
#include "dw4/reflected.h"
extern "C" {
igObject *FUN_0033f8b0(int);
igObject *FUN_0033fa80(int);
int Memory_GetAllocatorBySelector(int);
int ObjectList_AppendRetained(int, igObject *);
int beMessenger_RegisterReceiverFromInfo(int, int, int *);
void igObject_Destroy(igObject *);
int igObject_GetAllocator(...);
extern int DAT_0050fbf0[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
/* Owning stack reference to the new attach-data list: constructed from the creating call and released on
 * scope exit (reference count in the low 23 bits of _refCount).  The out-of-line copy the exception table
 * names is the retail body 0x0033f6d0 (config/SLUS-20836/unit-objects.json, duplicate __dt__7ListRefFv). */
class ListRef {
public:
    igObject *p;
    ListRef(igObject *o) : p(o) {}
    ~ListRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* Owning stack reference to one new attach-data element: released at the end of each loop pass.  The
 * out-of-line copy the exception table names is the retail body 0x003a19d0 (config/SLUS-20836/unit-objects.json,
 * duplicate __dt__9ObjectRefFv). */
class ObjectRef {
public:
    igObject *p;
    ObjectRef(igObject *o) : p(o) {}
    ~ObjectRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
extern "C" void Gap__Bec__beWeapon__vfunc_29(beWeapon *arg0, int arg1) {
    int var_v0;
    int var_s0;
    igObject *t;
    igObject *old;
    if (arg0->_attachDataList == 0) {
        var_v0 = igObject_GetAllocator();
        var_v0 = GPR_00554c14 ? var_v0 : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        ListRef list(FUN_0033f8b0(var_v0));
        t = list.p;
        if (t != 0) {
            t->_refCount = t->_refCount + 1;
        }
        old = (igObject *)arg0->_attachDataList;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7fffff) == 0) {
                igObject_Destroy(old);
            }
        }
        arg0->_attachDataList = (int)t;
        for (var_s0 = 0; var_s0 < 4; var_s0++) {
            var_v0 = igObject_GetAllocator(arg0);
            var_v0 = GPR_00554c14 ? var_v0 : Memory_GetAllocatorBySelector(DAT_00587110[0]);
            ObjectRef data(FUN_0033fa80(var_v0));
            ObjectList_AppendRetained(arg0->_attachDataList, data.p);
        }
    }
    beMessenger_RegisterReceiverFromInfo(arg0->_messenger, arg1, &DAT_0050fbf0[0]);
}
