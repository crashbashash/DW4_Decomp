#include "dw4/reflected.h"
int FUN_002d3890();
int FUN_002ea4b0();
int FUN_0044c880();
int FUN_0044cbd0();
int FUN_0044d170();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004d0020[4];
extern int DAT_004d0040[4];
extern int DAT_004d0060[4];
extern int DAT_004d0080[4];
extern int DAT_0058c240[4];
void igRadioGroup_InitFields(void) {
    int temp_s0;
    void *temp_s1;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;

    temp_s1 = (void *)DAT_0058c240[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004d0020[0], 6);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_0044d170();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_0044cbd0();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_0044c880();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3), 1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4), -1);
    igMetaObject_NameFields(temp_s1, &DAT_004d0040[0], &DAT_004d0060[0], &DAT_004d0080[0], temp_s0);
}
