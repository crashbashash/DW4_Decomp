#include "dw4/reflected.h"
int FUN_002cc2c0();
int FUN_002e3810(void *, float);
int FUN_002ebc00();
int FUN_002fe480();
int FUN_0030e750();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048c3a0[4];
extern int DAT_0048c3c0[4];
extern int DAT_0048c3e0[4];
extern int DAT_0048c400[4];
extern int DAT_00561ba0[4];
void FUN_001a21b0(void);  /* code at 0x1a21b0, passed by address (was DAT_1a21b0; docs/engine/function-inventory.md) */
void FUN_001a24e0(void);  /* code at 0x1a24e0, passed by address (was FUN_001a24e0; docs/engine/function-inventory.md) */
void igEnbayaAnimationSource_InitFields(void) {
    igMemoryRefMetaField *temp_s2;
    igFloatMetaField *temp_v0;
    igLongMetaField *temp_v0_2;
    igUnsignedCharArrayMetaField *tf;
    igEnumMetaField *tf2;
    int temp_s0;
    void *temp_s1;
    temp_s1 = (void *)DAT_00561ba0[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_0048c3a0[0], 6);
    temp_s2 = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s0);
    temp_s2->_memType = FUN_002cc2c0();
    temp_s2->_destruct = 1;
    temp_s2->_releaseOnCopy = 1;
    temp_s2->_releaseOnReset = 1;
    tf = (igUnsignedCharArrayMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1);
    tf->_num = 3;
    FUN_0030e750(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2), 3);
    tf2 = (igEnumMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3);
    tf2->_getMetaEnumFunction = (int)FUN_001a21b0;
    temp_v0 = (igFloatMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4);
    FUN_002e3810(temp_v0, -1.0f);
    temp_v0->_persistent = 0;
    temp_v0_2 = (igLongMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5);
    FUN_002ebc00(temp_v0_2, -1);
    temp_v0_2->_persistent = 0;
    igMetaObject_NameFields(temp_s1, &DAT_0048c3c0[0], &DAT_0048c3e0[0], &DAT_0048c400[0], temp_s0);
    FUN_002fe480(FUN_001a24e0);
}
