int FUN_002607e8();
extern int DAT_004edef0[4];
int FUN_00262648(void *arg0) {
    if (arg0 == 0) {
        FUN_002607e8(&DAT_004edef0[0]);
        return -3;
    }
    return *(int *)((char *)(arg0) + 32);
}
