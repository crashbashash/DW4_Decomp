#include "dw4/reflected.h"
extern "C" {
int FUN_003c9480(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c9c30[4];
extern int DAT_004c9c38[4];
extern int DAT_004c9c40[4];
extern int DAT_004c9c48[4];
extern int DAT_0058ae08[4];
void beNDMWShopCtrlEvolve_InitFields(void);
}
void beNDMWShopCtrlEvolve_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058ae08[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c9c30[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_003c9480();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c9c38[0], &DAT_004c9c40[0], &DAT_004c9c48[0], temp_s2);
}
