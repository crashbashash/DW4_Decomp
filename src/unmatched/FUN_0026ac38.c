/* Ignores its first argument and passes the second, a message, to ADXERR_CallErrFunc1. */
void ADXERR_CallErrFunc1(const char *message);

void FUN_0026ac38(void *unused, const char *message) {
    ADXERR_CallErrFunc1(message);
}
