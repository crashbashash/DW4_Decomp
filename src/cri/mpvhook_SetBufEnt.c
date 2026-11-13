extern int (*DAT_004bcc2c)();

void mpvhook_SetBufEnt(void) {
    if (DAT_004bcc2c != 0) {
        DAT_004bcc2c();
    }
}
