/* 0x00285220 — FUN_00285220 (44 bytes). Calls the hook registered at 0x004bcc0c, if any, and returns its
   result (0 without a hook). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int (*DAT_004bcc0c)(void);

int FUN_00285220(void) {
    if (DAT_004bcc0c != 0) {
        return DAT_004bcc0c();
    }
    return 0;
}
