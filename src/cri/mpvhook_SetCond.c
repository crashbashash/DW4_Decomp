extern int (*DAT_004bcc14)();

void mpvhook_SetCond(void) {
    if (DAT_004bcc14 != 0) {
        DAT_004bcc14();
    }
}
