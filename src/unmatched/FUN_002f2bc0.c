extern char DAT_004c2170[];
int FUN_0012aba0();
int igStrCmp();
extern int DAT_004fa3b0[4];
extern int DAT_004fa3c8[4];
int FUN_002f2bc0(int arg0, char *arg1) {
    int i;
    char *s = arg1;
    if (s != 0 && *s != 0) {
        if (FUN_0012aba0(s, &DAT_004fa3b0[0], 0x13) == 0) {
            s += 0x13;
        } else if (FUN_0012aba0(s, &DAT_004fa3c8[0], 0xD) == 0) {
            s += 0xD;
        }
        for (i = 0; i < 0x2E; i++) {
            if (igStrCmp(arg0 + i * 0x90 + 0x18, s) == 0) return i;
        }
        for (i = 0; i < 0x2E; i++) {
            if (igStrCmp(*(int *)(DAT_004c2170 + i * 4), s) == 0) return i;
        }
    }
    return -1;
}
