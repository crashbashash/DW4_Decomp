#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"

extern "C" {
igObject *FUN_0033f8b0(int);
igObject *FUN_0033fa80(int);
int Memory_GetAllocatorBySelector(int);
int ObjectList_AppendRetained(int, igObject *);
int beMessenger_RegisterReceiverFromInfo(int, int, int *);
int igObject_GetAllocator(...);

extern int DAT_0050fbf0[4];
extern int g_defaultAllocatorSelector[4];
extern unsigned char GPR_00554c14;
extern int g_beWeaponInfo_metaObject[4];
extern int g_beWeapon_metaObject[4];

void Gap__Bec__beWeapon__vfunc_32(beWeapon *arg0);
int Gap__Bec__beWeapon__vfunc_30(void);
void Gap__Bec__beWeapon__vfunc_29(beWeapon *arg0, int arg1);
void Gap__Bec__beWeapon__vfunc_31(void);
int Gap__Bec__beWeapon__vfunc_20(void);
}

void Gap__Bec__beWeapon__vfunc_32(beWeapon *arg0) {
    int *temp_a0;

    temp_a0 = (int *)arg0->_attachDataList;
    if (temp_a0 != 0) {
        temp_a0[1] = temp_a0[1] - 1;
        if (((unsigned long long) ((long long) temp_a0[1] << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->_attachDataList = 0;
}

int Gap__Bec__beWeapon__vfunc_30(void)
{
    return g_beWeaponInfo_metaObject[0];
}

class ObjectRef {
public:
    igObject *p;
    ObjectRef(igObject *o) : p(o) {}
    ~ObjectRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};

void Gap__Bec__beWeapon__vfunc_29(beWeapon *arg0, int arg1) {
    int var_v0;
    int var_s0;
    igObject *t;
    igObject *old;
    if (arg0->_attachDataList == 0) {
        var_v0 = igObject_GetAllocator();
        var_v0 = GPR_00554c14 ? var_v0 : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        igSmartPointer<igObject> list(FUN_0033f8b0(var_v0));
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
            var_v0 = GPR_00554c14 ? var_v0 : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
            ObjectRef data(FUN_0033fa80(var_v0));
            ObjectList_AppendRetained(arg0->_attachDataList, data.p);
        }
    }
    beMessenger_RegisterReceiverFromInfo(arg0->_messenger, arg1, &DAT_0050fbf0[0]);
}

void Gap__Bec__beWeapon__vfunc_31(void)
{
}

int Gap__Bec__beWeapon__vfunc_20(void)
{
    return g_beWeapon_metaObject[0];
}
