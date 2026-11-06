#include "dw4/reflected.h"
extern "C" {
int igIntList_GetOrCreateMetaObject(void);
int FUN_003b3730(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c9b50[4];
extern int DAT_004c9b58[4];
extern int DAT_004c9b60[4];
extern int DAT_004c9b68[4];
extern int DAT_0058ada0[4];
void beNDMWShopCtrlA0_InitFields(void);
}
void beNDMWShopCtrlA0_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058ada0[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c9b50[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_003b3730();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c9b58[0], &DAT_004c9b60[0], &DAT_004c9b68[0], temp_s2);
}
