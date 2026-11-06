#include "dw4/reflected.h"
int FUN_00226340();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00497c38[4];
extern int DAT_00497c40[4];
extern int DAT_00497c48[4];
extern int DAT_00497c50[4];
extern int DAT_0056d8a8[4];
void igMessageInterface_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_0056d8a8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00497c38[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00226340();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_00497c40[0], &DAT_00497c48[0], &DAT_00497c50[0], temp_s2);
}
