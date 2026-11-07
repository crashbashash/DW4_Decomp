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

void igAABox_InitFields(void) {
    float va[4];
    float vb[4];
    int temp_a0;
    int temp_a0_2;
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_005610e0[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048ae58[0], 2);
    temp_a0 = igMetaObject_GetFieldAt(temp_s0, temp_s1);
    va[0] = 3.402823466e+38f;
    va[1] = 3.402823466e+38f;
    va[2] = 3.402823466e+38f;
    FUN_0018e470(temp_a0, va);
    temp_a0_2 = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1);
    vb[0] = -3.402823466e+38f;
    vb[1] = -3.402823466e+38f;
    vb[2] = -3.402823466e+38f;
    FUN_0018e470(temp_a0_2, vb);
    igMetaObject_NameFields(temp_s0, &DAT_0048ae60[0], &DAT_0048ae68[0], &DAT_0048ae70[0], temp_s1);
}
