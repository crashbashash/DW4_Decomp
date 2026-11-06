int FUN_002607e8();
extern int DAT_004ee7f0[4];
short FUN_0026c630(void *arg0) {
    if (arg0 == 0) {
        FUN_002607e8(&DAT_004ee7f0[0]);
        return 0;
    }
    return *(int *)((char *)(arg0) + 70);
}
