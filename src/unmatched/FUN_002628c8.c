int FUN_002607e8();
extern int DAT_004edf98[4];
void FUN_002628c8(void *arg0, int arg1) {
    if (*(char *)((char *)(arg0) + 1) == 2) {
        FUN_002607e8(&DAT_004edf98[0]);
        return;
    }
    *(int *)((char *)(arg0) + 44) = arg1;
}
