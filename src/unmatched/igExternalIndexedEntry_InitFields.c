#include "dw4/reflected.h"
int FUN_002be610();
int FUN_002ea4b0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004c0c50[4];
extern int DAT_004c0c70[4];
extern int DAT_004c0c90[4];
extern int DAT_004c0cb0[4];
extern int DAT_00586418[4];
void igExternalIndexedEntry_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    void *temp_s1_2;
    int temp_s2;

    temp_s0 = (void *)DAT_00586418[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c0c50[0], 6);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002be610();
    ((igMetaField *)temp_s1)->_persistent = 0;
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3), -1);
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_002be610();
    ((igMetaField *)temp_s1_2)->_persistent = 0;
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5), -1);
    igMetaObject_NameFields(temp_s0, &DAT_004c0c70[0], &DAT_004c0c90[0], &DAT_004c0cb0[0], temp_s2);
}
