/* Calls the hook registered at 0x004bcc0c, if any, and returns its result (0 without a hook). */
extern int (*DAT_004bcc0c)(void);

int FUN_00285220(void) {
    if (DAT_004bcc0c != 0) {
        return DAT_004bcc0c();
    }
    return 0;
}
