#include "dw4/reflected.h"
extern "C" {
int FUN_002d3890(void *, int);
int FUN_0036a8d0(void);
int FUN_0036ac80(void);
int FUN_0036aec0(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c7bb0[4];
extern int DAT_004c7be0[4];
extern int DAT_004c7c10[4];
extern int DAT_004c7c40[4];
extern int DAT_00589d28[4];
void beBaseInfoRam_InitFields(void);
}
void beBaseInfoRam_InitFields(void) {
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00589d28[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c7bb0[0], 9);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0036ac80();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    ((igMetaField *)temp_s1)->_persistent = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_0036a8d0();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    ((igMetaField *)temp_s1_2)->_persistent = 0;
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3), 1);
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 8));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_0036aec0();
    igMetaObject_NameFields(temp_s0, &DAT_004c7be0[0], &DAT_004c7c10[0], &DAT_004c7c40[0], temp_s2);
}
