/* 0x0014b5a0 — igVertexData_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
int igDataList_GetOrCreateMetaObject();
int FUN_002dc7a0();
int FUN_0030e9b0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
void FUN_0014b330(void);  /* code at 0x14b330, passed by address (was DAT_14b330; docs/engine/function-inventory.md) */
extern int DAT_004886c0[4];
extern int DAT_004886e0[4];
extern int DAT_00488700[4];
extern int DAT_00488720[4];
extern int DAT_00488738[4];
extern int DAT_0055fa58[4];
void igVertexData_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    void *temp_v0;
    int temp_s2;

    temp_s0 = (void *)DAT_0055fa58[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004886c0[0], 6);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igDataList_GetOrCreateMetaObject();
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    FUN_002dc7a0(temp_v0, &DAT_00488738[0]);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(FUN_0014b330);
    FUN_0030e9b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3), 1);
    igMetaObject_NameFields(temp_s0, &DAT_004886e0[0], &DAT_00488700[0], &DAT_00488720[0], temp_s2);
}
