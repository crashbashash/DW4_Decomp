/* 0x00132750 — igTextureCoordSourceAttr_InitFields. Retyped m2c draft, verified byte-identical to retail by tools/verify.py (wave5 shard 8). */
int FUN_002dc7a0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
void FUN_00140fd0(void);  /* code at 0x140fd0, passed by address (was DAT_140fd0; docs/engine/function-inventory.md) */
extern int DAT_00485c60[4];
extern int DAT_00485c70[4];
extern int DAT_00485c80[4];
extern int DAT_00485c90[4];
extern int DAT_00485ca0[4];
extern int DAT_0055ed68[4];
int FUN_001497a0();

void igTextureCoordSourceAttr_InitFields(void) {
    void *temp_v0_2;
    int temp_s0;
    int temp_s2;
    void *temp_v0;

    temp_s0 = DAT_0055ed68[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00485c60[0], 3);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    FUN_002dc7a0(temp_v0, &DAT_00485ca0[0]);
    *(int *)((char *)(temp_v0) + 52) = (int)(&FUN_001497a0);
    temp_v0_2 = igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2);
    *(int *)((char *)(temp_v0_2) + 48) = (int)(FUN_00140fd0);
    igMetaObject_NameFields(temp_s0, &DAT_00485c70[0], &DAT_00485c80[0], &DAT_00485c90[0], temp_s2);
}
