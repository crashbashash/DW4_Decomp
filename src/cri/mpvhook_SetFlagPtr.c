extern int (*DAT_004bcc34)();

void mpvhook_SetFlagPtr(void) {
    if (DAT_004bcc34 != 0) {
        DAT_004bcc34();
    }
}
