extern int (*DAT_004bcc44)();

void mpvhook_GetRate(void) {
    if (DAT_004bcc44 != 0) {
        DAT_004bcc44();
    }
}
