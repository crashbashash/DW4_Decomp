extern int (*DAT_004bcc10)();

void mpvhook_Destroy(void) {
    if (DAT_004bcc10 != 0) {
        DAT_004bcc10();
    }
}
