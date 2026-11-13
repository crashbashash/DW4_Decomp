extern int (*DAT_004a8e5c)();

void ADXT_DetachAhx(void) {
    if (DAT_004a8e5c != 0) {
        DAT_004a8e5c();
    }
}
