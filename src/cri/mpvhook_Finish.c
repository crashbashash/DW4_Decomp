extern int (*DAT_004bcc08)();

void mpvhook_Finish(void) {
    if (DAT_004bcc08 != 0) {
        DAT_004bcc08();
    }
}
