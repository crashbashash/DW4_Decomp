extern int (*DAT_004bcc3c)();

void mpvhook_GetPicInf(void) {
    if (DAT_004bcc3c != 0) {
        DAT_004bcc3c();
    }
}
