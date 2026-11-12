/* Runs a server pass (FUN_0029ac78) for the caller: in mode 1 (ADXM_IsSetupThrd) only when
 * FUN_0029aa78 also reports 1, otherwise after FUN_0029aa98; returns the pass result or 0 when
 * skipped. */
extern int ADXM_IsSetupThrd(void);
extern int FUN_0029aa78(void *arg);
extern void FUN_0029aa98(void *arg);
extern int FUN_0029ac78(void *arg);

int FUN_0029a990(void *arg) {
    int result = 0;
    int mode = ADXM_IsSetupThrd();

    if (mode == 1) {
        if (FUN_0029aa78(arg) == mode) {
            result = FUN_0029ac78(arg);
        }
    } else {
        FUN_0029aa98(arg);
        result = FUN_0029ac78(arg);
    }
    return result;
}
