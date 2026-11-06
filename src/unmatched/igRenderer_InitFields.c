#include "dw4/reflected.h"
int FUN_0014a040();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004cff98[4];
extern int DAT_004cffa0[4];
extern int DAT_004cffa8[4];
extern int DAT_004cffb0[4];
extern int DAT_0058c208[4];
void igRenderer_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_0058c208[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cff98[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0014a040();
    igMetaObject_NameFields(temp_s0, &DAT_004cffa0[0], &DAT_004cffa8[0], &DAT_004cffb0[0], temp_s2);
}
