#include "dw4/reflected.h"
int FUN_002be100();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004bfbb0[4];
extern int DAT_004bfbb8[4];
extern int DAT_004bfbc0[4];
extern int DAT_004bfbc8[4];
extern int DAT_00585bc0[4];
void igNamedObjectInfo_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00585bc0[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004bfbb0[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002be100();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004bfbb8[0], &DAT_004bfbc0[0], &DAT_004bfbc8[0], temp_s2);
}
