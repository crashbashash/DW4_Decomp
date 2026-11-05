/* 0x002399b0 — igCollisionInfo_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
int FUN_0023a080();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00498388[4];
extern int DAT_00498390[4];
extern int DAT_00498398[4];
extern int DAT_004983a0[4];
extern int DAT_0056dcc8[4];
void igCollisionInfo_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_0056dcc8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00498388[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0023a080();
    igMetaObject_NameFields(temp_s0, &DAT_00498390[0], &DAT_00498398[0], &DAT_004983a0[0], temp_s2);
}
