#include "dw4/reflected.h"
extern "C" {
int FUN_002d3890(void *, int);
int FUN_0034c8e0(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c3b88[4];
extern int DAT_004c3b90[4];
extern int DAT_004c3b98[4];
extern int DAT_004c3ba0[4];
extern int DAT_00587f98[4];
void beSelectCtrl_InitFields(void);
}
void beSelectCtrl_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_00587f98[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c3b88[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0034c8e0();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1), 1);
    igMetaObject_NameFields(temp_s0, &DAT_004c3b90[0], &DAT_004c3b98[0], &DAT_004c3ba0[0], temp_s2);
}
