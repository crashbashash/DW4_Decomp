extern int (*DAT_004bcc40)();

void mpvhook_GetInf(void) {
    if (DAT_004bcc40 != 0) {
        DAT_004bcc40();
    }
}
