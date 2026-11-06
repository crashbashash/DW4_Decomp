#include "dw4/reflected.h"
int FUN_0013b070();
int FUN_00197af0();
int FUN_002ea4b0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048cd90[4];
extern int DAT_0048cdb0[4];
extern int DAT_0048cdd0[4];
extern int DAT_0048cdf0[4];
extern int DAT_00562030[4];
void igAttrStack_InitFields(void) {
    int temp_s2;
    void *temp_s1_4;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00562030[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048cd90[0], 8);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0013b070();
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1), -1);
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_0013b070();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_0013b070();
    ((igObjectRefMetaField *)temp_s1_3)->_refCounted = 0;
    temp_s1_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 7));
    ((igObjectRefMetaField *)temp_s1_4)->_metaObject = FUN_00197af0();
    ((igObjectRefMetaField *)temp_s1_4)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, &DAT_0048cdb0[0], &DAT_0048cdd0[0], &DAT_0048cdf0[0], temp_s2);
}
