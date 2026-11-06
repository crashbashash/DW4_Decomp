extern char DAT_004fb3a8[];
int FUN_002d81f0();
int igObject_Destroy();
int FUN_003087a0();
extern int DAT_004e4870[4];
extern int DAT_00586dd0[4];
void FUN_001d8b90(void) {
    void *sp1C;

    FUN_003087a0(&sp1C, DAT_00586dd0[0], DAT_004fb3a8);
    FUN_002d81f0(sp1C, &DAT_004e4870[0]);
    if (sp1C != 0) {
        *(int *)((char *)sp1C + 4) = (int) (*(int *)((char *)sp1C + 4) - 1);
        if (((unsigned long long) ((long long) *(int *)((char *)sp1C + 4) << 0x29) >> 0x29) == 0) {
            igObject_Destroy(sp1C);
        }
    }
}
