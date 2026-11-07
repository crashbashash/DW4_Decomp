extern "C" {
int FUN_0018e2f0(void *, int *);
int FUN_002d3890(void *, int);
int FUN_0044ff40(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004d03c0[4];
extern int DAT_004d03f0[4];
extern int DAT_004d0420[4];
extern int DAT_004d0450[4];
extern int DAT_0058c3c8[4];
void igGuiSystemModel_InitFields(void);
}
void igGuiSystemModel_InitFields(void) {
    int temp_s2;
    int sp48[2];
    int sp40[2];
    void *temp_s1_4;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_a0_2;
    void *temp_a0;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c3c8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d03c0[0], 0xB);
    temp_a0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    sp48[0] = 0;
    sp48[1] = 0;
    FUN_0018e2f0(temp_a0, sp48);
    temp_a0_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    sp40[0] = 0;
    sp40[1] = 0;
    FUN_0018e2f0(temp_a0_2, sp40);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5), 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6));
    *(int *)((char *)(temp_s1) + 56) = FUN_0044ff40();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 7));
    *(int *)((char *)(temp_s1_2) + 56) = FUN_0044ff40();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 8));
    *(int *)((char *)(temp_s1_3) + 56) = FUN_0044ff40();
    temp_s1_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 9));
    *(int *)((char *)(temp_s1_4) + 56) = FUN_0044ff40();
    igMetaObject_NameFields(temp_s0, &DAT_004d03f0[0], &DAT_004d0420[0], &DAT_004d0450[0], temp_s2);
}
