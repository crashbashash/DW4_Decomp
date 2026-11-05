/* 0x001a1a30 — igEnbayaTransformSource_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
int FUN_001a2210();
int FUN_002ea4b0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048c2d0[4];
extern int DAT_0048c2d8[4];
extern int DAT_0048c2e0[4];
extern int DAT_0048c2e8[4];
extern int DAT_00561b48[4];
void igEnbayaTransformSource_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_00561b48[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048c2d0[0], 2);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2), -1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_001a2210();
    igMetaObject_NameFields(temp_s0, &DAT_0048c2d8[0], &DAT_0048c2e0[0], &DAT_0048c2e8[0], temp_s2);
}
