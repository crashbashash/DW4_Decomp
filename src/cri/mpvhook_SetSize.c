extern int (*DAT_004bcc30)();

void mpvhook_SetSize(void) {
    if (DAT_004bcc30 != 0) {
        DAT_004bcc30();
    }
}
