/* Calls the hook registered at 0x004bcc38, if any, and returns its result (0 without a hook). */
extern int (*DAT_004bcc38)(void);

int FUN_002853e0(void) {
    if (DAT_004bcc38 != 0) {
        return DAT_004bcc38();
    }
    return 0;
}
