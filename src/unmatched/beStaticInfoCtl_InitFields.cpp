#include "dw4/reflected.h"
extern "C" {
int FUN_0036aaf0(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c37a0[4];
extern int DAT_004c37a8[4];
extern int DAT_004c37b0[4];
extern int DAT_004c37b8[4];
extern int DAT_00587e10[4];
void beStaticInfoCtl_InitFields(void);
}
void beStaticInfoCtl_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_00587e10[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c37a0[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0036aaf0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c37a8[0], &DAT_004c37b0[0], &DAT_004c37b8[0], temp_s2);
}
