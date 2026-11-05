#include "dw4/reflected.h"
int FUN_002eb010();
int Memory_GetAllocatorBySelector();
int StringChunk_ReleaseHeader();
int StringPool_Construct();
void *StringPool_Intern();
int igMetaField_SetFieldName();
int igMetaObject_FinalizeAndAppendField();
int igObject_Destroy();
igUnsignedIntMetaField *igUnsignedIntMetaField_Create();
extern int DAT_004faf40[4];
extern int DAT_004faf50[4];
extern int DAT_00586f20[4];
extern int DAT_00587040[4];
extern int DAT_00587198[4];
extern int DAT_005871a0[4];
extern int DAT_005871a8[4];
void igObject_InitFields(void) {
    void *sp2C;
    void *sp28;
    int *temp_a1;
    int *temp_a1_2;
    int temp_v0_2;
    int temp_v0_4;
    int var_v0_2;
    int var_v0_4;
    igUnsignedIntMetaField *temp_v0;
    igUnsignedIntMetaField *temp_v0_3;
    void *var_v0;
    void *var_v0_3;

    temp_v0 = igUnsignedIntMetaField_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    temp_v0->_offset = 4;
    temp_v0->_externalEnumStorage = (int)(&DAT_005871a0[0]);
    if (&DAT_004faf40[0] == 0) {
        var_v0 = (void *)(0);
    } else {
        if (DAT_00586f20[0] == 0) {
            var_v0_2 = FUN_002eb010(0x10);
            if (var_v0_2 != 0) {
                var_v0_2 = StringPool_Construct(var_v0_2);
            }
            DAT_00586f20[0] = var_v0_2;
        }
        var_v0 = (void *)(StringPool_Intern(DAT_00586f20[0], &DAT_004faf40[0]));
    }
    sp2C = (void *)(var_v0);
    igMetaField_SetFieldName(temp_v0, &sp2C);
    if (sp2C != 0) {
        temp_a1 = (int *)((char *)sp2C - 8);
        temp_v0_2 = *(int *)((char *)(sp2C) - 4) - 1;
        *(int *)((char *)(sp2C) - 4) = temp_v0_2;
        if (temp_v0_2 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
    temp_v0->_persistent = 0;
    temp_v0->_resetMethod = 3;
    igMetaObject_FinalizeAndAppendField(DAT_00587198[0], temp_v0);
    temp_v0->_refCount = (int)temp_v0->_refCount - 1;
    if (((unsigned long long)((long long)(int)temp_v0->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0);
    }
    temp_v0_3 = igUnsignedIntMetaField_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    temp_v0_3->_offset = 4;
    temp_v0_3->_externalEnumStorage = (int)(&DAT_005871a8[0]);
    if (&DAT_004faf50[0] == 0) {
        var_v0_3 = (void *)(0);
    } else {
        if (DAT_00586f20[0] == 0) {
            var_v0_4 = FUN_002eb010(0x10);
            if (var_v0_4 != 0) {
                var_v0_4 = StringPool_Construct(var_v0_4);
            }
            DAT_00586f20[0] = var_v0_4;
        }
        var_v0_3 = (void *)(StringPool_Intern(DAT_00586f20[0], &DAT_004faf50[0]));
    }
    sp28 = (void *)(var_v0_3);
    igMetaField_SetFieldName(temp_v0_3, &sp28);
    if (sp28 != 0) {
        temp_a1_2 = (int *)((char *)sp28 - 8);
        temp_v0_4 = *(int *)((char *)(sp28) - 4) - 1;
        *(int *)((char *)(sp28) - 4) = temp_v0_4;
        if (temp_v0_4 == 0) {
            StringChunk_ReleaseHeader(*temp_a1_2, temp_a1_2);
        }
    }
    temp_v0_3->_persistent = 0;
    temp_v0_3->_resetMethod = 3;
    igMetaObject_FinalizeAndAppendField(DAT_00587198[0], temp_v0_3);
    temp_v0_3->_refCount = (int)temp_v0_3->_refCount - 1;
    if (((unsigned long long)((long long)(int)temp_v0_3->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0_3);
    }
}
