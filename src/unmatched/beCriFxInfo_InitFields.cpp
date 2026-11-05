/* 0x00366ec0 — beCriFxInfo_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess.
 * C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
#include "dw4/reflected.h"
extern "C" {
int FUN_002ea4b0(void *, int);
int igStringMetaField_SetDefaultText(void *, int);
int FUN_00366fa0(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c74b0[4];
extern int DAT_004c74c0[4];
extern int DAT_004c74d0[4];
extern int DAT_004c74e0[4];
extern int DAT_005899f8[4];
void beCriFxInfo_InitFields(void);
}
void beCriFxInfo_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_005899f8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c74b0[0], 4);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s2), 0);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1), -1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2), -1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00366fa0();
    igMetaObject_NameFields(temp_s0, &DAT_004c74c0[0], &DAT_004c74d0[0], &DAT_004c74e0[0], temp_s2);
}
