extern int (*DAT_004bcc30)();

void FUN_00285390(void) {
    if (DAT_004bcc30 != 0) {
        DAT_004bcc30();
    }
}
