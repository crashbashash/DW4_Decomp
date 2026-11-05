int FUN_0018e470();
int igMetaObject_CreateFields();
int igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048adc8[4];
extern int DAT_0048add8[4];
extern int DAT_0048ade8[4];
extern int DAT_0048adf8[4];
extern int DAT_00560fc0[4];
void igRay_InitFields(void) {
    int sp30[4];
    int sp40[4];
    int temp_a0;
    int temp_a0_2;
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_00560fc0[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048adc8[0], 3);
    temp_a0 = igMetaObject_GetFieldAt(temp_s0, temp_s1);
    sp40[0] = 0;
    sp40[1] = 0;
    sp40[2] = 0;
    FUN_0018e470(temp_a0, &sp40[0]);
    temp_a0_2 = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1);
    sp30[0] = 0;
    sp30[1] = 0x3F800000;
    sp30[2] = 0;
    FUN_0018e470(temp_a0_2, &sp30[0]);
    igMetaObject_NameFields(temp_s0, &DAT_0048add8[0], &DAT_0048ade8[0], &DAT_0048adf8[0], temp_s1);
}
