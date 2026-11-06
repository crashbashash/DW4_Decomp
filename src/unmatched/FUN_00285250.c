extern int (*DAT_004bcc10)();

void FUN_00285250(void) {
    if (DAT_004bcc10 != 0) {
        DAT_004bcc10();
    }
}
