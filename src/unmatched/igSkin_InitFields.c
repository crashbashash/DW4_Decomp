#include "dw4/reflected.h"
int FUN_0018a6a0();
int FUN_0019cd50();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048b560[4];
extern int DAT_0048b568[4];
extern int DAT_0048b570[4];
extern int DAT_0048b578[4];
extern int DAT_00561490[4];
void igSkin_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00561490[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048b560[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0019cd50();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_0018a6a0();
    igMetaObject_NameFields(temp_s0, &DAT_0048b568[0], &DAT_0048b570[0], &DAT_0048b578[0], temp_s2);
}
