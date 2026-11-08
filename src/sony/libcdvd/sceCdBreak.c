extern int DAT_004850c0;
extern int DAT_00484740;
extern volatile int DAT_0048356c;
extern volatile int DAT_00483598;
int FUN_0010af00(int sema);
int FUN_00116d90(int cmd);
void sceSifWriteBackDCache(void *p, int size);
int FUN_0010e2a8(void *cd, int fno, int mode, void *send, int ssize, void *recv, int rsize, void (*end)(void *), void *arg);
int sceCdBreak(void) {
    int r;
    if (FUN_00116d90(30) == 0) return 0;
    DAT_00483598 = 8;
    if (FUN_0010e2a8(&DAT_004850c0, 22, 0, 0, 0, &DAT_00484740, 4, 0, 0) < 0) {
        FUN_0010af00(DAT_0048356c);
        DAT_00483598 = 0;
        return 0;
    }
    DAT_00483598 = 0;
    r = *(int *)((unsigned int)&DAT_00484740 | 0x20000000);
    FUN_0010af00(DAT_0048356c);
    return r;
}
