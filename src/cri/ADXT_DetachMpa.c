extern int (*DAT_004a8e60)();

void ADXT_DetachMpa(void) {
    if (DAT_004a8e60 != 0) {
        DAT_004a8e60();
    }
}
