#include "dw4/reflected.h"
int FUN_001888e0();
int igUnsignedIntMetaField_GetDefaultDescriptor();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00486a10[4];
extern int DAT_00486a20[4];
extern int DAT_00486a30[4];
extern int DAT_00486a40[4];
extern int DAT_0055f360[4];
void igBlendMatrixPaletteAttr_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    void *temp_s1_2;
    int temp_s2;

    temp_s0 = (void *)DAT_0055f360[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00486a10[0], 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igMemoryRefMetaField *)temp_s1)->_memType = FUN_001888e0();
    ((igRefMetaField *)temp_s1)->_destruct = 1;
    ((igMemoryRefMetaField *)temp_s1)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)temp_s1)->_releaseOnReset = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igMemoryRefMetaField *)temp_s1_2)->_memType = igUnsignedIntMetaField_GetDefaultDescriptor();
    ((igRefMetaField *)temp_s1_2)->_destruct = 1;
    ((igMemoryRefMetaField *)temp_s1_2)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)temp_s1_2)->_releaseOnReset = 1;
    igMetaObject_NameFields(temp_s0, &DAT_00486a20[0], &DAT_00486a30[0], &DAT_00486a40[0], temp_s2);
}
