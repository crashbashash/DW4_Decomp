/* 0x002c14d0 — igMediaFile_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
int igUnsignedCharMetaField_GetDefaultDescriptor();
int FUN_002c16e0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004c03e0[4];
extern int DAT_004c0410[4];
extern int DAT_004c0440[4];
extern int DAT_004c0470[4];
extern int DAT_00585fc8[4];
void igMediaFile_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    void *temp_s1_2;
    int temp_s2;

    temp_s0 = (void *)DAT_00585fc8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c03e0[0], 9);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 7));
    ((igMemoryRefMetaField *)temp_s1)->_memType = igUnsignedCharMetaField_GetDefaultDescriptor();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 8));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_002c16e0();
    igMetaObject_NameFields(temp_s0, &DAT_004c0410[0], &DAT_004c0440[0], &DAT_004c0470[0], temp_s2);
}
