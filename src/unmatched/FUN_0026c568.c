int ADXERR_CallErrFunc1();
extern int DAT_004ee790[4];
short FUN_0026c568(int arg0, int arg1) {
    if (arg0 == 0) {
        ADXERR_CallErrFunc1(&DAT_004ee790[0]);
        return 0;
    }
    return *(int *)((char *)(((arg1 * 2) + arg0)) + 66);
}
