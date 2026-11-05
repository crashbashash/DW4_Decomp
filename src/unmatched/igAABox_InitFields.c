int FUN_0018e470();
int igMetaObject_CreateFields();
int igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048ae58[4];
extern int DAT_0048ae60[4];
extern int DAT_0048ae68[4];
extern int DAT_0048ae70[4];
extern int DAT_005610e0[4];
extern float GPR_0055490c;
extern float GPR_00554910;

void igAABox_InitFields(void) {
    float vb[4];
    float va[4];
    int temp_a0;
    int temp_a0_2;
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_005610e0[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048ae58[0], 2);
    temp_a0 = igMetaObject_GetFieldAt(temp_s0, temp_s1);
    va[0] = GPR_0055490c;
    va[1] = GPR_0055490c;
    va[2] = GPR_0055490c;
    FUN_0018e470(temp_a0, va);
    temp_a0_2 = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1);
    vb[0] = GPR_00554910;
    vb[1] = GPR_00554910;
    vb[2] = GPR_00554910;
    FUN_0018e470(temp_a0_2, vb);
    igMetaObject_NameFields(temp_s0, &DAT_0048ae60[0], &DAT_0048ae68[0], &DAT_0048ae70[0], temp_s1);
}
