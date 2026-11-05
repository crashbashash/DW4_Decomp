/* 0x003cc7d0 - Gap__Bec__libNdmwRuntimePlugin__vfunc_21: build the plugin's 21 sub-objects (each factory takes the
 * object's memory allocator: the object's own pool or, when GPR_00554c14 is zero, the selector-108 default pool),
 * dropping any previous reference, then register every non-null sub-object with the owner passed in arg1
 * (vfunc_22 is the matching teardown that walks the same fields). */
#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
void *FUN_003cae00(int allocator);
void *FUN_003bbda0(int allocator);
void *FUN_003bee90(int allocator);
void *FUN_003c2340(int allocator);
void *FUN_003b28a0(int allocator);
void *FUN_003c7da0(int allocator);
void *FUN_003c4700(int allocator);
void *FUN_003bd3f0(int allocator);
void *FUN_003bcc80(int allocator);
void *FUN_003c9ca0(int allocator);
void *FUN_003bb790(int allocator);
void *FUN_003bf890(int allocator);
void *FUN_003bf1b0(int allocator);
void *FUN_003c0960(int allocator);
void *FUN_003c1720(int allocator);
void *FUN_003c1ca0(int allocator);
void *FUN_003c0b50(int allocator);
void *FUN_003c1120(int allocator);
void *FUN_003c1ab0(int allocator);
void *FUN_003c0f30(int allocator);
void *FUN_003c0d40(int allocator);
int FUN_00236ab0(int, int);
void igObject_Destroy(void *obj);
int igObject_GetAllocator(libNdmwRuntimePlugin *);
int Memory_GetAllocatorBySelector(int);
extern int DAT_00587108[4];
extern unsigned char GPR_00554c14;

/* drop one reference to a sub-object; free it when the 23-bit count reaches zero */
#define RELEASE(field) { igObject *old = (igObject *)(field); if (old != 0) { old->_refCount = old->_refCount - 1; if (((unsigned long long)((long long)(int)old->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(old); } } }
#define ALLOC(a) { a = igObject_GetAllocator(arg0); a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587108[0]); }
#define CREATE(field, factory) { ALLOC(alloc) RELEASE(arg0->field) arg0->field = (int)factory(alloc); }
#define REGISTER(field) { int sub = arg0->field; if (sub != 0) FUN_00236ab0(arg1, sub); }

void Gap__Bec__libNdmwRuntimePlugin__vfunc_21(libNdmwRuntimePlugin *arg0, int arg1) {
    int alloc;
    CREATE(_afsSetup, FUN_003cae00)
    CREATE(_stageCtl, FUN_003bbda0)
    CREATE(_panelWaza, FUN_003bee90)
    CREATE(_logo, FUN_003c2340)
    CREATE(_title2, FUN_003b28a0)
    CREATE(_loadCtrl2, FUN_003c7da0)
    CREATE(_loadIntf2, FUN_003c4700)
    CREATE(_saveCtrl, FUN_003bd3f0)
    CREATE(_saveIntf, FUN_003bcc80)
    CREATE(_gameRam, FUN_003c9ca0)
    CREATE(_status, FUN_003bb790)
    CREATE(_mdlPlayer, FUN_003bf890)
    CREATE(_mdlPlayer2, FUN_003bf1b0)
    CREATE(_mdlPBullet, FUN_003c0960)
    CREATE(_mdlEnemy, FUN_003c1720)
    CREATE(_mdlEBullet, FUN_003c1ca0)
    CREATE(_mdlObject, FUN_003c0b50)
    CREATE(_mdlItem, FUN_003c1120)
    CREATE(_mdlEffect, FUN_003c1ab0)
    CREATE(_mdlMapBase, FUN_003c0f30)
    CREATE(_mdlMapCursor, FUN_003c0d40)
    REGISTER(_afsSetup)
    REGISTER(_stageCtl)
    REGISTER(_panelWaza)
    REGISTER(_logo)
    REGISTER(_title2)
    REGISTER(_loadCtrl2)
    REGISTER(_loadIntf2)
    REGISTER(_saveCtrl)
    REGISTER(_saveIntf)
    REGISTER(_gameRam)
    REGISTER(_status)
    REGISTER(_mdlPlayer2)
    REGISTER(_mdlPBullet)
    REGISTER(_mdlEBullet)
    REGISTER(_mdlObject)
    REGISTER(_mdlItem)
    REGISTER(_mdlEffect)
    REGISTER(_mdlMapBase)
    REGISTER(_mdlMapCursor)
    REGISTER(_mdlPlayer)
    REGISTER(_mdlEnemy)
}
} /* extern "C" */
