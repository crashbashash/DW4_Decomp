extern "C" {
int FUN_0019fae0(void);
int FUN_002e3810(void *, float);
int FUN_0034d2f0(void);
int FUN_0034d8f0(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c4950[4];
extern int DAT_004c4970[4];
extern int DAT_004c4990[4];
extern int DAT_004c49b0[4];
extern int DAT_00588650[4];
void beNumberCtrlInfoRam_InitFields(void);
}
void beNumberCtrlInfoRam_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_s0;

    temp_s0 = (void *)DAT_00588650[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c4950[0], 6);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 56) = FUN_0019fae0();
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1), 0.09375f);
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    *(int *)((char *)(temp_s1_2) + 56) = FUN_0034d8f0();
    *(char *)((char *)(temp_s1_2) + 52) = 1;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5));
    *(int *)((char *)(temp_s1_3) + 56) = FUN_0034d2f0();
    igMetaObject_NameFields(temp_s0, &DAT_004c4970[0], &DAT_004c4990[0], &DAT_004c49b0[0], temp_s2);
}
