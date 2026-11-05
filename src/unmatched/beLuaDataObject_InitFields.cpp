/* 0x0035b6a0 — beLuaDataObject_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess.
 * C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
#include "dw4/reflected.h"
extern "C" {
int FUN_002cc2c0(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c62b8[4];
extern int DAT_004c62c0[4];
extern int DAT_004c62c8[4];
extern int DAT_004c62d0[4];
extern int DAT_005891f0[4];
void beLuaDataObject_InitFields(void);
}
void beLuaDataObject_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_005891f0[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c62b8[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igMemoryRefMetaField *)temp_s1)->_memType = FUN_002cc2c0();
    igMetaObject_NameFields(temp_s0, &DAT_004c62c0[0], &DAT_004c62c8[0], &DAT_004c62d0[0], temp_s2);
}
