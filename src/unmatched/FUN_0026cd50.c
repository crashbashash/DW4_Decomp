int ADXERR_CallErrFunc1();
extern int DAT_004eea98[4];
int FUN_0026cd50(void *arg0) {
    if (arg0 == 0) {
        ADXERR_CallErrFunc1(&DAT_004eea98[0]);
        return -1;
    }
    return *(int *)((char *)(arg0) + 76);
}
