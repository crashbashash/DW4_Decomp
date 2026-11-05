/* 0x002853e0 — FUN_002853e0 (44 bytes). Calls the hook registered at 0x004bcc38, if any, and returns its
   result (0 without a hook). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int (*DAT_004bcc38)(void);

int FUN_002853e0(void) {
    if (DAT_004bcc38 != 0) {
        return DAT_004bcc38();
    }
    return 0;
}
