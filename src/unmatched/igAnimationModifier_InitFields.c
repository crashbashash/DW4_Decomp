/* 0x001a76a0 — igAnimationModifier_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
int FUN_00196190();
int FUN_002dc7a0();
int FUN_002ea4b0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
void FUN_001a7440(void);  /* code at 0x1a7440, passed by address (was DAT_1a7440; docs/engine/function-inventory.md) */
extern int DAT_0048d1b8[4];
extern int DAT_0048d1c8[4];
extern int DAT_0048d1d8[4];
extern int DAT_0048d1e8[4];
extern int DAT_0048d1f8[4];
extern int DAT_00562200[4];
void igAnimationModifier_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    void *temp_v0;
    int temp_s2;

    temp_s0 = (void *)DAT_00562200[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048d1b8[0], 3);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2), -1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00196190();
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    FUN_002dc7a0(temp_v0, &DAT_0048d1f8[0]);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(FUN_001a7440);
    igMetaObject_NameFields(temp_s0, &DAT_0048d1c8[0], &DAT_0048d1d8[0], &DAT_0048d1e8[0], temp_s2);
}
