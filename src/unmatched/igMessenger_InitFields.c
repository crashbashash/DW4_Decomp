#include "dw4/reflected.h"
int FUN_002320b0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00497fb8[4];
extern int DAT_00497fc0[4];
extern int DAT_00497fc8[4];
extern int DAT_00497fd0[4];
extern int DAT_0056dac8[4];
void igMessenger_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0056dac8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00497fb8[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002320b0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_00497fc0[0], &DAT_00497fc8[0], &DAT_00497fd0[0], temp_s2);
}
