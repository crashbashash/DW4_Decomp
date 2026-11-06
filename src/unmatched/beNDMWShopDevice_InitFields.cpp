#include "dw4/reflected.h"
extern "C" {
int FUN_003c9130(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c9940[4];
extern int DAT_004c9948[4];
extern int DAT_004c9950[4];
extern int DAT_004c9958[4];
extern int DAT_0058aca8[4];
void beNDMWShopDevice_InitFields(void);
}
void beNDMWShopDevice_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058aca8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c9940[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_003c9130();
    igMetaObject_NameFields(temp_s0, &DAT_004c9948[0], &DAT_004c9950[0], &DAT_004c9958[0], temp_s2);
}
