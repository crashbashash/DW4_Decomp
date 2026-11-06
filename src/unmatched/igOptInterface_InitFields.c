#include "dw4/reflected.h"
int FUN_00228e60();
int FUN_002c3440();
int FUN_002c8e50();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
int igStringMetaField_SetDefaultText();
extern int DAT_00497bc0[4];
extern int DAT_00497bd0[4];
extern int DAT_00497be0[4];
extern int DAT_00497bf0[4];
extern int DAT_004e79b0[4];
extern int DAT_0056d860[4];
void igOptInterface_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_v0;
    void *temp_s1;

    temp_s1 = (void *)DAT_0056d860[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_00497bc0[0], 4);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_002c8e50();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    igStringMetaField_SetDefaultText(temp_v0, &DAT_004e79b0[0]);
    ((igStringMetaField *)temp_v0)->_destruct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_00228e60();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_002c3440();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    igMetaObject_NameFields(temp_s1, &DAT_00497bd0[0], &DAT_00497be0[0], &DAT_00497bf0[0], temp_s0);
}
