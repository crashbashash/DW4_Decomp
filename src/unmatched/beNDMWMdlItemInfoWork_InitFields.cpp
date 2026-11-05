/* 0x003c1670 — beNDMWMdlItemInfoWork_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess.
 * C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
#include "dw4/reflected.h"
extern "C" {
int FUN_002ea4b0(void *, int);
int FUN_003c92c0(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004cab80[4];
extern int DAT_004caba0[4];
extern int DAT_004cabc0[4];
extern int DAT_004cabe0[4];
extern int DAT_0058b4c0[4];
void beNDMWMdlItemInfoWork_InitFields(void);
}
void beNDMWMdlItemInfoWork_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058b4c0[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cab80[0], 8);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_003c92c0();
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4), -1);
    igMetaObject_NameFields(temp_s0, &DAT_004caba0[0], &DAT_004cabc0[0], &DAT_004cabe0[0], temp_s2);
}
