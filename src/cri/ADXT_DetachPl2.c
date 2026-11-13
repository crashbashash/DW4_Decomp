extern int (*DAT_004a8e68)();

void ADXT_DetachPl2(void) {
    if (DAT_004a8e68 != 0) {
        DAT_004a8e68();
    }
}
