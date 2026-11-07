extern "C" {
int FUN_0018e2f0(int, int *);
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c4740[4];
extern int DAT_004c47a0[4];
extern int DAT_004c4800[4];
extern int DAT_004c4860[4];
extern int DAT_00588550[4];
void bePadData_InitFields(void);
}
void bePadData_InitFields(void) {
    int sp38[2];
    int sp30[2];
    int temp_a0;
    int temp_a0_2;
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00588550[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c4740[0], 0x16);
    temp_a0 = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1);
    sp38[0] = 0;
    sp38[1] = 0;
    FUN_0018e2f0(temp_a0, sp38);
    temp_a0_2 = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2);
    sp30[0] = 0;
    sp30[1] = 0;
    FUN_0018e2f0(temp_a0_2, sp30);
    igMetaObject_NameFields(temp_s0, &DAT_004c47a0[0], &DAT_004c4800[0], &DAT_004c4860[0], temp_s1);
}
