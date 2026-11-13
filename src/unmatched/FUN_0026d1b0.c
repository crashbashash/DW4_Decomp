int ADXERR_CallErrFunc1();
int ADXSJD_GetDecNumSmpl();
extern int DAT_004eebf0[4];
int FUN_0026d1b0(void *arg0) {
    if (arg0 == 0) {
        ADXERR_CallErrFunc1(&DAT_004eebf0[0]);
        return -1;
    }
    return ADXSJD_GetDecNumSmpl(*(int *)((char *)(arg0) + 4));
}
