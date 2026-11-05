#include "dw4/reflected.h"
int FUN_002ba690();
int igRawRefMetaField_GetDefaultDescriptor();
int FUN_0030e9b0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004c1bf0[4];
extern int DAT_004c1c10[4];
extern int DAT_004c1c30[4];
extern int DAT_004c1c50[4];
extern void * DAT_00586c50[4];
extern void thunk_igQueue_GetMetaObject(void);

void igStandardQueue_InitFields(void) {
    int temp_s0;
    void *temp_s1;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;

    temp_s1 = (void *)(DAT_00586c50[0]);
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004c1bf0[0], 8);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_002ba690();
    ((igObjectRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_002ba690();
    ((igObjectRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_002ba690();
    ((igObjectRefMetaField *)temp_s2_3)->_construct = 1;
    FUN_0030e9b0(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3), 4);
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 6));
    ((igMemoryRefMetaField *)temp_s2_4)->_memType = igRawRefMetaField_GetDefaultDescriptor();
    ((igMemoryRefMetaField *)temp_s2_4)->_destruct = 1;
    ((igMemoryRefMetaField *)temp_s2_4)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)temp_s2_4)->_releaseOnReset = 1;
    FUN_0030e9b0(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7), 0x2000);
    igMetaObject_NameFields(temp_s1, &DAT_004c1c10[0], &DAT_004c1c30[0], &DAT_004c1c50[0], temp_s0);
    ((igMetaObject *)DAT_00586c50[0])->_writeProxy = (int)thunk_igQueue_GetMetaObject;
}
