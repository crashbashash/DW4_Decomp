#include "dw4/reflected.h"
int FUN_001399d0();
int FUN_0013b070();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048c5b8[4];
extern int DAT_0048c5c0[4];
extern int DAT_0048c5c8[4];
extern int DAT_0048c5d0[4];
extern int DAT_00561ca8[4];
void igBlendListRecord_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    void *temp_s1_2;
    int temp_s2;

    temp_s0 = (void *)DAT_00561ca8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048c5b8[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_001399d0();
    ((igMetaField *)temp_s1)->_persistent = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_0013b070();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    ((igMetaField *)temp_s1_2)->_persistent = 0;
    igMetaObject_NameFields(temp_s0, &DAT_0048c5c0[0], &DAT_0048c5c8[0], &DAT_0048c5d0[0], temp_s2);
}
