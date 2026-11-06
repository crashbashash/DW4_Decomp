#include "dw4/reflected.h"
int igUnsignedCharMetaField_GetDefaultDescriptor();
int FUN_002c4ce0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00489150[4];
extern int DAT_00489180[4];
extern int DAT_004891b0[4];
extern int DAT_004891e0[4];
extern int DAT_0055ff10[4];
void igTgaLoader_InitFields(void) {
    int temp_s2;
    void *temp_s1_4;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0055ff10[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00489150[0], 0xA);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002c4ce0();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igMemoryRefMetaField *)temp_s1_2)->_memType = igUnsignedCharMetaField_GetDefaultDescriptor();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igMemoryRefMetaField *)temp_s1_3)->_memType = igUnsignedCharMetaField_GetDefaultDescriptor();
    temp_s1_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    ((igMemoryRefMetaField *)temp_s1_4)->_memType = igUnsignedCharMetaField_GetDefaultDescriptor();
    igMetaObject_NameFields(temp_s0, &DAT_00489180[0], &DAT_004891b0[0], &DAT_004891e0[0], temp_s2);
}
