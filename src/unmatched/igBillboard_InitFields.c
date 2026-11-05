int FUN_001356f0();
int FUN_0018e470();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048cbc0[4];
extern int DAT_0048cbd0[4];
extern int DAT_0048cbe0[4];
extern int DAT_0048cbf0[4];
extern int DAT_00561f68[4];
void igBillboard_InitFields(void) {
    void *temp_s0;
    void *temp_a0;
    void *temp_a0_2;
    void *temp_s1;
    int temp_s2;
    float spB[4];
    float spA[4];

    temp_s0 = (void *)DAT_00561f68[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048cbc0[0], 4);
    temp_a0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    spA[0] = 0;
    spA[2] = 1.0f;
    spA[1] = 0;
    FUN_0018e470(temp_a0, spA);
    temp_a0_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    spB[0] = 0;
    spB[1] = 0;
    spB[2] = 0;
    FUN_0018e470(temp_a0_2, spB);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    *(int *)((char *)(temp_s1) + 56) = FUN_001356f0();
    *(char *)((char *)(temp_s1) + 38) = 0;
    igMetaObject_NameFields(temp_s0, &DAT_0048cbd0[0], &DAT_0048cbe0[0], &DAT_0048cbf0[0], temp_s2);
}

