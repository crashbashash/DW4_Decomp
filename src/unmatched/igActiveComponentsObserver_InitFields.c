#include "dw4/reflected.h"
int FUN_0044ff40();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004d02c8[4];
extern int DAT_004d02d8[4];
extern int DAT_004d02e8[4];
extern int DAT_004d02f8[4];
extern int DAT_0058c360[4];
void igActiveComponentsObserver_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    int temp_s2;

    temp_s0 = (void *)DAT_0058c360[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d02c8[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0044ff40();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_0044ff40();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_0044ff40();
    igMetaObject_NameFields(temp_s0, &DAT_004d02d8[0], &DAT_004d02e8[0], &DAT_004d02f8[0], temp_s2);
}
