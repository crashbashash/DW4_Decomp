/* 0x002bcb20 - igPluginRepository_InitFields. the pointer store after GetFieldAt needs the call result in a local. Verified byte-identical by tools/verify.py. */
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
void FUN_002bc8d0(void);  /* code at 0x2bc8d0, passed by address (was DAT_2bc8d0; docs/engine/function-inventory.md) */
extern int DAT_004bfa58[4];
extern int DAT_004bfa60[4];
extern int DAT_004bfa68[4];
extern int DAT_004bfa70[4];
extern int DAT_00585af0[4];
void igPluginRepository_InitFields(void) {
    void *temp_s0; int temp_s1; void *f;
    temp_s0 = (void *)DAT_00585af0[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004bfa58[0], 2);
    f = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1);
    *(int *)((char *)f + 52) = (int)(FUN_002bc8d0);
    igMetaObject_NameFields(temp_s0, &DAT_004bfa60[0], &DAT_004bfa68[0], &DAT_004bfa70[0], temp_s1);
}
