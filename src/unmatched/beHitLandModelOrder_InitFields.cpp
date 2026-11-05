/* 0x0035e150 — beHitLandModelOrder_InitFields. Retyped m2c draft, verified byte-identical to retail by tools/verify.py (wave5 shard 8).
 * C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
extern "C" {
int FUN_001880b0(void);
int FUN_0018e470(void *, int *);
int FUN_0035e270(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
int igStringMetaField_SetDefaultText(void *, int *);
extern int DAT_004c66a0[4];
extern int DAT_004c66d0[4];
extern int DAT_004c6700[4];
extern int DAT_004c6730[4];
extern int DAT_00502a98[4];
extern int DAT_00589390[4];
void beHitLandModelOrder_InitFields(void);
}
void beHitLandModelOrder_InitFields(void) {
    void *temp_a0;
    void *temp_a0_2;
    void *temp_s1;
    int temp_s2;
    void *temp_s1_2;
    void *temp_s0;
    int sp50[3];
    int sp40[3];

    temp_s0 = (void *)DAT_00589390[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c66a0[0], 9);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s2), &DAT_00502a98[0]);
    temp_a0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    sp50[0] = 0;
    sp50[1] = 0;
    sp50[2] = 0;
    FUN_0018e470(temp_a0, sp50);
    temp_a0_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    sp40[0] = 0;
    sp40[1] = 0;
    sp40[2] = 0;
    FUN_0018e470(temp_a0_2, sp40);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6));
    *(int *)((char *)(temp_s1) + 56) = FUN_001880b0();
    *(char *)((char *)(temp_s1) + 52) = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 8));
    *(int *)((char *)(temp_s1_2) + 56) = FUN_0035e270();
    *(char *)((char *)(temp_s1_2) + 52) = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c66d0[0], &DAT_004c6700[0], &DAT_004c6730[0], temp_s2);
}
