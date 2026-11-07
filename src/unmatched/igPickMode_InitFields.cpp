#include "dw4/reflected.h"
extern "C" {
int FUN_00188260(void);
int FUN_0018e2f0(void *, int *);
int FUN_0019dfd0(void);
int FUN_0019f670(void);
int FUN_002e3810(void *, float);
int FUN_0044ded0(void);
int FUN_0044e430(void);
int FUN_0045b420(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004d13a0[4];
extern int DAT_004d13d0[4];
extern int DAT_004d1400[4];
extern int DAT_004d1430[4];
extern int DAT_0058cb88[4];
void igPickMode_InitFields(void);
}
void igPickMode_InitFields(void) {
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s1;
    int temp_s0;
    int sp48[2];
    void *temp_a0;

    temp_s1 = (void *)DAT_0058cb88[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004d13a0[0], 0xC);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_0045b420();
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_0044ded0();
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_0044e430();
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_0044e430();
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_0019dfd0();
    ((igObjectRefMetaField *)temp_s2_5)->_construct = 1;
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 6));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = FUN_00188260();
    ((igObjectRefMetaField *)temp_s2_6)->_construct = 1;
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7), 0.0f);
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 9));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = FUN_0019f670();
    temp_a0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xB));
    sp48[0] = 0;
    sp48[1] = 0;
    FUN_0018e2f0(temp_a0, sp48);
    igMetaObject_NameFields(temp_s1, &DAT_004d13d0[0], &DAT_004d1400[0], &DAT_004d1430[0], temp_s0);
}
