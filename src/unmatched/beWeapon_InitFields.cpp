#include "dw4/reflected.h"
extern "C" {
int FUN_0033f8f0(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c3020[4];
extern int DAT_004c3028[4];
extern int DAT_004c3030[4];
extern int DAT_004c3038[4];
extern int DAT_00587a68[4];
void beWeapon_InitFields(void);
}
void beWeapon_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00587a68[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c3020[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0033f8f0();
    igMetaObject_NameFields(temp_s0, &DAT_004c3028[0], &DAT_004c3030[0], &DAT_004c3038[0], temp_s2);
}
