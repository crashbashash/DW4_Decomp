int ADXERR_CallErrFunc1();
extern int DAT_004eebc0[4];
char ADXT_GetStatPause(void *arg0) {
    if (arg0 == 0) {
        ADXERR_CallErrFunc1(&DAT_004eebc0[0]);
        return 0;
    }
    return *(int *)((char *)(arg0) + 114);
}
