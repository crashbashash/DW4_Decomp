#include "dw4/reflected.h"
int FUN_002be610();
int FUN_002d3890();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004bfab8[4];
extern int DAT_004bfac8[4];
extern int DAT_004bfad8[4];
extern int DAT_004bfae8[4];
extern int DAT_00585b20[4];
void igObjectRefMetaField_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_00585b20[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004bfab8[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002be610();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    ((igMetaField *)temp_s1)->_deepCopyMethod = 1;
    ((igMetaField *)temp_s1)->_shallowCopyMethod = 1;
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1), 1);
    igMetaObject_NameFields(temp_s0, &DAT_004bfac8[0], &DAT_004bfad8[0], &DAT_004bfae8[0], temp_s2);
}
