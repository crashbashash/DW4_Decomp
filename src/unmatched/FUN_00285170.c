/* Calls the hook registered at 0x004bcbfc, if any, and returns its result (0 without a hook). */
extern int (*DAT_004bcbfc)(void);

int FUN_00285170(void) {
    if (DAT_004bcbfc != 0) {
        return DAT_004bcbfc();
    }
    return 0;
}
