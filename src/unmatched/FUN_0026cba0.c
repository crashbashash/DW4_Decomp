int ADXERR_CallErrFunc1();
extern int DAT_004eea08[4];
int FUN_0026cba0(void *arg0) {
    if (arg0 == 0) {
        ADXERR_CallErrFunc1(&DAT_004eea08[0]);
        return -1;
    }
    return *(char *)((char *)(arg0) + 1) == 5;
}
