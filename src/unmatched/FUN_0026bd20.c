int ADXERR_CallErrFunc1();
extern int DAT_004ee5f0[4];
char FUN_0026bd20(void *arg0) {
    if (arg0 == 0) {
        ADXERR_CallErrFunc1(&DAT_004ee5f0[0]);
        return -1;
    }
    return *(int *)((char *)(arg0) + 1);
}
