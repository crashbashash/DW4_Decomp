/* 0x00451d40 — igDefaultAspectElement_InitFields, m2c draft (hybrid+po mode), does not match yet.
 * Iterate here; a match is copied to src/igDefaultAspectElement_InitFields.c only after verify.py agrees. */
int FUN_00196190();
int FUN_002dc7a0();
int FUN_004505b0();
int FUN_004521d0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
void FUN_00451ac0(void);  /* code at 0x451ac0, passed by address (was DAT_451ac0; docs/engine/function-inventory.md) */
extern int DAT_004d07c0[4];
extern int DAT_004d07e0[4];
extern int DAT_004d0800[4];
extern int DAT_004d0820[4];
extern int DAT_004d0838[4];
extern int DAT_0058c5b0[4];
void igDefaultAspectElement_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_v0;
    int temp_s2;

    temp_s0 = (void *)DAT_0058c5b0[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d07c0[0], 6);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 56) = FUN_004505b0();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    *(int *)((char *)(temp_s1_2) + 56) = FUN_004521d0();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    *(int *)((char *)(temp_s1_3) + 56) = FUN_00196190();
    *(unsigned char *)((char *)(temp_s1_3) + 52) = 1;
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    FUN_002dc7a0(temp_v0, &DAT_004d0838[0]);
    *(int *)((char *)(temp_v0) + 52) = (int)(FUN_00451ac0);
    igMetaObject_NameFields(temp_s0, &DAT_004d07e0[0], &DAT_004d0800[0], &DAT_004d0820[0], temp_s2);
}
