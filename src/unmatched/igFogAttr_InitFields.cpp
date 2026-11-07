extern "C" {
int FUN_0018e670(void *, float *);
int FUN_002dc7a0(void *, int *);
int FUN_002e3810(void *, float);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
int FUN_00149560(void);
extern int DAT_00486680[4];
extern int DAT_004866a0[4];
extern int DAT_004866c0[4];
extern int DAT_004866e0[4];
extern int DAT_004866f8[4];
extern int DAT_0055f1d8[4];
void igFogAttr_InitFields(void);
}
void igFogAttr_InitFields(void) {
    int temp_s2;
    float sp[4];
    void *temp_v0;
    void *temp_a0;
    void *temp_s0;

    temp_s0 = (void *)DAT_0055f1d8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00486680[0], 5);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    FUN_002dc7a0(temp_v0, &DAT_004866f8[0]);
    *(int *)((char *)(temp_v0) + 52) = (int)(&FUN_00149560);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2), 1000.0f);
    temp_a0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    sp[0] = 0.0f;
    sp[3] = 1.0f;
    sp[1] = 0.0f;
    sp[2] = 0.0f;
    FUN_0018e670(temp_a0, sp);
    igMetaObject_NameFields(temp_s0, &DAT_004866a0[0], &DAT_004866c0[0], &DAT_004866e0[0], temp_s2);
}
