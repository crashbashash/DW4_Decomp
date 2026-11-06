#include "dw4/reflected.h"
extern "C" {
int FUN_0036b600(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c7da8[4];
extern int DAT_004c7db0[4];
extern int DAT_004c7db8[4];
extern int DAT_004c7dc0[4];
extern int DAT_00589e20[4];
void beActionStarterInfo_InitFields(void);
}
void beActionStarterInfo_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00589e20[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c7da8[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0036b600();
    igMetaObject_NameFields(temp_s0, &DAT_004c7db0[0], &DAT_004c7db8[0], &DAT_004c7dc0[0], temp_s2);
}
