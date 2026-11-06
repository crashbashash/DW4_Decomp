#include "dw4/reflected.h"
extern "C" {
int FUN_0034c8e0(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004ca438[4];
extern int DAT_004ca440[4];
extern int DAT_004ca448[4];
extern int DAT_004ca450[4];
extern int DAT_0058b1d8[4];
void beNDMWSaveCtrl_InitFields(void);
}
void beNDMWSaveCtrl_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_0058b1d8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004ca438[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0034c8e0();
    igMetaObject_NameFields(temp_s0, &DAT_004ca440[0], &DAT_004ca448[0], &DAT_004ca450[0], temp_s2);
}
