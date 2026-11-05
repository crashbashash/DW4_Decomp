int FUN_002607e8();
extern int DAT_004ee5f0[4];
char FUN_0026bd20(void *arg0) {
    if (arg0 == 0) {
        FUN_002607e8(&DAT_004ee5f0[0]);
        return -1;
    }
    return *(int *)((char *)(arg0) + 1);
}
