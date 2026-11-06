#include "dw4/reflected.h"
int FUN_001a4d90();
int FUN_001a7100();
int igIntMetaField_GetDefaultDescriptor();
int igIntList_GetOrCreateMetaObject();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048d470[4];
extern int DAT_0048d490[4];
extern int DAT_0048d4b0[4];
extern int DAT_0048d4d0[4];
extern int DAT_00562338[4];
void igAnimationBinding_InitFields(void) {
    int temp_s2;
    void *temp_s1_4;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00562338[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048d470[0], 5);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_001a7100();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igMemoryRefMetaField *)temp_s1_2)->_memType = igIntMetaField_GetDefaultDescriptor();
    ((igRefMetaField *)temp_s1_2)->_destruct = 1;
    ((igMemoryRefMetaField *)temp_s1_2)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)temp_s1_2)->_releaseOnReset = 1;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = igIntList_GetOrCreateMetaObject();
    temp_s1_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    ((igObjectRefMetaField *)temp_s1_4)->_metaObject = FUN_001a4d90();
    igMetaObject_NameFields(temp_s0, &DAT_0048d490[0], &DAT_0048d4b0[0], &DAT_0048d4d0[0], temp_s2);
}
