#include "dw4/reflected.h"
extern "C" {
int FUN_00195e70(void);
int FUN_00196930(void);
int FUN_0019f930(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c78d0[4];
extern int DAT_004c78f0[4];
extern int DAT_004c7910[4];
extern int DAT_004c7930[4];
extern int DAT_00589c08[4];
void beCameraBoxData_InitFields(void);
}
void beCameraBoxData_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s1;

    temp_s1 = (void *)DAT_00589c08[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004c78d0[0], 5);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_00196930();
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_0019f930();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_00195e70();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_00195e70();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_00195e70();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    igMetaObject_NameFields(temp_s1, &DAT_004c78f0[0], &DAT_004c7910[0], &DAT_004c7930[0], temp_s0);
}
