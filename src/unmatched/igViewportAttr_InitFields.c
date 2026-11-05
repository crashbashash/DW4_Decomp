int FUN_0014bc80();
int FUN_002e3810(void *, float);
int FUN_002ea4b0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00485940[4];
extern int DAT_00485960[4];
extern int DAT_00485980[4];
extern int DAT_004859a0[4];
extern int DAT_0055ebd8[4];
void igViewportAttr_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_0055ebd8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00485940[0], 7);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2), 0x27F);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3), 0x1BF);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    *(int *)((char *)(temp_s1) + 56) = FUN_0014bc80();
    *(char *)((char *)(temp_s1) + 38) = 0;
    *(char *)((char *)(temp_s1) + 40) = 1;
    *(char *)((char *)(temp_s1) + 39) = 1;
    *(char *)((char *)(temp_s1) + 44) = 3;
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6), 1.0f);
    igMetaObject_NameFields(temp_s0, &DAT_00485960[0], &DAT_00485980[0], &DAT_004859a0[0], temp_s2);
}
