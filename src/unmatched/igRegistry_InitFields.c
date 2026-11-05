/* 0x002bb2a0 — igRegistry_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
int FUN_002b9390();
int FUN_002bb390();
int FUN_002c4ce0();
int FUN_002d3890();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004bf890[4];
extern int DAT_004bf8b0[4];
extern int DAT_004bf8d0[4];
extern int DAT_004bf8f0[4];
extern int DAT_00585a08[4];
void igRegistry_InitFields(void) {
    int temp_s0;
    void *temp_s1;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;

    temp_s1 = (void *)DAT_00585a08[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004bf890[0], 5);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_002bb390();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_002c4ce0();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_002b9390();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4), 1);
    igMetaObject_NameFields(temp_s1, &DAT_004bf8b0[0], &DAT_004bf8d0[0], &DAT_004bf8f0[0], temp_s0);
}
