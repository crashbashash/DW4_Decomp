extern int (*DAT_004bcc08)();

void FUN_002851f8(void) {
    if (DAT_004bcc08 != 0) {
        DAT_004bcc08();
    }
}
