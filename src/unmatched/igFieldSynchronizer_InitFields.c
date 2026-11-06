#include "dw4/reflected.h"
int FUN_00450c70();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004d06c8[4];
extern int DAT_004d06d0[4];
extern int DAT_004d06d8[4];
extern int DAT_004d06e0[4];
extern int DAT_0058c538[4];
void igFieldSynchronizer_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c538[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d06c8[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00450c70();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004d06d0[0], &DAT_004d06d8[0], &DAT_004d06e0[0], temp_s2);
}
