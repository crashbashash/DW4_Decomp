/* 0x0035cf20 - beLOA_InitFields. four stack words are one int sp40[4]; flag bytes stored as char. Verified byte-identical by tools/verify.py.
 * C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
#include "dw4/reflected.h"
extern "C" {
int FUN_00138f20(void);
int FUN_00139640(void);
int FUN_00139f10(void);
int FUN_0013af00(void);
int FUN_0018e670(void *, int *);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c6470[4];
extern int DAT_004c64a0[4];
extern int DAT_004c64d0[4];
extern int DAT_004c6500[4];
extern int DAT_005892b0[4];
void beLOA_InitFields(void);
}
void beLOA_InitFields(void) {
    int sp40[4];
    int temp_s0;
    void *temp_s1;
    void *temp_a0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;

    temp_s1 = (void *)DAT_005892b0[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004c6470[0], 0xA);
    temp_a0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    sp40[0] = 0x3F800000;
    sp40[1] = 0x3F800000;
    sp40[2] = 0x3F800000;
    sp40[3] = 0x3F800000;
    FUN_0018e670(temp_a0, sp40);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 6));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_0013af00();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_00139640();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 8));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_00139f10();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 9));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_00138f20();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    igMetaObject_NameFields(temp_s1, &DAT_004c64a0[0], &DAT_004c64d0[0], &DAT_004c6500[0], temp_s0);
}
