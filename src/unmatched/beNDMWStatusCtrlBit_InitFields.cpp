#include "dw4/reflected.h"
extern "C" {
int igIntList_GetOrCreateMetaObject(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c9d98[4];
extern int DAT_004c9da0[4];
extern int DAT_004c9da8[4];
extern int DAT_004c9db0[4];
extern int DAT_0058aeb0[4];
void beNDMWStatusCtrlBit_InitFields(void);
}
void beNDMWStatusCtrlBit_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058aeb0[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c9d98[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c9da0[0], &DAT_004c9da8[0], &DAT_004c9db0[0], temp_s2);
}
