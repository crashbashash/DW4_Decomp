#include "dw4/reflected.h"
int FUN_001a4d90();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048b218[4];
extern int DAT_0048b220[4];
extern int DAT_0048b228[4];
extern int DAT_0048b230[4];
extern int DAT_00561308[4];
void igSwitch_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_00561308[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048b218[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_001a4d90();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_0048b220[0], &DAT_0048b228[0], &DAT_0048b230[0], temp_s2);
}
