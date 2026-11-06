#include "dw4/reflected.h"
extern "C" {
int FUN_001313d0(void);
int FUN_00135e60(void);
int FUN_00138f20(void);
int FUN_00139640(void);
int FUN_0036d9f0(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c7ec0[4];
extern int DAT_004c7f20[4];
extern int DAT_004c7f80[4];
extern int DAT_004c7fe0[4];
extern int DAT_00589e98[4];
void beAction2InfoWork_InitFields(void);
}
void beAction2InfoWork_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_s1_4;
    void *temp_s1_5;
    void *temp_s0;

    temp_s0 = (void *)DAT_00589e98[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c7ec0[0], 0x15);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0036d9f0();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0x11));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_00138f20();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0x12));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_00139640();
    temp_s1_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0x13));
    ((igObjectRefMetaField *)temp_s1_4)->_metaObject = FUN_001313d0();
    temp_s1_5 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0x14));
    ((igObjectRefMetaField *)temp_s1_5)->_metaObject = FUN_00135e60();
    igMetaObject_NameFields(temp_s0, &DAT_004c7f20[0], &DAT_004c7f80[0], &DAT_004c7fe0[0], temp_s2);
}
