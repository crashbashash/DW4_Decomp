#include "dw4/reflected.h"
int FUN_0018a6a0();
int FUN_002b9540();
int FUN_002bcbb0();
int FUN_002c8e50();
int FUN_002d3890();
int FUN_002ebc00();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048cad0[4];
extern int DAT_0048caf0[4];
extern int DAT_0048cb10[4];
extern int DAT_0048cb30[4];
extern int DAT_00561ef0[4];
void igBoundingBoxesMaker_InitFields(void) {
    int temp_s2;
    void *temp_s1_4;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00561ef0[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048cad0[0], 8);
    FUN_002ebc00(igMetaObject_GetFieldAt(temp_s0, temp_s2), -1);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1), 1);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2), 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0018a6a0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_002bcbb0();
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5), 1);
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_002b9540();
    temp_s1_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 7));
    ((igObjectRefMetaField *)temp_s1_4)->_metaObject = FUN_002c8e50();
    igMetaObject_NameFields(temp_s0, &DAT_0048caf0[0], &DAT_0048cb10[0], &DAT_0048cb30[0], temp_s2);
}
