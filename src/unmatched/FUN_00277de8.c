/* 0x00277de8 — FUN_00277de8 (48 bytes). Error report: invokes the registered error callback 0x004b0374, if
   any, with its context word 0x004b0378, the message and the caller's first argument (same shape as
   FUN_002739b8). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern void (*DAT_004b0374)(int context, const char *message, int detail);
extern int DAT_004b0378;

void FUN_00277de8(int detail, const char *message) {
    if (DAT_004b0374 != 0) {
        DAT_004b0374(DAT_004b0378, message, detail);
    }
}
