#include "dw4/reflected.h"
extern "C" {
int FUN_0014b980(void);
int FUN_002c95d0(void);
int FUN_002c9780(void);
int igIntList_GetOrCreateMetaObject(void);
int FUN_00340490(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c30b0[4];
extern int DAT_004c3120[4];
extern int DAT_004c3190[4];
extern int DAT_004c3200[4];
extern int DAT_00587aa8[4];
void beWaterPlainInfoRam_InitFields(void);
}
void beWaterPlainInfoRam_InitFields(void) {
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s1;
    int temp_s0;

    temp_s1 = (void *)DAT_00587aa8[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004c30b0[0], 0x1B);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xA));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_0014b980();
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xB));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_002c9780();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xC));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x15));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_002c95d0();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x1A));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_00340490();
    igMetaObject_NameFields(temp_s1, &DAT_004c3120[0], &DAT_004c3190[0], &DAT_004c3200[0], temp_s0);
}
