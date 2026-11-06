#include "dw4/reflected.h"
int FUN_002cb340();
int FUN_002cb4f0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004c1478[4];
extern int DAT_004c1488[4];
extern int DAT_004c1498[4];
extern int DAT_004c14a8[4];
extern int DAT_005868f8[4];
void igContext_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    void *temp_s1_2;
    int temp_s2;

    temp_s0 = (void *)DAT_005868f8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c1478[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002cb4f0();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_002cb340();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c1488[0], &DAT_004c1498[0], &DAT_004c14a8[0], temp_s2);
}
