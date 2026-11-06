#include "dw4/reflected.h"
extern "C" {
int FUN_0019f210(void);
int FUN_001e4240(void);
int FUN_002b9120(void);
int FUN_002b9540(void);
int FUN_002c3440(void);
int FUN_002c7300(void);
int FUN_002d3890(void *, int);
int FUN_002e3810(void *, float);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
int igStringMetaField_SetDefaultText(void *, int);
extern int DAT_004c35a0[4];
extern int DAT_004c3610[4];
extern int DAT_004c3680[4];
extern int DAT_004c36f0[4];
extern int DAT_00587d08[4];
void beSystem_InitFields(void);
}
void beSystem_InitFields(void) {
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00587d08[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c35a0[0], 0x1A);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3), 1.0f);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 7));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_001e4240();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 8));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_002b9120();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xA), 0);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xB), 1);
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xC));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_002c7300();
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xD));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_002b9540();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xE));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_002c3440();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xF));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = FUN_0019f210();
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x15), 1);
    igMetaObject_NameFields(temp_s0, &DAT_004c3610[0], &DAT_004c3680[0], &DAT_004c36f0[0], temp_s1);
}
