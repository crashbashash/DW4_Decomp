#include "dw4/reflected.h"
int FUN_002c8b30();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004c14c8[4];
extern int DAT_004c14d0[4];
extern int DAT_004c14d8[4];
extern int DAT_004c14e0[4];
extern int DAT_00586918[4];
void igCompoundMetaField_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00586918[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c14c8[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002c8b30();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c14d0[0], &DAT_004c14d8[0], &DAT_004c14e0[0], temp_s2);
}
