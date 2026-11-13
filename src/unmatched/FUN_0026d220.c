int ADXERR_CallErrFunc1();
int FUN_002670c8();
extern int DAT_004eec20[4];
void FUN_0026d220(void *arg0) {
    if (arg0 == 0) {
        ADXERR_CallErrFunc1(&DAT_004eec20[0]);
        return;
    }
    FUN_002670c8(*(int *)((char *)(arg0) + 4));
}
