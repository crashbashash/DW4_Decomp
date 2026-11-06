#include "dw4/reflected.h"
int FUN_0044ff40();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004d0488[4];
extern int DAT_004d0490[4];
extern int DAT_004d0498[4];
extern int DAT_004d04a0[4];
extern int DAT_0058c428[4];
void igGuiComponentNode_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_0058c428[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d0488[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0044ff40();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004d0490[0], &DAT_004d0498[0], &DAT_004d04a0[0], temp_s2);
}
