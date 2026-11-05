/* 0x00227b90 — igIterateDerived_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
int FUN_002be610();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00497db0[4];
extern int DAT_00497db8[4];
extern int DAT_00497dc0[4];
extern int DAT_00497dc8[4];
extern int DAT_0056d980[4];
void igIterateDerived_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_0056d980[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00497db0[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002be610();
    igMetaObject_NameFields(temp_s0, &DAT_00497db8[0], &DAT_00497dc0[0], &DAT_00497dc8[0], temp_s2);
}
