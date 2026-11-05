#include "dw4/reflected.h"
int FUN_002be610();
int FUN_002ea4b0();
int FUN_00303460();
int Memory_GetAllocatorBySelector();
int ObjectPointerList_FindIndex();
int igMetaField_Configure();
int igMetaObject_CreateFields();
int igMetaObject_FinalizeAndReplaceField();
int igMetaObject_FindFieldByName();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
void *igObjectRefMetaField_Create();
int igObject_Destroy();
int igStringMetaField_SetDefaultText();
extern int DAT_004bfb30[4];
extern int DAT_004bfb50[4];
extern int DAT_004bfb70[4];
extern int DAT_004bfb90[4];
extern int DAT_004f6518[4];
extern int DAT_004f6520[4];
extern void * DAT_00585b70[4];
extern int DAT_00585b98[4];
extern int DAT_00587040[4];
extern int DAT_00587198[4];
void igObjectDirEntry_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    void *temp_v0;
    void *temp_v0_2;
    int temp_s1_2;
    int temp_s2;
    int temp_s3;
    int var_a1;

    temp_s0 = (void *)(DAT_00585b70[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004bfb30[0], 6);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002be610();
    ((igMetaField *)temp_s1)->_persistent = 0;
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    igStringMetaField_SetDefaultText(temp_v0, &DAT_004f6518[0]);
    ((igStringMetaField *)temp_v0)->_destruct = 1;
    ((igMetaField *)temp_v0)->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3))->_persistent = 0;
    temp_s1_2 = ((igMetaObject *)temp_s0)->_metaFields;
    temp_s3 = ObjectPointerList_FindIndex(temp_s1_2, igMetaObject_FindFieldByName(temp_s0, &DAT_004f6520[0]));
    temp_v0_2 = (void *)(igObjectRefMetaField_Create(Memory_GetAllocatorBySelector(DAT_00587040[0])));
    igMetaField_Configure(temp_v0_2, &DAT_004f6520[0], &DAT_00585b98[0], 0x18, temp_s0);
    ((igObjectRefMetaField *)temp_v0_2)->_metaObject = (int)((int) DAT_00587198[0]);
    FUN_00303460(temp_v0_2, 0);
    ((igMetaField *)temp_v0_2)->_persistent = 0;
    ((igMetaField *)temp_v0_2)->_externalEnumStorage = (int)(&DAT_00585b98[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s0, temp_s3, temp_v0_2);
    --((igObject *)temp_v0_2)->_refCount;
    var_a1 = temp_s2 + 4;
    if (((unsigned long long)(long long)((igObject *)temp_v0_2)->_refCount & 0x7fffffULL) == 0) {
        igObject_Destroy(temp_v0_2, var_a1);
        var_a1 = temp_s2 + 4;
    }
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, var_a1), -1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5), -1);
    igMetaObject_NameFields(temp_s0, &DAT_004bfb50[0], &DAT_004bfb70[0], &DAT_004bfb90[0], temp_s2);
}
