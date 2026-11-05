/* 0x0013b5f0 — igAlphaFunctionAttr_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
int FUN_002dc7a0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00486c90[4];
extern int DAT_00486c98[4];
extern int DAT_00486ca0[4];
extern int DAT_00486ca8[4];
extern int DAT_00486cb0[4];
extern int DAT_0055f490[4];
int FUN_001496e0();

void igAlphaFunctionAttr_InitFields(void) {
    void *temp_s0;
    void *temp_v0;
    int temp_s2;

    temp_s0 = (void *)DAT_0055f490[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00486c90[0], 2);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    FUN_002dc7a0(temp_v0, &DAT_00486cb0[0]);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(&FUN_001496e0);
    igMetaObject_NameFields(temp_s0, &DAT_00486c98[0], &DAT_00486ca0[0], &DAT_00486ca8[0], temp_s2);
}
