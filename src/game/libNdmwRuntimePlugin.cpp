#include "dw4/reflected.h"
#define RELEASE(field) { igObject *old = (igObject *)(field); if (old != 0) { old->_refCount = old->_refCount - 1; if (((unsigned long long)((long long)(int)old->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(old); } } }
#define ALLOC(a) { a = igObject_GetAllocator(arg0); a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(g_ndmwAllocatorSelector[0]); }
#define CREATE(field, factory) { ALLOC(alloc) RELEASE(arg0->field) arg0->field = (int)factory(alloc); }
#define REGISTER(field) { int sub = arg0->field; if (sub != 0) FUN_00236ab0(arg1, sub); }

extern "C" void *FUN_003cae00(int allocator);
extern "C" void *FUN_003bbda0(int allocator);
extern "C" void *FUN_003bee90(int allocator);
extern "C" void *FUN_003c2340(int allocator);
extern "C" void *FUN_003b28a0(int allocator);
extern "C" void *FUN_003c7da0(int allocator);
extern "C" void *FUN_003c4700(int allocator);
extern "C" void *FUN_003bd3f0(int allocator);
extern "C" void *FUN_003bcc80(int allocator);
extern "C" void *FUN_003c9ca0(int allocator);
extern "C" void *FUN_003bb790(int allocator);
extern "C" void *FUN_003bf890(int allocator);
extern "C" void *FUN_003bf1b0(int allocator);
extern "C" void *FUN_003c0960(int allocator);
extern "C" void *FUN_003c1720(int allocator);
extern "C" void *FUN_003c1ca0(int allocator);
extern "C" void *FUN_003c0b50(int allocator);
extern "C" void *FUN_003c1120(int allocator);
extern "C" void *FUN_003c1ab0(int allocator);
extern "C" void *FUN_003c0f30(int allocator);
extern "C" void *FUN_003c0d40(int allocator);
extern "C" int FUN_00236ab0(int, int);
extern "C" void igObject_Destroy(void *obj);
extern "C" int Memory_GetAllocatorBySelector(int);
extern "C" int FUN_00236b10(int, int);
extern "C" int Gap__Bec__libNdmwRuntimePlugin__vfunc_20(void);
extern "C" int igObject_GetAllocator(libNdmwRuntimePlugin *);
extern "C" int g_ndmwAllocatorSelector[4];
extern "C" unsigned char GPR_00554c14;
extern "C" void Gap__Bec__libNdmwRuntimePlugin__vfunc_21(libNdmwRuntimePlugin *arg0, int arg1);
extern "C" void Gap__Bec__libNdmwRuntimePlugin__vfunc_22(libNdmwRuntimePlugin *arg0, int arg1);
extern "C" int g_libNdmwRuntimePlugin_metaObject[4];

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

void Gap__Bec__libNdmwRuntimePlugin__vfunc_22(libNdmwRuntimePlugin *arg0, int arg1) {
    int temp_a1;
    int temp_a1_10;
    int temp_a1_11;
    int temp_a1_12;
    int temp_a1_13;
    int temp_a1_14;
    int temp_a1_15;
    int temp_a1_16;
    int temp_a1_17;
    int temp_a1_18;
    int temp_a1_19;
    int temp_a1_20;
    int temp_a1_21;
    int temp_a1_2;
    int temp_a1_3;
    int temp_a1_4;
    int temp_a1_5;
    int temp_a1_6;
    int temp_a1_7;
    int temp_a1_8;
    int temp_a1_9;

    temp_a1 = arg0->_mdlMapCursor;
    if (temp_a1 != 0) {
        FUN_00236b10(arg1, temp_a1);
    }
    temp_a1_2 = arg0->_mdlMapBase;
    if (temp_a1_2 != 0) {
        FUN_00236b10(arg1, temp_a1_2);
    }
    temp_a1_3 = arg0->_mdlEffect;
    if (temp_a1_3 != 0) {
        FUN_00236b10(arg1, temp_a1_3);
    }
    temp_a1_4 = arg0->_mdlItem;
    if (temp_a1_4 != 0) {
        FUN_00236b10(arg1, temp_a1_4);
    }
    temp_a1_5 = arg0->_mdlObject;
    if (temp_a1_5 != 0) {
        FUN_00236b10(arg1, temp_a1_5);
    }
    temp_a1_6 = arg0->_mdlEBullet;
    if (temp_a1_6 != 0) {
        FUN_00236b10(arg1, temp_a1_6);
    }
    temp_a1_7 = arg0->_mdlEnemy;
    if (temp_a1_7 != 0) {
        FUN_00236b10(arg1, temp_a1_7);
    }
    temp_a1_8 = arg0->_mdlPBullet;
    if (temp_a1_8 != 0) {
        FUN_00236b10(arg1, temp_a1_8);
    }
    temp_a1_9 = arg0->_mdlPlayer2;
    if (temp_a1_9 != 0) {
        FUN_00236b10(arg1, temp_a1_9);
    }
    temp_a1_10 = arg0->_mdlPlayer;
    if (temp_a1_10 != 0) {
        FUN_00236b10(arg1, temp_a1_10);
    }
    temp_a1_11 = arg0->_status;
    if (temp_a1_11 != 0) {
        FUN_00236b10(arg1, temp_a1_11);
    }
    temp_a1_12 = arg0->_gameRam;
    if (temp_a1_12 != 0) {
        FUN_00236b10(arg1, temp_a1_12);
    }
    temp_a1_13 = arg0->_saveCtrl;
    if (temp_a1_13 != 0) {
        FUN_00236b10(arg1, temp_a1_13);
    }
    temp_a1_14 = arg0->_saveIntf;
    if (temp_a1_14 != 0) {
        FUN_00236b10(arg1, temp_a1_14);
    }
    temp_a1_15 = arg0->_loadIntf2;
    if (temp_a1_15 != 0) {
        FUN_00236b10(arg1, temp_a1_15);
    }
    temp_a1_16 = arg0->_loadCtrl2;
    if (temp_a1_16 != 0) {
        FUN_00236b10(arg1, temp_a1_16);
    }
    temp_a1_17 = arg0->_title2;
    if (temp_a1_17 != 0) {
        FUN_00236b10(arg1, temp_a1_17);
    }
    temp_a1_18 = arg0->_logo;
    if (temp_a1_18 != 0) {
        FUN_00236b10(arg1, temp_a1_18);
    }
    temp_a1_19 = arg0->_panelWaza;
    if (temp_a1_19 != 0) {
        FUN_00236b10(arg1, temp_a1_19);
    }
    temp_a1_20 = arg0->_afsSetup;
    if (temp_a1_20 != 0) {
        FUN_00236b10(arg1, temp_a1_20);
    }
    temp_a1_21 = arg0->_stageCtl;
    if (temp_a1_21 != 0) {
        FUN_00236b10(arg1, temp_a1_21);
    }
}

int Gap__Bec__libNdmwRuntimePlugin__vfunc_20(void)
{
    return g_libNdmwRuntimePlugin_metaObject[0];
}
