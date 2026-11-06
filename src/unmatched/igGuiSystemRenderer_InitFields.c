#include "dw4/reflected.h"
int FUN_00137fb0();
int FUN_0019cd50();
int FUN_001a38e0();
int FUN_0044f210();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004d0280[4];
extern int DAT_004d0290[4];
extern int DAT_004d02a0[4];
extern int DAT_004d02b0[4];
extern int DAT_0058c338[4];
void igGuiSystemRenderer_InitFields(void) {
    int temp_s2;
    void *temp_s1_4;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c338[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d0280[0], 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0019cd50();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_0044f210();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_001a38e0();
    ((igRefMetaField *)temp_s1_3)->_construct = 1;
    temp_s1_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    ((igObjectRefMetaField *)temp_s1_4)->_metaObject = FUN_00137fb0();
    igMetaObject_NameFields(temp_s0, &DAT_004d0290[0], &DAT_004d02a0[0], &DAT_004d02b0[0], temp_s2);
}
