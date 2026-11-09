extern int DAT_004850c0;
extern int DAT_00484740;
extern int DAT_0048356c;
extern int DAT_00483598;
int FUN_0010af00(int sema);
int FUN_00116d90(int cmd);
void sceSifWriteBackDCache(void *p, int size);
int FUN_0010e2a8(void *cd, int fno, int mode, void *send, int ssize, void *recv, int rsize, void (*end)(void *), void *arg);
extern int DAT_00484b80;
extern int DAT_004850e8;
extern int DAT_004850ec;
extern int DAT_004850f0;
int sceCdMmode(int arg) {
    int r;
    int *p;
    p = &DAT_00484b80;
    if (FUN_00116d90(34) == 0) return 0;
    *p = arg;
    sceSifWriteBackDCache(p, 4);
    if (FUN_0010e2a8(&DAT_004850c0, DAT_004850e8, 0, p, DAT_004850ec, &DAT_00484740, DAT_004850f0, 0, 0) < 0) {
        FUN_0010af00(DAT_0048356c);
        return 0;
    }
    r = *(int *)((unsigned int)&DAT_00484740 | 0x20000000);
    FUN_0010af00(DAT_0048356c);
    return r;
}
