/* Calls the hook registered at 0x004bcc00, if any, and returns its result (0 without a hook). */
extern int (*DAT_004bcc00)(void);

int FUN_002851a0(void) {
    if (DAT_004bcc00 != 0) {
        return DAT_004bcc00();
    }
    return 0;
}
