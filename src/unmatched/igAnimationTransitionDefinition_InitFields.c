#include "dw4/reflected.h"
int FUN_001a9130();
int FUN_001a9830();
int FUN_001a9bb0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048d5b0[4];
extern int DAT_0048d5c0[4];
extern int DAT_0048d5d0[4];
extern int DAT_0048d5e0[4];
extern int DAT_005623c0[4];
void igAnimationTransitionDefinition_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    int temp_s2;

    temp_s0 = (void *)DAT_005623c0[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048d5b0[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_001a9130();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_001a9830();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_001a9bb0();
    igMetaObject_NameFields(temp_s0, &DAT_0048d5c0[0], &DAT_0048d5d0[0], &DAT_0048d5e0[0], temp_s2);
}
