#include "dw4/reflected.h"
int FUN_0014a040();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004882d8[4];
extern int DAT_004882e0[4];
extern int DAT_004882e8[4];
extern int DAT_004882f0[4];
extern int DAT_0055f8d0[4];
void igVisualContextCapabilityManager_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_0055f8d0[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004882d8[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0014a040();
    ((igMetaField *)temp_s1)->_persistent = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004882e0[0], &DAT_004882e8[0], &DAT_004882f0[0], temp_s2);
}
