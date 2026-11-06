int FUN_002607e8();
extern int DAT_004edec0[4];
int FUN_002625f8(void *arg0, int *arg1) {
    if (arg0 == 0) {
        FUN_002607e8(&DAT_004edec0[0]);
        *arg1 = 0;
        return -3;
    }
    *arg1 = *(int *)((char *)(arg0) + 24);
    return *(int *)((char *)(arg0) + 28);
}
