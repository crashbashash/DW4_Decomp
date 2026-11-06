#include "dw4/reflected.h"
int FUN_0044b880();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004d00e0[4];
extern int DAT_004d00e8[4];
extern int DAT_004d00f0[4];
extern int DAT_004d00f8[4];
extern int DAT_0058c298[4];
void igModel_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_0058c298[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d00e0[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0044b880();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004d00e8[0], &DAT_004d00f0[0], &DAT_004d00f8[0], temp_s2);
}
