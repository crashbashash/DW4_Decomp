/* 0x002c2c40 — __internalNonRefCountedObjectList_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
int igObjectRefMetaField_GetDefaultDescriptor();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004c05c0[4];
extern int DAT_004c05c8[4];
extern int DAT_004c05d0[4];
extern int DAT_004c05d8[4];
extern int DAT_005860e0[4];
void __internalNonRefCountedObjectList_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_005860e0[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c05c0[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igMemoryRefMetaField *)temp_s1)->_memType = igObjectRefMetaField_GetDefaultDescriptor();
    ((igMemoryRefMetaField *)temp_s1)->_memSize = 0x40;
    ((igRefMetaField *)temp_s1)->_construct = 1;
    ((igRefMetaField *)temp_s1)->_destruct = 1;
    ((igMemoryRefMetaField *)temp_s1)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)temp_s1)->_releaseOnReset = 1;
    ((igMemoryRefMetaField *)temp_s1)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004c05c8[0], &DAT_004c05d0[0], &DAT_004c05d8[0], temp_s2);
}
