#include "dw4/reflected.h"
extern "C" {
int FUN_001a5d70(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c6bf0[4];
extern int DAT_004c6c10[4];
extern int DAT_004c6c30[4];
extern int DAT_004c6c50[4];
extern int DAT_005895f8[4];
void beFontInfoData_InitFields(void);
}
void beFontInfoData_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_005895f8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c6bf0[0], 7);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_001a5d70();
    igMetaObject_NameFields(temp_s0, &DAT_004c6c10[0], &DAT_004c6c30[0], &DAT_004c6c50[0], temp_s2);
}
