#include "dw4/reflected.h"
extern "C" {
int FUN_003416b0(void);
int FUN_00342ce0(void);
int FUN_0034c8e0(void);
int FUN_0035b770(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c33a0[4];
extern int DAT_004c33c0[4];
extern int DAT_004c33e0[4];
extern int DAT_004c3400[4];
extern int DAT_00587c18[4];
void beTimer_InitFields(void);
}
void beTimer_InitFields(void) {
    int temp_s2;
    void *temp_s1_4;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00587c18[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c33a0[0], 5);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00342ce0();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_0034c8e0();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_0035b770();
    ((igObjectRefMetaField *)temp_s1_3)->_refCounted = 0;
    temp_s1_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    ((igObjectRefMetaField *)temp_s1_4)->_metaObject = FUN_003416b0();
    ((igRefMetaField *)temp_s1_4)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c33c0[0], &DAT_004c33e0[0], &DAT_004c3400[0], temp_s2);
}
