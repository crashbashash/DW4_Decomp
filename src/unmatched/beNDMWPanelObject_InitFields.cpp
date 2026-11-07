#include "dw4/reflected.h"
extern "C" {
int FUN_002b9120(void);
int igIntList_GetOrCreateMetaObject(void);
int FUN_002ea4b0(void *, int);
int FUN_00357910(void);
int FUN_00364090(void);
int FUN_0036a8d0(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004ca630[4];
extern int DAT_004ca670[4];
extern int DAT_004ca6b0[4];
extern int DAT_004ca6f0[4];
extern int DAT_0058b2c8[4];
void beNDMWPanelObject_InitFields(void);
}
void beNDMWPanelObject_InitFields(void) {
    int temp_s2;
    void *temp_s1_5;
    void *temp_s1_4;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058b2c8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004ca630[0], 0x10);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0036a8d0();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_00357910();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6), 2);
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 7));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_00364090();
    temp_s1_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xC));
    ((igObjectRefMetaField *)temp_s1_4)->_metaObject = FUN_002b9120();
    temp_s1_5 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xD));
    ((igObjectRefMetaField *)temp_s1_5)->_metaObject = igIntList_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s0, &DAT_004ca670[0], &DAT_004ca6b0[0], &DAT_004ca6f0[0], temp_s2);
}
