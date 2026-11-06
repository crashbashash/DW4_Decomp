int FUN_003065f0();
int FUN_00306e50();
extern int DAT_0048dae0[4];
extern int DAT_004e4830[4];
extern int DAT_004e4850[4];
extern void * DAT_00586dc8[4];
extern int GPR_00554b9c;

int FUN_001d81e0(void) {
    int temp_s0;

    if (DAT_0048dae0[0] == -1) {
        temp_s0 = *(int *)((char *)DAT_00586dc8[0] + 56);
        FUN_003065f0(temp_s0, 7, &DAT_004e4830[0], &DAT_0048dae0[0], 0x100, 1);
        FUN_00306e50(temp_s0, 7, &DAT_004e4850[0], &GPR_00554b9c, 0, 1);
    }
    return DAT_0048dae0[0];
}
