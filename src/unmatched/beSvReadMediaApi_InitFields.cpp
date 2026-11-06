/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
#include "dw4/reflected.h"
extern "C" {
int igObjectList_GetOrCreateMetaObject(void);
int FUN_002ea4b0(void *, int);
int FUN_0034a210(void);
int FUN_0034aeb0(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c40b0[4];
extern int DAT_004c40d0[4];
extern int DAT_004c40f0[4];
extern int DAT_004c4110[4];
extern int DAT_00588238[4];
void beSvReadMediaApi_InitFields(void);
}
void beSvReadMediaApi_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_s1_4;
    void *temp_s0;

    temp_s0 = (void *)DAT_00588238[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c40b0[0], 5);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0034a210();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_0034aeb0();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2), 0x10);
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_0034aeb0();
    temp_s1_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    ((igObjectRefMetaField *)temp_s1_4)->_metaObject = igObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_4)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c40d0[0], &DAT_004c40f0[0], &DAT_004c4110[0], temp_s2);
}
