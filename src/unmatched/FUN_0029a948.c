/* In mode 1 (ADXM_IsSetupThrd) returns FUN_0029aa98(arg), otherwise 0. */
extern int ADXM_IsSetupThrd(void);
extern int FUN_0029aa98(void *arg);

int FUN_0029a948(void *arg) {
    int result = 0;

    if (ADXM_IsSetupThrd() == 1) {
        result = FUN_0029aa98(arg);
    }
    return result;
}
