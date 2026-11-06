#include "dw4/reflected.h"
int FUN_0013ad40();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00486708[4];
extern int DAT_00486710[4];
extern int DAT_00486718[4];
extern int DAT_00486720[4];
extern int DAT_0055f208[4];
void igDisplayListAttr_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_0055f208[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00486708[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0013ad40();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_00486710[0], &DAT_00486718[0], &DAT_00486720[0], temp_s2);
}
