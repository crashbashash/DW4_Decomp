#include "dw4/reflected.h"
extern "C" {
int FUN_002b9120(void);
int FUN_002c3440(void);
int FUN_002c7150(void);
int FUN_002ea4b0(void *, int);
int FUN_00342ce0(void);
int FUN_00357910(void);
int FUN_00459380(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c6e90[4];
extern int DAT_004c6ec0[4];
extern int DAT_004c6ef0[4];
extern int DAT_004c6f20[4];
extern int DAT_005896f8[4];
void beFileListInfoManager_InitFields(void);
}
void beFileListInfoManager_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s2_8;
    void *temp_s1;

    temp_s1 = (void *)DAT_005896f8[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004c6e90[0], 0xC);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_00342ce0();
    ((igObjectRefMetaField *)temp_s2)->_refCounted = 0;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_00357910();
    ((igObjectRefMetaField *)temp_s2_2)->_refCounted = 0;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_00459380();
    ((igObjectRefMetaField *)temp_s2_3)->_refCounted = 0;
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4), -1);
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_002b9120();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 6));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_002c3440();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = FUN_002c7150();
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 8));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = FUN_002c3440();
    ((igRefMetaField *)temp_s2_7)->_construct = 1;
    temp_s2_8 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 9));
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = FUN_002c3440();
    ((igRefMetaField *)temp_s2_8)->_construct = 1;
    igMetaObject_NameFields(temp_s1, &DAT_004c6ec0[0], &DAT_004c6ef0[0], &DAT_004c6f20[0], temp_s0);
}
