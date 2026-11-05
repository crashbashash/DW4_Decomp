int FUN_001236b8();
int FUN_00124d60();
int printf();
int FUN_0020d340();
int FUN_0020e4a0();
extern int DAT_004965c0[4];
extern int DAT_004e55c0[4];
extern int DAT_004e55e0[4];
extern int DAT_004e5600[4];
extern int DAT_0056d670[4];
extern volatile int DAT_0056d678[4];
extern volatile int DAT_0056d680[4];
void FUN_0020e6a0(void) {
    int temp_v0;
    printf(&DAT_004e55c0[0]);
    for (;;) {
        do {
            FUN_0020d340(4);
        } while (DAT_004965c0[0] != 0);
        if (DAT_0056d678[0] != 0) {
            printf(&DAT_004e55e0[0], DAT_0056d678[0]);
            FUN_0020e4a0();
            FUN_001236b8();
        }
        DAT_0056d678[0] = DAT_0056d670[0];
        temp_v0 = DAT_0056d680[0] + 1;
        DAT_0056d680[0] = temp_v0;
        if (temp_v0 < 0x3C) {
            continue;
        }
        printf(&DAT_004e5600[0]);
        FUN_001236b8();
        FUN_00124d60(1);
    }
}
