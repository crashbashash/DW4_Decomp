/* 0x00285170 — FUN_00285170 (44 bytes). Calls the hook registered at 0x004bcbfc, if any, and returns its
   result (0 without a hook). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int (*DAT_004bcbfc)(void);

int FUN_00285170(void) {
    if (DAT_004bcbfc != 0) {
        return DAT_004bcbfc();
    }
    return 0;
}
