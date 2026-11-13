/* Forwards its second argument to ADXERR_CallErrFunc1 (the ADX error reporter); the first is ignored. */
extern void ADXERR_CallErrFunc1(const char *message);

void FUN_00279200(int unused, const char *message) {
    ADXERR_CallErrFunc1(message);
}
