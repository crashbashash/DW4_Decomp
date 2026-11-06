#include "dw4/reflected.h"
extern "C" {
int FUN_002cb110(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c97c0[4];
extern int DAT_004c97e0[4];
extern int DAT_004c9800[4];
extern int DAT_004c9820[4];
extern int DAT_0058abf8[4];
void beNDMWWindowSelect_InitFields(void);
}
void beNDMWWindowSelect_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058abf8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c97c0[0], 6);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002cb110();
    igMetaObject_NameFields(temp_s0, &DAT_004c97e0[0], &DAT_004c9800[0], &DAT_004c9820[0], temp_s2);
}
