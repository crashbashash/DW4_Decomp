#include "dw4/reflected.h"
extern "C" {
int FUN_002cb110(void);
int FUN_003c9130(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c9998[4];
extern int DAT_004c99a0[4];
extern int DAT_004c99a8[4];
extern int DAT_004c99b0[4];
extern int DAT_0058acc8[4];
void beNDMWShopCtrlSales_InitFields(void);
}
void beNDMWShopCtrlSales_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    void *temp_s1_2;
    int temp_s2;

    temp_s0 = (void *)DAT_0058acc8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c9998[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_003c9130();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_002cb110();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c99a0[0], &DAT_004c99a8[0], &DAT_004c99b0[0], temp_s2);
}
