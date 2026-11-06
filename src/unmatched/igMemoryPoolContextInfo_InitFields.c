#include "dw4/reflected.h"
int FUN_002bfd60();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004c0168[4];
extern int DAT_004c0170[4];
extern int DAT_004c0178[4];
extern int DAT_004c0180[4];
extern int DAT_00585e88[4];
void igMemoryPoolContextInfo_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_00585e88[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c0168[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002bfd60();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c0170[0], &DAT_004c0178[0], &DAT_004c0180[0], temp_s2);
}
