/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
#include "dw4/reflected.h"
extern "C" {
int FUN_0019e6c0(void);
int FUN_002d3890(void *, int);
int FUN_0035dc10(void);
int FUN_0035ded0(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c65f0[4];
extern int DAT_004c6610[4];
extern int DAT_004c6630[4];
extern int DAT_004c6650[4];
extern int DAT_00589350[4];
void beHitLandModel_InitFields(void);
}
void beHitLandModel_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_s0;

    temp_s0 = (void *)DAT_00589350[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c65f0[0], 5);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0035ded0();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_0035dc10();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_0019e6c0();
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3), 1);
    igMetaObject_NameFields(temp_s0, &DAT_004c6610[0], &DAT_004c6630[0], &DAT_004c6650[0], temp_s2);
}
