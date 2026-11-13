extern int (*DAT_004bcc04)();

void mpvhook_Init(void) {
    if (DAT_004bcc04 != 0) {
        DAT_004bcc04();
    }
}
